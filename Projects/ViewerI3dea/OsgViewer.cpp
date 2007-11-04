
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>

#include <osg/Switch>
#include <osgText/Text>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>

#include <osg/MatrixTransform>

#include <iostream>

#include "GlslShaders.h"

// Global list of shders programs. 
static std::vector< I3deaApp::IGlslShaders* > shaders;

// Keyboard mouse event handler. 
class KeyHandler: public osgGA::GUIEventHandler
{
    public:
		KeyHandler( osg::Node* scene ) :
                mRoot( scene )
        {}

        bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& )
        {
			static unsigned int shadersCounter = 0;

            if( ea.getEventType() != osgGA::GUIEventAdapter::KEYDOWN )
                return false;

            switch( ea.getKey() )
            {
                case 'e':
				{
					// Enable the next shader. Disable the last one. 
					if( !shaders.empty() && ( shaders.at( shadersCounter ) ) )
					{
						if( shadersCounter != 0 )
						{
							int prevShader = shadersCounter - 1;
							shaders[ prevShader ]->disableShaders( mRoot.get() );
						}

						shaders[shadersCounter]->applyShaders( mRoot.get() );						
					}
					++shadersCounter;

					if( shadersCounter >=  shaders.size() )
					{
						shadersCounter  = 0;
					}

                    return false;
				}
				case 'd':
				{
					// Disable the current shader. 
					if( !shaders.empty() && ( shaders.at( shadersCounter ) ) )
					{
						shaders[shadersCounter]->disableShaders( mRoot.get() );						
					}
				}
            }
            return false;
        }

    private:
		osg::ref_ptr< osg::Node >  mRoot;
};

// Rescale the scene to unit bounding sphere. This is required to make sure 
// that eye separation required to make it look stereo correct constant.
osg::Group* createSceneScaleByBSRatio( osg::Group* root, float reqBSSize )
{
	if( !root )
	{
		return 0x00;
	}

	osg::Matrix mat;
	float scaleFactor = reqBSSize / root->getBound().radius();
	mat.makeScale( osg::Vec3f( scaleFactor, scaleFactor, scaleFactor ) );

	osg::ref_ptr< osg::MatrixTransform > transform( new osg::MatrixTransform() );
	transform->setMatrix( mat );
	transform->addChild( root );

	// Since this we applied the scane the normals of the geometry needs to be renormalized. 
	osg::ref_ptr< osg::StateSet > ss( transform->getOrCreateStateSet() );
	ss->setMode( GL_NORMALIZE, osg::StateAttribute::ON );

	return ( static_cast< osg::Group* >( transform.release() ) );
}

// Add additional lights to the scene.
void addSceneLight( osg::Node* node )
{
	const float positionFactor =  10.0;

	osg::ref_ptr< osg::Group > root( node->asGroup() );
	if( !root.valid() )
	{
		return;
	}
	
	osg::ref_ptr< osg::StateSet > rootStateSet( root->getOrCreateStateSet() );
	if( !rootStateSet.valid() )
	{
		return;
	}

	// Transforms for the light which would be static. 
	osg::ref_ptr< osg::MatrixTransform > transformLight( new osg::MatrixTransform() );
	//transformLight->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
	
	// Sky light. 
	osg::ref_ptr< osg::Light > light1( new osg::Light() );
	light1->setAmbient( osg::Vec4( 0.1, 0.1, 0.1, 1.0 ) );	
	light1->setDiffuse( osg::Vec4( 0.3, 0.3, 0.3, 1.0 ) );
	light1->setSpecular( osg::Vec4( 0.3, 0.3, 0.3, 1.0 ) );
	light1->setPosition( osg::Vec4( 0.0, 0.0, ( root->getBound().radius() + positionFactor ), 0.0 ) );
	light1->setLightNum( 1 );

	osg::ref_ptr< osg::Light > light2( new osg::Light() );
	light2->setAmbient( osg::Vec4( 0.1, 0.1, 0.1, 1.0 ) );	
	light2->setDiffuse( osg::Vec4( 0.2, 0.2, 0.2, 1.0 ) );
	light2->setSpecular( osg::Vec4( 0.2, 0.2, 0.2, 1.0 ) );
	light2->setPosition( osg::Vec4( 0.0, 0.0, -( root->getBound().radius() + positionFactor ), 0.0 ) );
	light2->setLightNum( 2 );
	
	osg::ref_ptr< osg::LightSource > lightSource1( new osg::LightSource() );
	lightSource1->setLight( light1.get() );
	lightSource1->setLocalStateSetModes( osg::StateAttribute::ON );
	lightSource1->setStateSetModes( *rootStateSet, osg::StateAttribute::ON );

	osg::ref_ptr< osg::LightSource > lightSource2( new osg::LightSource() );
	lightSource2->setLight( light2.get() );
	lightSource2->setLocalStateSetModes( osg::StateAttribute::ON );
	lightSource2->setStateSetModes( *rootStateSet, osg::StateAttribute::ON );

	transformLight->addChild( lightSource1.get() );
	transformLight->addChild( lightSource2.get() );

	root->addChild( transformLight.get() );
}

