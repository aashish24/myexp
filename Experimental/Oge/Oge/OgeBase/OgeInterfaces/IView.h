
#ifndef __OGE_INTERFACES_I_VIEW_H__
#define __OGE_INTERFACES_I_VIEW_H__

#include "IObserver.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IView : public IObserver 
      {
        enum{ IID = 9514518190 };         

        virtual void          draw() = 0;
      };      
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge      

#endif // __OGE_INTERFACES_I_VIEW_H__
