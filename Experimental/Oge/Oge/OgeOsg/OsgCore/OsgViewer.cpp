
#include "Oge/OgeOsg/OsgCore/OsgViewer.h"

#include "Oge/OgeOsg/OsgCore/OsgModel.h"
#include "Oge/OgeOsg/OsgCore/OsgView.h"

#include "osg/MatrixTransform"

#include "osgUtil/SceneView"

using namespace Oge::OgeBase::OgeInterfaces;

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OsgViewer::OsgViewer( ViewerMode mode ) : 
        OgeBase::OgeCore::Viewer(), 
        osgViewer::Viewer       (), 
        _osgModel               ( new OsgModel() ), 
        _osgView                ( new OsgView( _osgModel.get() ) )
      { 
        _model = _osgModel.get();
        _view  = _osgView.get();
      }


      OsgViewer::~OsgViewer()
      {
      }


      OsgViewer::IUnknown* OsgViewer::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case IUnknown::IID :          
          default :
          {
            return 0x00;
          }
        };
      }


      void OsgViewer::init()
      {
        OgeBase::OgeCore::Viewer::init();
      }


      void OsgViewer::update()
      {
        OgeBase::OgeCore::Viewer::update();        
        
        _osgModel->rootNav()->setMatrix( osg::Matrix( _osgView->getCamera()->getMatrix() ) );
      }


      void OsgViewer::draw()
      { 
      }


      int OsgViewer::run()
      {
        if( _viewerMode = EMBEDDED )
        {
          this->frame();
        }
        {
          osgViewer::Viewer::run();
        }

        return 1;
      }


      void OsgViewer::setSceneData( osg::Node *sceneRoot )
      {        
        _osgModel->setSceneData( sceneRoot );
      }
    } 
  } 
} 
