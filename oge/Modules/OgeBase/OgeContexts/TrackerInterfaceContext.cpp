
#include "OgeBase/OgeContexts/TrackerInterfaceContext.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeContexts
    {
      // Start callback.
      struct PushStart : public OgeCore::InputCallback
      {
        PushStart( OgeInterfaces::IInputDevice*  inputDevice ) :
          _inputDevice( inputDevice )
        {
        }

        virtual void operator()( OgeInterfaces::IInput* input )
        {
	   std::cout << "[ Ready to take user inputs ]" << std::endl;
          _inputDevice->start();
        }

        OgeInterfaces::IInputDevice::RefPtr  _inputDevice;
      };


      // Camera move callback. 
      struct CameraMove : public OgeCore::InputCallback
      {
        CameraMove( OgeInterfaces::IViewer* viewer, OgeInterfaces::IInputDevice* inputDevice ) : 
          _viewer     ( viewer ),
          _inputDevice( inputDevice )
        {
          _wand = _inputDevice->getInput( OgeInterfaces::IInputDevice::Position, 1 );
        }

          
        virtual void operator()( OgeInterfaces::IInput* input )
        { 
          gmtl::Matrix44f mat;
          mat.set( _wand->getPositionData() );

          gmtl::Vec3f dir = mat * gmtl::Vec3f( 0.0, 1.0, 0.0 );
          
	  _viewer->getActiveCamera()->slide( dir[ 0 ], dir[ 1 ], dir[ 2 ] );          
        }


        OgeInterfaces::IViewer::RefPtr      _viewer;
        OgeInterfaces::IInputDevice::RefPtr _inputDevice;
        OgeInterfaces::IInput::RefPtr       _wand;        
      };


      // Camera yaw callback.
      struct CameraYaw : public OgeCore::InputCallback
      { 
        CameraYaw( OgeInterfaces::IViewer* viewer ) : 
          _viewer( viewer )
        {
        }


        virtual void operator()( OgeInterfaces::IInput* input )
        {
          // Flip of coordinate systems. 
          _viewer->getActiveCamera()->yaw( input->getAnalogData() );
        }
  
        OgeInterfaces::IViewer::RefPtr _viewer;
      };     


      // Camera pitch callback. 
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


        OgeInterfaces::IViewer::RefPtr _viewer;
      };     


      // Interface context for the tracker.   
      TrackerInterfaceContext::TrackerInterfaceContext( OgeBase::OgeInterfaces::IViewer *viewer, 
                                                        IInputDevice *inputDevice) :
        _navigateButtonIndex( 5 ),
        _viewer( viewer ), 
        _inputDevice( inputDevice )
      {       
      }


      void TrackerInterfaceContext::config()
      {
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > dInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > aInputCallbacks;
        std::vector< OgeBase::OgeInterfaces::IInputCallback::RefPtr > pInputCallbacks;

        CameraMove::RefPtr cmCallback ( new CameraMove( _viewer.get(), _inputDevice.get() ) );
        
        CameraYaw::RefPtr   cryCallback( new CameraYaw( _viewer.get() ) );
        CameraPitch::RefPtr crpCallback( new CameraPitch( _viewer.get() ) );

	PushStart::RefPtr   startCallback( new PushStart( _inputDevice.get() ) );		

        // Configuring each callback that corresponds to digital inputs now. 
        dInputCallbacks.push_back( startCallback.get() );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        dInputCallbacks.push_back( 0x00 );
        
        // 
        aInputCallbacks.push_back( cryCallback.get() );
        aInputCallbacks.push_back( crpCallback.get()  );
        

        // 
        pInputCallbacks.push_back( 0x00 );
        pInputCallbacks.push_back( 0x00 );

        // Digital. 
        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::Digital ); ++i ) 
        {
          if( i != ( _navigateButtonIndex  ) )
          {
            _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Digital, i )->addInputCallback
              ( OgeBase::OgeInterfaces::IEvent::KeyPress, dInputCallbacks[ i ].get(), false );
          }
          else
          {
            _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::Digital, i )->addInputCallback
              ( OgeBase::OgeInterfaces::IEvent::KeyDown, cmCallback.get(), false );
          }
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

