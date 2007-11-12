
#include "osgDB/ReadFile"
#include "osgViewer/Viewer"

#include "OsgModel.h"
#include "OsgView.h"

#include "Viewer.h"

int main( int argc, char** argv )
{
  // We need to have a document which contains a viewer.   
  Oge::OgeOsg::OsgCore::OsgModel* model = new Oge::OgeOsg::OsgCore::OsgModel();
  Oge::OgeOsg::OsgCore::OsgView* view   = new Oge::OgeOsg::OsgCore::OsgView( model );   
  
  osg::Node* node = osgDB::readNodeFile( "cow.osg" );
  
  model->setSceneData( node );
  model->build(); 
  
  osgViewer::Viewer viewer;
  
  viewer.realize();    
  
  viewer.setSceneData( view->sceneView()->getSceneData() );
  
  viewer.run();
}

