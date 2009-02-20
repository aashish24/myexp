
#include "OgeBase/OgeCore/InputCallback.h"

namespace Oge 
{
  namespace OgeBase 
  {  
    namespace OgeCore
    {
      OgeBase::OgeInterfaces::IUnknown* InputCallback::queryInterface( const unsigned long &iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID: 
          case OgeBase::OgeInterfaces::IInputCallback::IID: 
          {
            return static_cast< OgeBase::OgeInterfaces::IInputCallback* >( this );
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
