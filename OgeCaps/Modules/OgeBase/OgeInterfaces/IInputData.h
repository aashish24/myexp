
#ifndef __I_INPUT_DATA_H__
#define __I_INPUT_DATA_H__

#include "OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      template< typename T >
      struct IInputData : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInputData );

        enum      { IID = 0 };

        virtual T getData() const = 0;
      };
    }
  }
}

#endif // __I_INPUT_DATA_H__
