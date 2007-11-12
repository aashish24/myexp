
#ifndef __I_MODEL_H__
#define __I_MODEL_H__

#include "IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IObserver;

      struct IModel : public IUnknown
      {
        enum { IID = 8364633860 };

        virtual void attach( IObserver* observer ) = 0;
        
        virtual void build()  = 0; 
        
        virtual void update() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_MODEL_H__
