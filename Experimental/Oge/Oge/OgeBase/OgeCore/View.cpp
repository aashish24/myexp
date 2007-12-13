
#include "Oge/OgeBase/OgeCore/View.h" 

#include "Oge/OgeBase/OgeInterfaces/ICamera.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      View::View( Oge::OgeBase::OgeInterfaces::IModel* model ) : 
        _model( model )
      {
        if( _model.valid() )
        {
          _model->attach( this );
        }
      }


      View::~View()
      {
      }


      View::IUnknown* View::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case IUnknown::IID :
          case IView::IID :
          {
            return static_cast< IView* >( this );
          }   
          default :
          {
            return 0x00;
          }
        };
      }
      

      void View::update()
      { 
      }

#if 0
      void View::setCamera( View::ICamera* camera )
      {
        if( camera && camera != _masterCamera.get() && 
            ( std::find( _cameraLists.begin(), _cameraLists.end(), camera ) == _cameraLists.end() ) )
        {
          _cameraLists.push_back( camera );
          _masterCamera = camera;
        }
      }


      View::ICamera* View::getCamera( const unsigned int& index )
      {
        if( index < _cameraLists.size() )
        {
          return _cameraLists[ index ].get();
        }
        else
        {
          addCamera( new Camera() );
          return _cameraLists.back().get();
        }
      }


      void View::addCamera( View::ICamera* camera ) 
      {
        if( camera && camera != _masterCamera.get() && 
          std::find( _cameraLists.begin(), _cameraLists.end(), camera ) == _cameraLists.end() )
        {
          _cameraLists.push_back( camera );
        }
      }
#endif 

      void View::draw()
      {
      }
    } 
  } 
} 
