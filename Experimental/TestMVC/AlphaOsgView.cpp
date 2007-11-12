
#include "AlphaOsgView.h"

#include "IOsgModel.h"
#include "AlphaOsgModel.h"

using namespace Oge::OgeBase::OgeInterfaces;

namespace Oge
{
  namespace OgeOsg
  {
    namespace OgeOsgCore
    {
      AlphaOsgView::AlphaOsgView( Oge::OgeBase::OgeInterfaces::IOsgModel* model ) : 
        _model( model ), 
        _sceneView( new osgUtil::SceneView() )
      {
        if( _model )
        {
          _model->attach( this );
          _sceneView->setDefaults();
          _sceneView->setSceneData( _model->root() );
        }
      }

      IUnknown* AlphaOsgView::queryInterface( unsigned long iid )
      {
        switch( iid )
        {
          case IUnknown::IID :
          case IObserver::IID:
          {
            return static_cast< IObserver* >( this );
          }
          case IView::IID :
          {
            return static_cast< IView* >( this );
          }
          case IOsgView::IID :
          {
            return static_cast< IOsgView* >( this );
          }    
          default :
          {
            return 0x00;
          }
        };
      }

      osgUtil::SceneView* AlphaOsgView::sceneView()
      {
        return _sceneView;
      }

      void AlphaOsgView::update()
      {
        _sceneView->update();
      }

      void AlphaOsgView::draw()
      { 
        _sceneView->cull();
        _sceneView->draw();
      }
    } // namespace OgeOsgCore
  } // namespace OsgOsg
} // namespace Oge
