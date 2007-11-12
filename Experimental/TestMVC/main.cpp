
#include "osg/Timer"
#include "osg/GraphicsContext"
#include "osg/ApplicationUsage"

#include "osgUtil/SceneView"

#include "osgDB/ReadFile"
#include "osgDB/WriteFile"

#include "osgViewer/Viewer"

#include "AlphaOsgModel.h"
#include "AlphaOsgView.h"

using namespace Oge::OgeBase::OgeInterfaces;
using namespace Oge::OgeOsg::OgeOsgCore;

int main( int argc, char** argv )
{
  // We need to have a document which contains a viewer.   
  AlphaOsgModel* model = new AlphaOsgModel();
  AlphaOsgView* view = new AlphaOsgView( model );   
  
  osg::Node* node = osgDB::readNodeFile( "cow.osg" );
  
  model->setSceneData( node );
  model->build();
  
  osgViewer::Viewer viewer;
  
  viewer.realize();    
  
  viewer.setSceneData( view->sceneView()->getSceneData() );
  
  viewer.run();
}

