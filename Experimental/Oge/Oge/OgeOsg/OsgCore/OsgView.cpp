
#include "Oge/OgeBase/OgeInterfaces/IOsgModel.h"
#include "Oge/OgeBase/OgeInterfaces/ICamera.h"

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

        _model->rootNav()->asTransform()->asMatrixTransform()->setMatrix( osg::Matrix( getCamera()->getMatrix() ) );
      }


      void OsgView::setCamera( OsgView::ICamera* camera )
      {
        if( camera )
        {
          _cameras.clear();
          _cameras.push_back( camera );
        }
      }


      OsgView::ICamera* OsgView::getCamera( const unsigned int& index )
      {
        if( index < _cameras.size() )
        {
          return _cameras[ index ].get();
        }
        else
        {
          _cameras.push_back( new Camera() );
          return _cameras[ 0 ].get();
        }
      }


      void OsgView::addCamera( OsgView::ICamera* camera ) 
      {
        if( camera )
        {
          _cameras.push_back( camera );
        }
      }


      void OsgView::draw()
      { 
        _sceneView->cull();
        _sceneView->draw();
      }
    } // namespace OsgCore
  } // namespace OsgOsg
} // namespace Oge
