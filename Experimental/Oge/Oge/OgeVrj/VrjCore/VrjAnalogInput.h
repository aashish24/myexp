
#ifndef __VRJ_CONTROLLER_VRJ_ANALOG_INPUT_H__
#define __VRJ_CONTROLLER_VRJ_ANALOG_INPUT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IEvent.h"
#include "Oge/OgeBase/OgeInterfaces/IInputGetData.h"

#include "Oge/OgeBase/OgeCore/Input.h"

#include "gadget/Type/AnalogInterface.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjCore
    {
      class OGE_EXPORT VrjAnalogInput : 
        public OgeBase::OgeCore::Input, 
        public OgeBase::OgeInterfaces::IInputGetData< float >
      {
        public: 

          OGE_DELCARE_SMART_PTR( VrjAnalogInput );          

          IMPLEMENT_IUNKNOWN_MEMBERS( VrjAnalogInput, Oge::OgeBase::OgeCore::Input );
          
          typedef OgeBase::OgeInterfaces::IEvent        IEvent;
          typedef OgeBase::OgeInterfaces::IUnknown      IUnknown;  
          
          VrjAnalogInput( const std::string& id, const std::string& proxy );
                  
          virtual void                                  init(); 

          virtual float                                 getData() const; 

          virtual bool                                  getDigitalData() const;

          virtual float                                 getAnalogData() const;

          virtual const float*                          getPositionalData() const;

          virtual IEvent::Type                           getEvent() const;

          IUnknown*                                     queryInterface( const unsigned long& iid );

        protected: 
          
          virtual ~VrjAnalogInput()
          {
          }

        private: 

          std::string                                   _proxy;

          gadget::AnalogInterface*                      _analogInterface;

      };
    }
  }
}
  
#endif // __VRJ_CONTROLLER_VRJ_ANALOG_INPUT_H__
