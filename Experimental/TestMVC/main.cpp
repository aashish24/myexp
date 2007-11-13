
#include "osgDB/ReadFile"

#include "OsgModel.h"

#include "Viewer.h"

int main( int argc, char** argv )
{
  osg::Node* node = osgDB::readNodeFile( "cow.osg" );
  
  Oge::OgeOsg::OsgViewer::Viewer viewer;

  viewer.setModelData( node );
  
  viewer.run();
}

