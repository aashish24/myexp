
#ifndef __OGE_INTERFACES_I_VIEWER_H__
#define __OGE_INTERFACES_I_VIEWER_H__

#include "OgeBase/OgeInterfaces/IUnknown.h"

#include <string>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    { 
      struct IView;
      struct IInputDevice;
      struct ICamera;
      struct IInterfaceContext;

      /////////////////////////////////////////////////////////////////////////
      //
      // We should have some interface for event handling here. 
      // Also how the user would have to set whether or not this viewer is embedded 
      // in an external window in the constrcutor. We could provide some interface 
      // later but for now lets keep it simple. 
      //
      ///////////////////////////////////////////////////////////////////////

      struct IViewer : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IViewer );

        enum                        { IID = 3027178794 };

        enum                        Mode{ REGULAR = 0, EMBEDDED = 1 };                

        virtual void                readConfig( const std::string& config ) = 0;

        virtual void                init() = 0;

        virtual void                contextInit() = 0;         

        virtual void                update() = 0; 

        virtual void                draw()= 0; 

        virtual int                 run() = 0;

        virtual IView*              getView() const = 0;

        virtual ICamera*            getActiveCamera() const = 0;        
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_VIEWER_H__
