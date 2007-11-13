
#include "Viewer.h"

#include "OsgModel.h" 
#include "OsgView.h" 

namespace Oge
{
  namespace OgeOsg
  { 
    namespace OsgViewer
    {

      Viewer::Viewer( ViewerModel vModel) : 
        osgViewer::Viewer(),
        _model( new Viewer::OsgModel() ) ,
        _view( new Viewer::OsgView( _model ) ), 
        _viewerModel( vModel )
      {   
        init();
      }


      Viewer::~Viewer() 
      {
      }  


      void Viewer::init()
      {
        _model->build();
        setSceneData( _view->sceneView()->getSceneData() );
      }


      void Viewer::contextInit()
      {
      }


      void Viewer::setModelData( osg::Node* node )
      {
        ( _model->rootModel()->asGroup() )->addChild ( node );
      }


      osg::Node* Viewer::findNode( const std::string& id )
      {
        return 0x00;
      }


      Viewer::IUnknown* Viewer::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }


      void Viewer::update()
      {
      }


      void Viewer::draw()
      {
      }


      int Viewer::run()
      {
        return osgViewer::Viewer::run();
      }


      void Viewer::setSceneData( osg::Node* node )
      {
        osgViewer::Viewer::setSceneData( node );
      }
    }
  }
}