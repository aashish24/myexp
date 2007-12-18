
#include "Oge/OgeBase/OgeCore/View.h" 

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


      OgeBase::OgeInterfaces::IUnknown* View::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID :
          case OgeBase::OgeInterfaces::IView::IID :
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


      void View::draw()
      {
      }
    } 
  } 
} 
