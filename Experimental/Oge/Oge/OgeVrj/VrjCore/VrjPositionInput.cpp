
#include "Oge/OgeVrj/VrjCore/VrjPositionInput.h"

namespace Oge
{ 
  namespace OgeVrj
  {
    namespace VrjCore
    {
      VrjPositionInput::VrjPositionInput( const std::string& id, 
                                              const std::string& proxy ) :
        OgeBase::OgeCore::Input ( id ),
        _proxy                  ( proxy ),
        _positionInterface      ( new gadget::PositionInterface() )
      {
        _id = id;
        _proxy = proxy;          
      }


      void VrjPositionInput::init()
      {
        _positionInterface->init( _proxy );
      }


      gmtl::Matrix44f VrjPositionInput::getData() const
      {        
        return ( *_positionInterface )->getData();
      }      


      bool VrjPositionInput::getDigitalData() const 
      {
        bool result( false );
        return result;
      }


      float VrjPositionInput::getAnalogData() const 
      {
        return 0.0;
      }


      const float* VrjPositionInput::getPositionalData() const
      {
        return ( *_positionInterface )->getData().mData;
      }


      OgeBase::OgeInterfaces::IEvent::Type VrjPositionInput::getEvent() const 
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


      OgeBase::OgeInterfaces::IUnknown* VrjPositionInput::queryInterface( const unsigned long& iid )
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
            return static_cast< OgeBase::OgeInterfaces::IInputGetData< gmtl::Matrix44f >* >( this );
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
  
