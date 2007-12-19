

#include "Oge/OgeVrj/VrjCore/VrjAnalogInput.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjCore
    {
      VrjAnalogInput::VrjAnalogInput( const std::string& id, 
                                      const std::string& proxy ) :
        OgeBase::OgeCore::Input( id ),
        _proxy( proxy ),
        _analogInterface( new gadget::AnalogInterface() )
      {
        _id = id;
        _proxy = proxy;          
      }


      void VrjAnalogInput::init()
      {
        _analogInterface->init( _proxy );
      }


      float VrjAnalogInput::getData() const
      {        
        return ( *_analogInterface )->getData();
      }      


      bool VrjAnalogInput::getDigitalData() const 
      {
        bool result( false );
        
        if( ( *_analogInterface )->getData() != 0.0 )
        {
          result = true;
        }
        
        return result;
      }


      float VrjAnalogInput::getAnalogData() const 
      {
        return ( *_analogInterface )->getData();
      }


      const float* VrjAnalogInput::getPositionalData() const
      {
        return 0x00;
      }


      OgeBase::OgeInterfaces::IEvent::Type VrjAnalogInput::getEvent() const 
      {
        IEvent::Type type( IEvent::None );

        switch( this->getDigitalData() )
        {
          case 0 : 
          {
            type = IEvent::Type::KeyUp;
            break;
          }
          case 1 : 
          {
            type = IEvent::Type::KeyDown;
            break;
          }
        };
        
        return type;
      }


      OgeBase::OgeInterfaces::IUnknown* VrjAnalogInput::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID :          
          case OgeBase::OgeInterfaces::IInput::IID:
          {
            return OgeBase::OgeCore::Input::queryInterface( iid );
          }
          case OgeBase::OgeInterfaces::IInputGetData< float >::IID :
          {
            return static_cast< OgeBase::OgeInterfaces::IInputGetData< float >* >( this );
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
  
