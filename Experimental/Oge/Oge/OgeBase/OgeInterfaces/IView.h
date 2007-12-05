
#ifndef 2
#define 2

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct ICamera;

      struct IView : public Oge::OgeBase::OgeInterfaces::IUnknown
      {
        OGE_DECLARE_SMART_PTR( IView ); 

        enum                  { IID = 9514518190 };         

        virtual void          setCamera( ICamera* camera ) = 0;
        virtual ICamera*      getCamera( const unsigned int& index = 0 ) = 0;

        virtual void          addCamera( ICamera* camera ) = 0;

        virtual void          draw() = 0;
      };      
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge      

#endif // 2
