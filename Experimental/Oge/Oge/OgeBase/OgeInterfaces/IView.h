
#ifndef __OGE_INTERFACES_I_VIEW_H__
#define __OGE_INTERFACES_I_VIEW_H__

#include "Oge/OgeBase/OgeInterfaces/IObserver.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct ICamera;

      struct IView : public IObserver
      {
                              enum{ IID = 9514518190 };         

                              OGE_DELCARE_SMART_PTR( IView );

        virtual void          setCamera( ICamera* camera ) = 0;
        virtual ICamera*      getCamera( const unsigned int& index = 0 ) = 0;

        virtual void          addCamera( ICamera* camera ) = 0;

        virtual void          draw() = 0;
      };      
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge      

#endif // __OGE_INTERFACES_I_VIEW_H__
