
// This is QT-OSG fusion exmple. 

#include <iostream>
#include "boost/bind.hpp"


#include "osgDB/ReadFile"

#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h"

#include "Oge/OgeBase/OgeDev/Gamepad.h"

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

  ViewerVrj::RefPtr viewer = new ViewerVrj( argc, argv );

  viewer->setSceneData( loadedModel.get() );    

  viewer->run();
}

