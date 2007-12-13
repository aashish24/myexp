
#ifndef __OGE_INTERFACES_I_INPUT_GET_DATA_H__
#define __OGE_INTERFACES_I_INPUT_GET_DATA_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

#include "Oge/OgeBase/OgeInterfaces/IEvent.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    { 
      template< typename DataType >
      struct IInputGetData : public OgeBase::OgeInterfaces::IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInputGetData );

        enum                  { IID = 0222 };

        virtual DataType      getData() const = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_INPUT_GET_DATA_H__
