
#include "Oge/OgeBase/OgeContexts/GamepadInterfaceContext.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeContexts
    {
      // Start callback. 
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

      
      // Camera move in x axis callback. 
      struct CameraMoveX : public OgeCore::InputCallback
      {
        CameraMoveX( OgeInterfaces::IViewer* viewer ) :
          _viewer( viewer )
        {
        }


        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _viewer->getActiveCamera()->slide( input->getAnalogData(), 0.0, 0.0 );
        }


        OgeInterfaces::IViewer::RefPtr  _viewer;
      };


      // Camera move in Y axis callback.
      struct CameraMoveY : public OgeCore::InputCallback
      {
        CameraMoveY( OgeInterfaces::IViewer* viewer ) :
          _viewer( viewer )
        {
        }


        virtual void operator()( OgeInterfaces::IInput* input )
        {
         _viewer->getActiveCamera()->slide( 0.0, input->getAnalogData(), 0.0 );
        }


        OgeInterfaces::IViewer::RefPtr  _viewer;
      };


      struct CameraMoveZ : public OgeCore::InputCallback
      {
        CameraMoveZ( OgeInterfaces::IViewer* viewer ) :
          _viewer( viewer )
        {
        }


        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _viewer->getActiveCamera()->slide( 0.0, 0.0, input->getAnalogData() );
        }


        OgeInterfaces::IViewer::RefPtr  _viewer;
      };


      struct CameraYaw : public OgeCore::InputCallback
      { 
        CameraYaw( OgeInterfaces::IViewer* viewer ) :
          _viewer( viewer )
        {
        }


        virtual void operator()( OgeInterfaces::IInput* input )
        {          
          _viewer->getActiveCamera()->yaw( input->getAnalogData() );
        }


        OgeInterfaces::IViewer::RefPtr  _viewer;
      };     


      struct CameraPitch : public OgeCore::InputCallback
      { 
        CameraPitch( OgeInterfaces::IViewer* viewer ) :
          _viewer( viewer )
        {
        }


        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _viewer->getActiveCamera()->pitch( input->getAnalogData() );
        }


        OgeInterfaces::IViewer::RefPtr  _viewer;
      };     


      GamepadInterfaceContext::GamepadInterfaceContext( OgeBase::OgeInterfaces::IViewer *viewer, 
                                                        IInputDevice *inputDevice) :
        _viewer( viewer ), 
        _inputDevice( inputDevice )
      {        
      }


      void GamepadInterfaceContext::config()
      {
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > dInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > aInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > pInputCallbacks;        

        CameraMoveX::RefPtr cmxCallback ( new CameraMoveX( _viewer.get() ) );
        CameraMoveY::RefPtr cmyCallback ( new CameraMoveY( _viewer.get() ) );
        CameraMoveZ::RefPtr cmzCallback ( new CameraMoveZ( _viewer.get() ) );

        CameraYaw::RefPtr   cryCallback( new CameraYaw( _viewer.get() ) );
        CameraPitch::RefPtr crpCallback( new CameraPitch( _viewer.get() ) );

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

