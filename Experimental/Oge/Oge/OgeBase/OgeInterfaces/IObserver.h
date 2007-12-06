
#ifndef __OGE_INTERFACES_I_OBSERVER_H__
#define __OGE_INTERFACES_I_OBSERVER_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IObserver : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IObserver );

        enum          { IID = 2535777544 };

        virtual void  update() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_OBSERVER_H__
