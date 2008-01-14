
#include "Oge/OgeBase/OgeContexts/GamepadInterfaceContext.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeContexts
    {
      OgeInterfaces::ICamera::RefPtr GamepadActiveCamera::_gamepadCamera = 0x00;


      struct Start : public OgeCore::InputCallback
      {
        Start( OgeInterfaces::IInputDevice*  inputDevice ) :
          _inputDevice( inputDevice )
        {
        }

        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _inputDevice->start();
        }

        OgeInterfaces::IInputDevice::RefPtr  _inputDevice;
      };


      struct CameraMoveX : public OgeCore::InputCallback
      {
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          // Is this callback used by a digital input? 
          if( input->getAnalogData() == 0.0 )
          {
            // Don't do anything. 
          }
          else
          {
            GamepadActiveCamera::getActiveCamera()->slide( input->getAnalogData(), 0.0, 0.0 );
          }
        }
      };


      struct CameraMoveY : public OgeCore::InputCallback
      {
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          // Is this callback used by a digital input? 
          if( input->getAnalogData() == 0.0 )
          {
            // Don't do anything. 
          }
          else
          {
            GamepadActiveCamera::getActiveCamera()->slide( 0.0, input->getAnalogData(), 0.0 );
          }
        }
      };


      struct CameraMoveZ : public OgeCore::InputCallback
      {
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          GamepadActiveCamera::getActiveCamera()->slide( 0.0, 0.0, input->getAnalogData() );
        }
      };


      struct CameraYaw : public OgeCore::InputCallback
      { 
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          // Flip of coordinate systems. 
          GamepadActiveCamera::getActiveCamera()->yaw( input->getAnalogData() );
        }
      };     


      struct CameraPitch : public OgeCore::InputCallback
      { 
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          GamepadActiveCamera::getActiveCamera()->pitch( input->getAnalogData() );
        }
      };     


      GamepadInterfaceContext::GamepadInterfaceContext( OgeBase::OgeInterfaces::IViewer *viewer, 
                                                        IInputDevice *inputDevice) :
        _viewer( viewer ), 
        _inputDevice( inputDevice )
      {
        _camera = _viewer->getActiveCamera();
      }


      void GamepadInterfaceContext::config()
      {
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > dInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > aInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > pInputCallbacks;

        GamepadActiveCamera::setActiveCamera( _camera.get() );

        CameraMoveX::RefPtr cmxCallback ( new CameraMoveX() );
        CameraMoveY::RefPtr cmyCallback ( new CameraMoveY() );
        CameraMoveZ::RefPtr cmzCallback ( new CameraMoveZ() );

        CameraYaw::RefPtr   cryCallback( new CameraYaw() );
        CameraPitch::RefPtr crpCallback( new CameraPitch() );

        // Configuring each callback that corresponds to digital inputs now. 
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );

        // Assuming we are using button no 10 to start. 
        dInputCallbacks.push_back( new Start( _inputDevice.get() ) ) ;

        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );

        aInputCallbacks.push_back( cryCallback.get() );
        aInputCallbacks.push_back( crpCallback.get()  );
        aInputCallbacks.push_back( cmxCallback.get() );
        aInputCallbacks.push_back( cmzCallback.get() );     
        aInputCallbacks.push_back( 0x00 );
        aInputCallbacks.push_back( 0x00 );


        // Digital. 
        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Digital ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Digital, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::KeyPress, dInputCallbacks[ i ].get(), false );
        }

        // Analog. 
        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Analog ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Analog, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::JoystickTilt, aInputCallbacks[ i ].get(), false );
        }

        // Position. 
        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Position ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Position, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::KeyPress, pInputCallbacks[ i ].get(), false );
        }
      }
    }
  }
}

