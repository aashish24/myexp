
#include "osg/Notify"
#include "osgGA/GUIEventAdapter"
#include "osgGA/GUIActionAdapter"
#include "osgDB/ReadFile"
#include "osgUtil/Optimizer"
#include "osgViewer/Viewer"

#include "SceneManager.h"


#include <iostream>

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

    // create the scene
    osg::ref_ptr< SceneManager > sm( new SceneManager );

    viewer.setSceneData( sm->getRootNode().get() );

    return viewer.run();
}

