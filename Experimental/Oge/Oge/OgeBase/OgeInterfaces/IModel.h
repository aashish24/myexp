
#ifndef __OGE_INTERFACES_I_MODEL_H__
#define __OGE_INTERFACES_I_MODEL_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    { 
      struct IView;

      struct IModel : public Oge::OgeBase::OgeInterfaces::IUnknown
      {
        OGE_DELCARE_SMART_PTR( IModel );

        enum          { IID = 8364633860 };

        virtual void  attach( IView* view ) = 0;
        
        virtual void  build()  = 0; 
        
        virtual void  update() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_MODEL_H__
