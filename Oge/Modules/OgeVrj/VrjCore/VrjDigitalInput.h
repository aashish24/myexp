
#ifndef __VRJ_CONTROLLER_VRJ_DIGITAL_INPUT_H__
#define __VRJ_CONTROLLER_VRJ_DIGITAL_INPUT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IEvent.h"
#include "Oge/OgeBase/OgeInterfaces/IInputGetData.h"

#include "Oge/OgeBase/OgeCore/Input.h"

#include "gadget/Type/DigitalInterface.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjCore
    {
      class OGE_EXPORT VrjDigitalInput : 
        public OgeBase::OgeCore::Input, 
        public OgeBase::OgeInterfaces::IInputGetData< gadget::Digital::State >
      {
        public: 

          OGE_DELCARE_SMART_PTR( VrjDigitalInput );          

          IMPLEMENT_IUNKNOWN_MEMBERS( VrjDigitalInput, Oge::OgeBase::OgeCore::Input );
          
          typedef OgeBase::OgeInterfaces::IEvent        IEvent;
          typedef OgeBase::OgeInterfaces::IUnknown      IUnknown;  
          typedef gadget::Digital::State                State;

          VrjDigitalInput( const std::string& id, const std::string& proxy );
                  
          virtual void                                  init(); 

          virtual State                                 getData() const; 

          virtual bool                                  getDigitalData() const;

          virtual float                                 getAnalogData() const;

          virtual float*                                getPositionData() const;

          virtual IEvent::Type                          getEvent() const;

          IUnknown*                                     queryInterface( const unsigned long& iid );


        protected: 
          
          virtual ~VrjDigitalInput()
          {
          }

        private: 

          std::string                                   _proxy;

          gadget::DigitalInterface*                     _digitalInterface;

      };
    }
  }
}
  
#endif // __VRJ_CONTROLLER_VRJ_DIGITAL_INPUT_H__
