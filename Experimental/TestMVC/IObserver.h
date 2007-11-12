
#ifndef __I_OBSERVER_H__
#define __I_OBSERVER_H__

#include "IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IObserver : public IUnknown
      {
        enum { IID = 2535777544 };

        virtual void update() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_OBSERVER_H__
