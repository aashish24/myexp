
#include "Oge/OgeBase/OgeInterfaces/IOsgModel.h"

#include "Oge/OgeOsg/OsgCore/OsgModel.h"
#include "Oge/OgeOsg/OsgCore/OsgView.h"

#include "osgUtil/SceneView"

using namespace Oge::OgeBase::OgeInterfaces;

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OsgView::OsgView( Oge::OgeBase::OgeInterfaces::IOsgModel* model ) : 
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


      OsgView::~OsgView()
      {
      }

      OsgView::IUnknown* OsgView::queryInterface( const unsigned long& iid )
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

      osgUtil::SceneView* OsgView::sceneView()
      {
        return _sceneView;
      }

      IOsgModel* OsgView::getModel()
      {
        return _model;
      }


      void OsgView::setModel( IOsgModel* model )
      {
        // Todo: Implement this. 
      }

      void OsgView::update()
      {
        _sceneView->update();
      }

      void OsgView::draw()
      { 
        _sceneView->cull();
        _sceneView->draw();
      }
    } // namespace OsgCore
  } // namespace OsgOsg
} // namespace Oge
