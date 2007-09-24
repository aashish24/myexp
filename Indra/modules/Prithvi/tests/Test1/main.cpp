
#include "Prithvi/Core/Planet.h"

#include "osgViewer/Viewer"
#include "osgViewer/ViewerEventHandlers"


#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgViewerd.lib" )
#elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgGA.lib" )
# pragma comment( lib, "osgViewer.lib" )
#endif // defined ( _MSC_VER && _DEBUG )

int main( int argc, char** argv )
{
  osgViewer::Viewer viewer;

  Prithvi::Core::Planet::RefPtr planet( new Prithvi::Core::Planet() );
  
  planet->readKwl( std::string( argv[ 1 ] ) );

  // add the thread model handler
   viewer.addEventHandler(new osgViewer::ThreadingHandler);
   
   // add the window size toggle handler
   viewer.addEventHandler(new osgViewer::WindowSizeHandler);
   
   // add the stats handler
   viewer.addEventHandler(new osgViewer::StatsHandler);
   
   // add the help handler
   //viewer.addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));
   
   // add the record camera path handler
   viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

  viewer.setSceneData( planet->root() );

  viewer.realize();
   
  //planet->mDatabasePager->setExpiryDelay( 0 );
  
  return viewer.run();
}
