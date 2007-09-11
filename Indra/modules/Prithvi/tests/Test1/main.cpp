
#include "Prithvi/Core/Planet.h"

#include "osgViewer/Viewer"
#include "osgViewer/ViewerEventHandlers"


#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgViewerd.lib" )
#elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgViewer.lib" )
#endif // defined ( _MSC_VER && _DEBUG )

int main( int argc, char** argv )
{
  osgViewer::Viewer viewer;

  Prithvi::Core::Planet::RefPtr planet( new Prithvi::Core::Planet() );
  
  planet->readKwl( std::string( argv[ 1 ] ) );

  viewer.setSceneData( planet->root() );

  viewer.realize();

  return viewer.run();
}
