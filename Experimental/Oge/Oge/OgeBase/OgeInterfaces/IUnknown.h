
#ifndef __OGE_INTERFACES_I_UNKNOWN_H__
#define __OGE_INTERFACES_I_UNKNOWN_H__

#include "Oge/OgeBase/OgeCore/Pointer.h"
#include "Oge/OgeBase/OgeCore/Referenced.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IUnknown : public OgeCore::Referenced
      {
                          enum { IID = 3197031617 };

                          OGE_DELCARE_SMART_PTR( IUnknown );
        
        virtual IUnknown* queryInterface( const unsigned long& iid ) = 0;

        protected:
        
          virtual        ~IUnknown() {;}
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_UNKNOWN_H__
