
#ifndef __OGE_INTERFACES_I_OBSERVER_H__
#define __OGE_INTERFACES_I_OBSERVER_H__

#include "IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IObserver : public IUnknown
      {
        enum          { IID = 2535777544 };

                      OGE_DELCARE_SMART_PTR( IObserver );

        virtual void  update() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_OBSERVER_H__
