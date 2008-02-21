
#include "Oge/OgeBase/OgeCore/Event.h" 


namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      Event::Event( Type type ) : _type( type )
      {
      }
      
      
      Event::~Event()
      {
      }


      OgeBase::OgeInterfaces::IEvent::Type Event::type() const
      {
        return _type;
      }


      OgeBase::OgeInterfaces::IUnknown* Event::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID : 
          case OgeBase::OgeInterfaces::IEvent::IID : 
          {
            return static_cast< OgeBase::OgeInterfaces::IEvent* >( this );
          }
          default: 
          {
            return 0x00;
          }
        };
      }
    }
  }
}
