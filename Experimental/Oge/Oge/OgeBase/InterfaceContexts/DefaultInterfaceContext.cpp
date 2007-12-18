
#include "Oge/OgeBase/InterfaceContexts/DefaultInterfaceContext.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace InterfaceContexts
    {
      struct CameraMoveForward : public OgeCore::InputCallback
      {
        CameraMoveForward( OgeInterfaces::ICamera* camera ) : 
          _camera( camera ) 
        {
        }
        
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _camera->move( -1.0 );
        }

        OgeInterfaces::ICamera::RefPtr _camera;
      };


      struct CameraMoveBackward : public OgeCore::InputCallback
      {
        CameraMoveBackward( OgeInterfaces::ICamera* camera ) : 
          _camera( camera ) 
        {
        }
        
        virtual void operator()( OgeInterfaces::IInput* input )
        {
          _camera->move( 1.0 );
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

        // Configuring each callback that corresponds to digital inputs now. 
        dInputCallbacks.push_back( new CameraMoveForward( _camera.get() ) );
        dInputCallbacks.push_back( new CameraMoveBackward( _camera.get() ) );

        for( size_t i = 0; i < _inputDevice->getCount( OgeBase::OgeInterfaces::IInputDevice::DIGITAL ); ++i ) 
        {
          _inputDevice->getInput( OgeBase::OgeInterfaces::IInputDevice::DIGITAL, i )->addInputCallback
            ( OgeBase::OgeInterfaces::IEvent::KeyPress, dInputCallbacks[ i ].get(), false );
        }
      }
    }
  }
}

