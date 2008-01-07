
#include "Oge/OgeBase/OgeContexts/DefaultInterfaceContext.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeContexts
    {
      OgeInterfaces::ICamera::RefPtr ActiveCamera::_camera = 0x00;

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
            ActiveCamera::getActiveCamera()->slide( input->getAnalogData(), 0.0, 0.0 );
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
            ActiveCamera::getActiveCamera()->slide( 0.0, input->getAnalogData(), 0.0 );
          }
        }
      };


      struct CameraMoveZ : public OgeCore::InputCallback
      {
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          ActiveCamera::getActiveCamera()->slide( 0.0, 0.0, input->getAnalogData() );
        }
      };


      struct CameraYaw : public OgeCore::InputCallback
      { 
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          // Flip of coordinate systems. 
          ActiveCamera::getActiveCamera()->yaw( input->getAnalogData() );
        }
      };     


      struct CameraPitch : public OgeCore::InputCallback
      { 
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          ActiveCamera::getActiveCamera()->pitch( input->getAnalogData() );
        }
      };     


      DefaultInterfaceContext::DefaultInterfaceContext( OgeBase::OgeInterfaces::IViewer *viewer, 
                                                        IInputDevice *inputDevice) :
        _viewer( viewer ), 
        _inputDevice( inputDevice )
      {
        _camera = _viewer->getActiveCamera();
      }


      void DefaultInterfaceContext::config()
      {
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > dInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > aInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > pInputCallbacks;

        ActiveCamera::setActiveCamera( _camera.get() );

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
        dInputCallbacks.push_back( 0x00 );
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

