
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

      struct IInputCallback : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInputCallback );

        enum                  { IID = 2961639404 };

        virtual void          operator()( IInput* ) = 0;
      };
    }
  }
}

#endif // __I_INPUT_CALLBACK_H__