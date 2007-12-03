
#ifndef __VRJ_CONTROLLER_VRJ_DIGITAL_INPUT_H__
#define __VRJ_CONTROLLER_VRJ_DIGITAL_INPUT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IEvent.h"
#include "Oge/OgeBase/OgeInterfaces/IInputData.h"

#include "Oge/OgeBase/OgeCore/Input.h"

#include "gadget/Type/DigitalInterface.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjController
    {
      namespace bi = Oge::OgeBase::OgeInterfaces;      
      namespace bc = Oge::OgeBase::OgeCore;

      typedef gadget::Digital::State                State;
      typedef OgeBase::OgeInterfaces::IEvent::Type  Type;
      typedef bi::IUnknown                          IUnknown;  

      class OGE_EXPORT VrjDigitalInput : 
        public bc::Input,
        public bi::IInputData< State >         
      {
        public: 

                                                    OGE_DELCARE_SMART_PTR( VrjDigitalInput );

                                                    VrjDigitalInput( const std::string& id, 
                                                                     const std::string& proxy );
                  
          virtual void                              init(); 

          virtual State                             getData() const; 

          virtual Type                              getEvent() const;

          virtual IUnknown*                         queryInterface( const unsigned long& iid );

        protected: 
          
          virtual ~VrjDigitalInput()
          {
          }

        private: 

          gadget::DigitalInterface*                _digitalInterface;

      };
    }
  }
}
  
#endif // __VRJ_CONTROLLER_VRJ_DIGITAL_INPUT_H__
