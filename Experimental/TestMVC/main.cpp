
#include "osgDB/ReadFile"
#include "osgViewer/Viewer"

#include "AlphaOsgModel.h"
#include "AlphaOsgView.h"

int main( int argc, char** argv )
{
  // We need to have a document which contains a viewer.   
  Oge::OgeOsg::OgeOsgCore::AlphaOsgModel* model = new Oge::OgeOsg::OgeOsgCore::AlphaOsgModel();
  Oge::OgeOsg::OgeOsgCore::AlphaOsgView* view = new Oge::OgeOsg::OgeOsgCore::AlphaOsgView( model );   
  
  osg::Node* node = osgDB::readNodeFile( "cow.osg" );
  
  model->setSceneData( node );
  model->build(); 
  
  osgViewer::Viewer viewer;
  
  viewer.realize();    
  
  viewer.setSceneData( view->sceneView()->getSceneData() );
  
  viewer.run();
}

