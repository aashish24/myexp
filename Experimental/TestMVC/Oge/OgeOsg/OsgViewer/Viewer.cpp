
#include "Viewer.h"

#include "Oge/OgeOsg/OsgCore/OsgModel.h" 
#include "Oge/OgeOsg/OsgCore/OsgView.h" 

namespace Oge
{
  namespace OgeOsg
  { 
    namespace OsgViewer
    {

      Viewer::Viewer( ViewerModel vModel ) : 
        osgViewer::Viewer(),
        _model                  ( new Viewer::OsgModel() ) ,
        _view                   ( new Viewer::OsgView ( _model ) ), 
        _viewportX              ( 0 ), 
        _viewportY              ( 0 ), 
        _viewportWidth          ( 400 ), 
        _viewportHeight         ( 400 ), 
        _isDisplayWindowSizeSet ( false ),
        _viewerModel            ( vModel )
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

      
      /////////////////////////////////////////////////////////////////////////
      //
      // 
      // @Note: This function should be called by the external windowing system 
      // only when we have a valid context. 
      //
      /////////////////////////////////////////////////////////////////////////

      void Viewer::contextInit()
      {        
        if( _viewerModel == EMBEDDED )
        {
          this->setUpViewerAsEmbeddedInWindow
            ( _viewportX, _viewportY, _viewportWidth, _viewportHeight );
        }
      }


      void Viewer::setModelData( osg::Node* node )
      {
        ( _model->rootModel()->asGroup() )->addChild ( node );
      }


      void Viewer::setEmbeddedDisplaySize( int x, int y, int width, int height )
      {
        _viewportX = x;
        _viewportY = y;

        _viewportWidth =  width;
        _viewportHeight = height;
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
        if( _viewerModel == EMBEDDED )
        {
          osgViewer::Viewer::run();
        }
        {
          frame();
        }

        return 1;
      }


      void Viewer::setSceneData( osg::Node* node )
      {
        osgViewer::Viewer::setSceneData( node );
      }
    }
  }
}