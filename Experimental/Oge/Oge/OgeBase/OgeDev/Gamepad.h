
#ifndef __OGE_DEV_GAMEPAD_H__
#define __OGE_DEV_GAMEPAD_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/MemberFunctor.h"

#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeVrj/VrjCore/VrjDigitalInput.h"


#include <ostream>

namespace Oge
{
  namespace OgeBase
  {
    
    namespace OgeInterfaces
    {
      struct IUnknown; 
      struct IInput;        
    }

    namespace OgeDev
    { 
      class OGE_EXPORT Gamepad : 
        public Oge::OgeBase::OgeInterfaces::IInputDevice, 
        public Oge::OgeBase::OgeCore::Referenced
      {
        public:
                                                                
          OGE_DELCARE_SMART_PTR( Gamepad ); 

          IMPLEMENT_IUNKNOWN_MEMBERS( Gamepad, Oge::OgeBase::OgeCore::Referenced );

          typedef std::vector< OgeInterfaces::IInput::RefPtr >::iterator InputsItr;

          Gamepad();

          virtual void                                              init();

          virtual void                                              config( const std::string& config );

          virtual void                                              update();

          virtual OgeInterfaces::IInput*                            getInput( IInputDevice::InputType type, const unsigned int& index );

          virtual OgeInterfaces::IUnknown*                          queryInterface( const unsigned long& iid );

        
        protected: 
          
          virtual ~Gamepad();


        protected: 

          std::vector< OgeInterfaces::IInput::RefPtr >                _digitalInputs;
          std::vector< OgeInterfaces::IInput::RefPtr >                _analogInputs;
          std::vector< OgeInterfaces::IInput::RefPtr >                _positionalInputs;
      };
    }
  }
}

#endif // __OGE_DEV_GAMEPAD_H__
