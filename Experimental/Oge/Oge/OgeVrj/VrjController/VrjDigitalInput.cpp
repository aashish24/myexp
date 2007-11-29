
#include "Oge/OgeVrj/VrjController/VrjDigitalInput.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjController
    {
      VrjDigitalInput::VrjDigitalInput( const std::string& id, 
        const std::string& proxy ) :
      _digitalInterface( new gadget::DigitalInterface() )
      {
        _id = id;
        _proxy = proxy;          
      }

      void VrjDigitalInput::init()
      {
        _digitalInterface->init( _proxy );
      }


      State VrjDigitalInput::getData() const
      {        
        return (*_digitalInterface)->getData();
      }      


      Type VrjDigitalInput::getEvent() const 
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

      IUnknown* VrjDigitalInput::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }
    }
  }
}
  
