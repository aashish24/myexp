
#ifndef __TRACKER_INTERFACE_CONTEXT_H__
#define __TRACKER_INTERFACE_CONTEXT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/InputCallback.h"


#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInput.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"
#include "Oge/OgeBase/OgeInterfaces/IInterfaceContext.h"

#include "Oge/OgeBase/OgeCore/Camera.h"


namespace Oge
{
  namespace OgeBase
  {
    namespace OgeContexts 
    {     
      // We should be able to have multiple context active at the same time. 
      // Or able to switch between the contexts.. 
      // Also the question would be whether a context can handle more than 
      // one input device? I think 
      class TrackerInterfaceContext : 
        public OgeBase::OgeInterfaces::IInterfaceContext, 
        public OgeBase::OgeCore::Referenced
      {
        public: 
          
          OGE_DELCARE_SMART_PTR( TrackerInterfaceContext );
          
          IMPLEMENT_IUNKNOWN_MEMBERS( TrackerInterfaceContext, OgeBase::OgeCore::Referenced );
          
  
          typedef OgeBase::OgeInterfaces::IViewer       IViewer;
          typedef OgeBase::OgeInterfaces::IInputDevice  IInputDevice;
          typedef OgeBase::OgeInterfaces::ICamera       ICamera;

          TrackerInterfaceContext( IViewer* viewer, IInputDevice* inputDevice );

          virtual IUnknown* queryInterface( const unsigned long& iid ){ return 0x00; }

          virtual void config();

        private:

          unsigned int          _navigateButtonIndex;

          IViewer::RefPtr       _viewer;
          IInputDevice::RefPtr  _inputDevice;          
      };
    }
  }
}

#endif // __OGE_CONTROLLER_GAME_CONTROLLER_H__
