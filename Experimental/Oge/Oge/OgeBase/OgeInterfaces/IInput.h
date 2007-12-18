
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
      struct IInputCallback;
      
      struct IInput : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInput );

        enum                  { IID = 1237951858 };

        virtual void          init() = 0;    

        virtual IEvent::Type  getEvent() const = 0;

        // Generic ( not in terms of programming )...functions. 
        virtual bool          getDigitalData() const = 0;

        virtual float         getAnalogData() const = 0;

        virtual const float*  getPositionalData() const = 0;

        virtual void          addInputCallback( IEvent::Type eventType, IInputCallback* callback, bool executeNext ) = 0; 
        virtual void          setInputCallback( IEvent::Type eventType, IInputCallback* callback, bool executeNext ) = 0; 
       
        virtual void          call( IEvent::Type type ) = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_INPUT_H__
