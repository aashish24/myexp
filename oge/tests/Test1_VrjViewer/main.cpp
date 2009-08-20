
// This is QT-OSG fusion exmple. 

#include <iostream>
#include "boost/bind.hpp"


#include "osgDB/ReadFile"

#include "Oge/OgeVrj/VrjOsg/VrjViewer.h"

int main( int argc, char **argv )
{
  typedef Oge::OgeVrj::VrjOsg::VrjViewer VrjViewer;
   
  osg::ArgumentParser arguments(&argc, argv);

  // load the scene.
  osg::ref_ptr< osg::Node > loadedModel = osgDB::readNodeFiles( arguments );
  if (!loadedModel)
  {
      std::cout << argv[0] <<": No data loaded." << std::endl;
      return 1;
  }

  VrjViewer::RefPtr viewer = new VrjViewer( argc, argv );

  viewer->setSceneData( loadedModel.get() );    

  viewer->run();
}

