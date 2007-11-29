
#ifndef __OGE_INTERFACES_I_FUNCTOR_H__
#define __OGE_INTERFACES_I_FUNCTOR_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      struct IFunctor : public IUnknown
      {
        virtual void operator()( )  = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_FUNCTOR_H__
