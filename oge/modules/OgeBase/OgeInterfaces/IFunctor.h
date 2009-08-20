
#ifndef __OGE_INTERFACES_I_FUNCTOR_H__
#define __OGE_INTERFACES_I_FUNCTOR_H__

#include "OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      struct IFunctor : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IFunctor );

        enum          { IID = 1822840908 };

        virtual void  operator()( )  = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_FUNCTOR_H__
