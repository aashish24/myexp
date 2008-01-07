
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
          case gadget::Digital::TOGGLE_OFF : 
          {
            result = 0;
            break;
          }
          case gadget::Digital::TOGGLE_ON :
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
          case gadget::Digital::TOGGLE_ON : 
          {
            type = IEvent::KeyPress;
            break;
          }
          case gadget::Digital::TOGGLE_OFF : 
          {
            type = IEvent::KeyRelease;
            break;
          }
          case gadget::Digital::ON : 
          {
            type = IEvent::KeyDown;
            break;
          }
          case gadget::Digital::OFF : 
          {
            type = IEvent::KeyUp;
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
          case OgeBase::OgeInterfaces::IInputGetData< State >::IID :
          {
            return static_cast< OgeBase::OgeInterfaces::IInputGetData< gadget::Digital::State >* >( this );
          }
          default :
          {
            0x00;
          }
        };
      }
    }
  }
}
  
