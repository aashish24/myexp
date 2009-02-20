
#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgDBd.lib" )
# pragma comment( lib, "osgUtild.lib" )
# pragma comment( lib, "osgGAd.lib" )
# pragma comment( lib, "osgTextd.lib" )
# pragma comment( lib, "osgViewerd.lib" )
# pragma comment( lib, "OpenThreadsd.lib" )
# elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgUtil.lib" )
# pragma comment( lib, "osgGA.lib" )
# pragma comment( lib, "osgText.lib" )  
# pragma comment( lib, "osgViewer.lib" )  
# pragma comment( lib, "OpenThreads.lib" )
#endif

#include "osg/Notify"
#include "osgGA/GUIEventAdapter"
#include "osgGA/GUIActionAdapter"
#include "osgDB/ReadFile"
#include "osgUtil/Optimizer"
#include "osgViewer/Viewer"

#include <iostream>

#include "SceneManager.h" 

// create the scene
static osg::ref_ptr< SceneManager > sm;


class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
    
        KeyboardEventHandler()
        {
        }
            
    
        virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
        {
            switch(ea.getEventType())
            {
                case(osgGA::GUIEventAdapter::KEYDOWN):
                {                
                    sm->update();
                    return true;
                }
                case(osgGA::GUIEventAdapter::KEYUP):
                {                 
                    return true;
                }

                default:
                    return false;
            }
        }
        
};


int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // Add the path for data files in lookup path lists.    
    osgDB::FilePathList dirs;

#if defined( _MSC_VER ) && _MSC_VER >= 1400  
    char* indraRoot( NULL );
    size_t len;
    _dupenv_s( &indraRoot, &len, "INDRA_ROOT_DIR" );
#else
    const char* indraRoot = getenv( "INDRA_ROOT_DIR" ); 
#endif
    if( indraRoot )
    {
      std::cout << "Indra root is: " << indraRoot << std::endl;
      
      dirs.push_back( std::string( indraRoot ) + std::string( "\\shaders\\GLSL\\") );
      osgDB::Registry::instance()->setDataFilePathList( dirs );
    }

    sm = new SceneManager();

    viewer.setSceneData( sm->getRootNode().get() );

    viewer.addEventHandler( new KeyboardEventHandler() );

    viewer.run();
  
    return 1;
}

