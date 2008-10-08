
#ifndef __OGE_DEV_GAMEPAD_H__
#define __OGE_DEV_GAMEPAD_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/MemberFunctor.h"

#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeVrj/VrjCore/VrjDigitalInput.h"


#include <ostream>

namespace Oge
{
  namespace OgeVrj
  {
    
    namespace OgeInterfaces
    {
      struct IUnknown; 
      struct IInput;        
    }

    namespace VrjDev
    { 
      class OGE_EXPORT Gamepad : 
        public Oge::OgeBase::OgeInterfaces::IInputDevice, 
        public Oge::OgeBase::OgeCore::Referenced
      {
        public:
                                                                
          OGE_DELCARE_SMART_PTR( Gamepad ); 

          IMPLEMENT_IUNKNOWN_MEMBERS( Gamepad, Oge::OgeBase::OgeCore::Referenced );

          typedef OgeBase::OgeInterfaces::IUnknown                  IUnknown;
          typedef OgeBase::OgeInterfaces::IInput                    IInput;
          typedef std::vector< IInput::RefPtr >                     IInputs;
          typedef IInputs::iterator                                 InputsItr;

          Gamepad( const unsigned int& digitalsCount  = 12, 
                   const unsigned int& analogsCount   = 6, 
                   const unsigned int& positionsCount = 0  );

          virtual void                                              init();

          virtual void                                              config( const std::string& config );

          virtual void                                              update();

          virtual OgeBase::OgeInterfaces::IInput*                   getInput( IInputDevice::InputType type, const unsigned int& index ) const;

          virtual IInputs&                                          getInputs( IInputDevice::InputType type );

          virtual unsigned int                                      getCount( IInputDevice::InputType type ) const;

          virtual IUnknown*                                         queryInterface( const unsigned long& iid );

          virtual void                                              start();

        
        protected: 
          
          virtual ~Gamepad();


        protected: 

          bool                                                      _start;

          IInputs                                                   _digitalInputs;
          IInputs                                                   _analogInputs;
          IInputs                                                   _positionInputs;
      };
    }
  }
}

#endif // __OGE_DEV_GAMEPAD_H__
