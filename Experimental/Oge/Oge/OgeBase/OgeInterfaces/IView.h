
#ifndef __OGE_INTERFACES_I_VIEW_H__
#define __OGE_INTERFACES_I_VIEW_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct ICamera;

      struct IView : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IView ); 

        enum                  { IID = 9514518190 };         

#if 0
        virtual void          setCamera( ICamera* camera ) = 0;
        virtual ICamera*      getCamera( const unsigned int& index = 0 ) = 0;

        virtual void          addCamera( ICamera* camera ) = 0;
#endif 
        virtual void          update() = 0;

        virtual void          draw() = 0;
      };      
    } 
  } 
} 

#endif // __OGE_INTERFACES_I_VIEW_H__
