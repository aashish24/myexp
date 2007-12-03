
#ifndef __OGE_INTERFACES_I_INPUT_H__
#define __OGE_INTERFACES_I_INPUT_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IEvent.h"
namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {      
      struct IEvent; 
      struct IFunctor;
      
      // May be instead of event we call it state. 
      struct IInput : public IUnknown
      {
                              OGE_DELCARE_SMART_PTR( IInput );

        virtual void          init() = 0;                      
        virtual IEvent::Type  getEvent() const = 0;

        virtual void          addActionCallback( IEvent::Type eventType, IFunctor* ftor, bool executeNext ) = 0; 
        virtual void          setActionCallback( IEvent::Type eventType, IFunctor* ftor, bool executeNext ) = 0; 
       
        virtual void          call( IEvent::Type type ) = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_INPUT_H__
