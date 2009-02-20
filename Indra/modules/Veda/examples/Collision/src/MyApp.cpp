//:
//: 

//: MYApp includes.
#include "MyApp.h"

//: C++ includes.
#include <fstream>

//: 
#include <osg/Group>
#include <osg/Node>
#include <osg/PolygonMode>

#include <Types.h>

//;
#include <Types.h>

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgVJApp( kern, argc, argv )
{
	/// Initialize member variables here.
	count = 0;
}

//:---------------------------------------------------------------------
//: One time initialization. 
//:---------------------------------------------------------------------
void MyApp::appInit()
{
	//: Set all the properties here
	setDevice(ALL, OFF);	
	setBackgroundColor((gmtl::Vec4f(0.35, 0.35, 0.35, 1.0)).getData());	
	setSceneInitialPosition(osg::Vec3(0.0, 0.0, 0.0));

	/// Current interaction engine can be queried in appInit() now. 
	getEngine()->setNavigationMode( FLYING_PLANE );

	/// App has to initialize and update KeyboradMouseHandler object. 
	mKMHandle.init();
	
	//setScenePivotPoint(osg::Vec3(0.0, 0.0, 0.0));	
} 

//:---------------------------------------------------------------------
//: 
//:---------------------------------------------------------------------
void MyApp::appBufferPreDraw()
{
	//: Set background color to black.
	glClearColor(0.5, 0.5, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

//:---------------------------------------------------------------------
//: Scenegraph will be build here. 
//:---------------------------------------------------------------------
void MyApp::appSceneInit()
{	
	std::cerr << " [MyApp] apiInit starts: " << std::endl;		

	osg::ref_ptr<osg::Group> modelGroupNode = new osg::Group();
	loadGroupedData(modelGroupNode.get(), ".//../data/ModelList.txt");

	osg::ref_ptr<osg::StateSet> stateset = modelGroupNode->getOrCreateStateSet();
	if(stateset.valid())
	{
		/// Wireframe display on. 
		//osg::ref_ptr<osg::PolygonMode> poly_mode = new osg::PolygonMode();
		//poly_mode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		//stateset->setAttributeAndModes(poly_mode.get(), osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
	}

	if(modelGroupNode.get())
	{
		mModelGroupNode->addChild(modelGroupNode.get());
	}

	std::cerr << " [MyApp] apiInit ends: " << std::endl;
}

//:---------------------------------------------------------------------
//: Load data files from the XML. 
//: TODO: Parameter should be ref_ptr not the raw pointer. 
//:---------------------------------------------------------------------
void MyApp::loadGroupedData(osg::Group* groupNode, const std::string& fileName)
{
	std::ifstream inputFile(fileName.c_str(), std::ios_base::in);
	if(inputFile.good()) 
	{		
		while(!inputFile.eof())
		{
			std::string dataFileName; 
			inputFile >> dataFileName >> std::ws;
			std::cerr << " [MyApp] Start loading: "  << dataFileName << std::endl;
			osg::ref_ptr<osg::Node> modelNode = osgDB::readNodeFile(dataFileName);
			if(modelNode.get())
			{		
				//: Just for the fun lets add one more cow. (Shallow Copy in OSG). 
				std::cerr << " Name: " << modelNode->getName();		
				osg::ref_ptr<osg::MatrixTransform> modelTransform_1 = new osg::MatrixTransform();
				//osg::ref_ptr<osg::MatrixTransform> modelTransform_2 = new osg::MatrixTransform();

				//: I found that we need to perform the translation first <BR> 
				//: before we add the model to the second transform node <BR>
				//: else it does not work. (any translation does not work.)
				//modelTransform_2->preMult(osg::Matrixf::translate(10.0, 0.0,0.0));
				modelTransform_1->addChild(modelNode.get());
				//modelTransform_2->addChild(modelNode.get());
				groupNode->addChild(modelTransform_1.get());	
				//groupNode->addChild(modelTransform_2.get());	
			}
			else 
			{
				std::cerr << " [MyApp]		Failed to load: "  << dataFileName << std::endl;
			}

			std::cerr << " [MyApp]		Finished loading: "  << dataFileName << std::endl;
		}
	}
	else
	{	
		std::cerr << " [MyApp]		Input file is corrupted: "  << std::endl;
	}
	inputFile.close();
}

void MyApp::appPreFrame()
{
	mKMHandle.update();

	if( !mKMHandle.isKeyPressEventEmpty() )
	{
		std::cout << mKMHandle.getKeyboardInputAsString( false, char(13) );
	}
}

void MyApp::appLatePreFrame()
{
	osgUtil::IntersectVisitor::HitList hli;
	osg::ref_ptr< osg::LineSegment > seg = 
		new osg::LineSegment( osg::Vec3( 0.0, 0.0, 0.0 ), osg::Vec3( 0.0, -5.0, 0.0 ) ); 
	getEngine()->checkForIntersection( seg.get(), hli );

	if( hli.empty() )
	{
		//std::cerr << " Is empty: " << std::endl;
	}
	else
	{
	   std::cerr <<  " Is not empty: " << std::endl;
	   osg::Matrixf matrix = mSceneTransformNode->getMatrix();
	   std::cerr 
		   << matrix( 0, 0 ) << " " 
		   << matrix( 0, 1 ) << " " 
		   << matrix( 0, 2 ) << " " 
		   << matrix( 0, 3 ) << " " 
		   << matrix( 1, 0 ) << " " 
		   << matrix( 1, 1 ) << " " 
		   << matrix( 1, 2 ) << " " 
		   << matrix( 1, 3 ) << " " 
		   << matrix( 2, 0 ) << " " 
		   << matrix( 2, 1 ) << " " 
		   << matrix( 2, 2 ) << " " 
		   << matrix( 2, 3 ) << " " 	 
		   << matrix( 3, 0 ) << " " 
		   << matrix( 3, 1 ) << " " 
		   << matrix( 3, 2 ) << " " 
		   << matrix( 3, 3 ) << " " 
		   << std::endl;
		   matrix.setTrans(0.0, -5.0, 0.0 );
		   getEngine()->reset();
		   mSceneTransformNode->setMatrix( matrix );
	}
}