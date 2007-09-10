
#include "Prithvi/Core/Planet.h"

#include "osgViewer/Viewer"
#include "osgViewer/ViewerEventHandlers"

int main( int argc, char** argv )
{
  osgViewer::Viewer viewer;

  Prithvi::Core::Planet::RefPtr planet( new Prithvi::Core::Planet() );
  
  planet->readKwl( std::string( argv[ 1 ] ) );

  viewer.setSceneData( planet->root() );

  viewer.realize();

  return viewer.run();
}
