
#ifndef __I_INPUT_CALLBACK_H__
#define __I_INPUT_CALLBACK_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IInput;

      struct IInputCallback : public OgeBase::OgeInterfaces::IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInputCallback );

        virtual void operator()( IInput* ) = 0;
      };
    }
  }
}

#endif // __I_INPUT_CALLBACK_H__