int main(int argc, char** argv)
{
    // use an ArgumentParser object to manage the program arguments.
    osg::ArgumentParser arguments(&argc,argv);

    arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
    arguments.getApplicationUsage()->setDescription(arguments.getApplicationName()+" is the standard OpenSceneGraph example which loads and visualises 3d models.");
    arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName()+" [options] filename ...");
    arguments.getApplicationUsage()->addCommandLineOption("--image <filename>","Load an image and render it on a quad");
    arguments.getApplicationUsage()->addCommandLineOption("--dem <filename>","Load an image/DEM and render it on a HeightField");
    arguments.getApplicationUsage()->addCommandLineOption("-h or --help","Display command line parameters");
    arguments.getApplicationUsage()->addCommandLineOption("--help-env","Display environmental variables available");
    arguments.getApplicationUsage()->addCommandLineOption("--help-keys","Display keyboard & mouse bindings available");
    arguments.getApplicationUsage()->addCommandLineOption("--help-all","Display all command line, env vars and keyboard & mouse bindings.");
    arguments.getApplicationUsage()->addCommandLineOption("--SingleThreaded","Select SingleThreaded threading model for viewer.");
    arguments.getApplicationUsage()->addCommandLineOption("--CullDrawThreadPerContext","Select CullDrawThreadPerContext threading model for viewer.");
    arguments.getApplicationUsage()->addCommandLineOption("--DrawThreadPerContext","Select DrawThreadPerContext threading model for viewer.");
    arguments.getApplicationUsage()->addCommandLineOption("--CullThreadPerCameraDrawThreadPerContext","Select CullThreadPerCameraDrawThreadPerContext threading model for viewer.");

    // if user request help write it out to cout.
    bool helpAll = arguments.read("--help-all");
    unsigned int helpType = ((helpAll || arguments.read("-h") || arguments.read("--help"))? osg::ApplicationUsage::COMMAND_LINE_OPTION : 0 ) |
                            ((helpAll ||  arguments.read("--help-env"))? osg::ApplicationUsage::ENVIRONMENTAL_VARIABLE : 0 ) |
                            ((helpAll ||  arguments.read("--help-keys"))? osg::ApplicationUsage::KEYBOARD_MOUSE_BINDING : 0 );
    if (helpType)
    {
        arguments.getApplicationUsage()->write(std::cout, helpType);
        return 1;
    }

    osgViewer::Viewer viewer(arguments);
    
    // report any errors if they have occurred when parsing the program arguments.
    if (arguments.errors())
    {
        arguments.writeErrorMessages(std::cout);
        return 1;
    }
    
    if (arguments.argc()<=1)
    {
        arguments.getApplicationUsage()->write(std::cout,osg::ApplicationUsage::COMMAND_LINE_OPTION);
        return 1;
    }

    // set up the camera manipulators.
    {
        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

        keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
        keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
        keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
        keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );

        std::string pathfile;
        char keyForAnimationPath = '5';
        while (arguments.read("-p",pathfile))
        {
            osgGA::AnimationPathManipulator* apm = new osgGA::AnimationPathManipulator(pathfile);
            if (apm || !apm->valid()) 
            {
                unsigned int num = keyswitchManipulator->getNumMatrixManipulators();
                keyswitchManipulator->addMatrixManipulator( keyForAnimationPath, "Path", apm );
                keyswitchManipulator->selectMatrixManipulator(num);
                ++keyForAnimationPath;
            }
        }

        viewer.setCameraManipulator( keyswitchManipulator.get() );
    }

    // add the state manipulator
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
    
    // add the thread model handler
    viewer.addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer.addEventHandler(new osgViewer::WindowSizeHandler);
        
    // add the stats handler
    viewer.addEventHandler(new osgViewer::StatsHandler);

    // add the help handler
    viewer.addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));

    // add the record camera path handler
    viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
	
	// SceneGraph creation.  
	osg::ref_ptr< osg::Group > root ( new osg::Group() );

    // load the data
    osg::ref_ptr< osg::Node > loadedModel = osgDB::readNodeFiles(arguments);
    if (!loadedModel) 
    {
        std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;
        return 1;
    }

    // any option left unread are converted into errors to write out later.
    arguments.reportRemainingOptionsAsUnrecognized();

    // report any errors if they have occurred when parsing the program arguments.
    if (arguments.errors())
    {
        arguments.writeErrorMessages(std::cout);
        return 1;
    }
	
	// Add loaded models to the scene root. 
	root->addChild( loadedModel.get() );

	// Create a scale scene root. 
	root = createSceneScaleByBSRatio( root.get(), 1.0 );

	// Add light to the scene. 
	addSceneLight( root.get() );

	// Add shaders. 
	shaders.push_back( new I3deaApp::GlslShaders() );

	// Add keyboard mouse event handler. 
	viewer.addEventHandler( new KeyHandler( root.get() ) );

	// Finally hand it off to the viewer. 
    viewer.setSceneData( root.get() );

    viewer.realize();

    viewer.run();
}
