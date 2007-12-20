
#include "Oge/OgeBase/InterfaceContexts/DefaultInterfaceContext.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace InterfaceContexts
    {
      struct CameraMove : public OgeCore::InputCallback
      {
        CameraMove( OgeInterfaces::ICamera* camera ) : 
          _camera( camera ) 
        {
        }
        
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          // Is this callback used by a digital input? 
          if( input->getAnalogData() == 0.0 )
          {
            //_camera->move( -1.0 );
          }
          else
          {
            _camera->move( input->getAnalogData() * 0.1 );
          }
        }

        OgeInterfaces::ICamera::RefPtr _camera;
      };


      struct CameraRotatePos : public OgeCore::InputCallback
      { 
        CameraRotatePos( OgeInterfaces::ICamera* camera ) : 
          _camera( camera ) 
        {
        }
        
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _camera->rotateView( input->getAnalogData() * 0.01 );
        }

        OgeInterfaces::ICamera::RefPtr _camera;
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

        CameraMove::RefPtr cmCallback ( new CameraMove( _camera.get()  ) );
        CameraMove::RefPtr crpCallback( new CameraRotatePos( _camera.get() ) );

        // Configuring each callback that corresponds to digital inputs now. 
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );
        dInputCallbacks.push_back( cmCallback.get() );

        aInputCallbacks.push_back( 0x00 );
        aInputCallbacks.push_back( crpCallback.get()  );
        aInputCallbacks.push_back( 0x00 );
        aInputCallbacks.push_back( cmCallback.get() );     
        aInputCallbacks.push_back( 0x00 );
        aInputCallbacks.push_back( 0x00 );


        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Digital ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Digital, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::KeyPress, dInputCallbacks[ i ].get(), false );
        }

        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Analog ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Analog, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::JoystickTilt, aInputCallbacks[ i ].get(), false );
        }

        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Position ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Position, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::KeyPress, pInputCallbacks[ i ].get(), false );
        }
      }
    }
  }
}

