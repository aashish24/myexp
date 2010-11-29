#include "App.h"

#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgDBd.lib" )
# pragma comment( lib, "osgUtild.lib" )
# pragma comment( lib, "osgFXd.lib" )
# pragma comment( lib, "osgTextd.lib" )
# elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgUtil.lib" )
# pragma comment( lib, "osgFX.lib" )
# pragma comment( lib, "osgText.lib" )  
#endif

int main( int argc, char **argv )
{
  typedef Oge::OgeVrj::VrjOsg::VrjViewer VrjViewer;
   
  osg::ArgumentParser arguments(&argc, argv);

  // Create new App here. 
  App::RefPtr app( new App( argc, argv ) );

  app->run();
}

