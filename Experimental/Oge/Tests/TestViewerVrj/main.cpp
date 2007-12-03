
// This is QT-OSG fusion exmple. 

#include <iostream>

#include "osgDB/ReadFile"

#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h"


int main( int argc, char **argv )
{
  typedef Oge::OgeOsg::OsgVrj::ViewerVrj ViewerVrj;
   
  osg::ArgumentParser arguments(&argc, argv);

  // load the scene.
  osg::ref_ptr< osg::Node > loadedModel = osgDB::readNodeFiles( arguments );
  if (!loadedModel)
  {
      std::cout << argv[0] <<": No data loaded." << std::endl;
      return 1;
  }

  ViewerVrj* viewer = new ViewerVrj;

  viewer->addDataModel( loadedModel.get() );  

  viewer->getCamera()->set( 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  viewer->run();
}

