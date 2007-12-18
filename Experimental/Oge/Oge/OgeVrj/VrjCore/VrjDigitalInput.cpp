
#include "Oge/OgeVrj/VrjCore/VrjDigitalInput.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjCore
    {
      VrjDigitalInput::VrjDigitalInput( const std::string& id, 
        const std::string& proxy ) :
        OgeBase::OgeCore::Input( id ),
        _proxy( proxy ),
        _digitalInterface( new gadget::DigitalInterface() )
      {
        _id = id;
        _proxy = proxy;          
      }


      void VrjDigitalInput::init()
      {
        _digitalInterface->init( _proxy );
      }


      gadget::Digital::State VrjDigitalInput::getData() const
      {        
        return (*_digitalInterface)->getData();
      }      


      bool VrjDigitalInput::getDigitalData() const 
      {
        bool result;

        switch( this->getData() )
        {
          case State::TOGGLE_OFF : 
          {
            result = 0;
            break;
          }
          case State::TOGGLE_ON :
          {
            result = 1;
            break;
          }          
        };

        return result;
      }


      float VrjDigitalInput::getAnalogData() const 
      {
        return 0.0f;
      }


      const float* VrjDigitalInput::getPositionalData() const
      {
        return 0x00;
      }


      OgeBase::OgeInterfaces::IEvent::Type VrjDigitalInput::getEvent() const 
      {
        IEvent::Type type( IEvent::None );

        switch( getData() )
        {
          case State::TOGGLE_ON : 
          {
            type = IEvent::Type::KeyPress;
            break;
          }
          case State::TOGGLE_OFF : 
          {
            type = IEvent::Type::KeyRelease;
            break;
          }
          case State::ON : 
          {
            type = IEvent::Type::KeyDown;
            break;
          }
          case State::OFF : 
          {
            type = IEvent::Type::KeyUp;
            break;
          }
        };
        
        return type;
      }

      
      OgeBase::OgeInterfaces::IUnknown* VrjDigitalInput::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID :          
          case OgeBase::OgeInterfaces::IInput::IID:
          {
            return OgeBase::OgeCore::Input::queryInterface( iid );
          }
          case OgeBase::OgeInterfaces::IInputGetData::IID :
          {
            return static_cast< OgeBase::OgeInterfaces::IInputGetData< gadget::Digital::State >* >( this );
          }
          default
          {
            0x00;
          }
        };
    }
  }
}
  
