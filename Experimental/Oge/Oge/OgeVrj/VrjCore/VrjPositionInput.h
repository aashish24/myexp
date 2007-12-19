
#ifndef __VRJ_CONTROLLER_VRJ_POSITIONAL_INPUT_H__
#define __VRJ_CONTROLLER_VRJ_POSITIONAL_INPUT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IEvent.h"
#include "Oge/OgeBase/OgeInterfaces/IInputGetData.h"

#include "Oge/OgeBase/OgeCore/Input.h"

#include "gadget/Type/PositionInterface.h"

#include "gmtl/Matrix.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjCore
    {
      

      class OGE_EXPORT VrjPositionInput : 
        public OgeBase::OgeCore::Input, 
        public OgeBase::OgeInterfaces::IInputGetData< gmtl::Matrix44f >
      {
        public: 

          OGE_DELCARE_SMART_PTR( VrjPositionInput );          

          IMPLEMENT_IUNKNOWN_MEMBERS( VrjPositionInput, Oge::OgeBase::OgeCore::Input );
          
          typedef OgeBase::OgeInterfaces::IEvent::Type  Type;
          typedef OgeBase::OgeInterfaces::IUnknown      IUnknown;            

          VrjPositionInput( const std::string& id, const std::string& proxy );
                  
          virtual void                                  init(); 

          virtual gmtl::Matrix44f                       getData() const; 

          virtual bool                                  getDigitalData() const;

          virtual float                                 getAnalogData() const;

          virtual const float*                          getPositionalData() const;

          virtual Type                                  getEvent() const;

          IUnknown*                                     queryInterface( const unsigned long& iid );

        protected: 
          
          virtual ~VrjPositionInput()
          {
          }

        private: 

          std::string                                   _proxy;

          gadget::PositionInterface*                    _positionInterface;

      };
    }
  }
}
  
#endif // __VRJ_CONTROLLER_VRJ_POSITIONAL_INPUT_H__
