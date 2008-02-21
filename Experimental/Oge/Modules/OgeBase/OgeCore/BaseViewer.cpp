
#include "Oge/OgeBase/OgeCore/BaseViewer.h"

#include <algorithm>

using namespace Oge::OgeBase::OgeInterfaces;

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      BaseViewer::BaseViewer( int argc, char** argv ) :               
        OgeBase::OgeCore::Referenced(),       
        _inputDevices           (), 
        _interfaceContexts      ()

      { 
      }


      BaseViewer::~BaseViewer()
      {
      }


      BaseViewer::IUnknown* BaseViewer::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case IUnknown::IID :          
          case IBaseViewer::IID :
          {
            return static_cast< IBaseViewer* >( this );
          }
          default :
          {
            return 0x00;
          }
        };
      }

     
      void BaseViewer::init()
      {
        // Initialize all the devices attached.  
        std::map< const std::string, IInputDevice::RefPtr >::iterator itr;
        for( itr = _inputDevices.begin(); itr != _inputDevices.end(); ++itr )
        {
          itr->second->init();
        }        
      }


      void BaseViewer::update()
      {
        std::map< const std::string, IInputDevice::RefPtr >::iterator itr;
        for( itr = _inputDevices.begin(); itr != _inputDevices.end(); ++itr )
        {
          itr->second->update();
        }
      }
      
      void BaseViewer::addInputDevice( const std::string& deviceName, IInputDevice *inputDevice )
      {

        if( _inputDevices.find( deviceName ) == _inputDevices.end() )
        {
          _inputDevices[ deviceName ] = inputDevice;
        }
      }


      IInputDevice* BaseViewer::getInputDevice( const std::string& deviceName ) const
      {
        if( _inputDevices.find( deviceName ) != _inputDevices.end() )
        {
          return _inputDevices.find( deviceName )->second.get();
        }
        else
        {
          return 0x00;
        }
      }    


      // Lets config the interface context right now. We may have to think about when interface context 
      // will be confiigred. 
      void BaseViewer::addInterfaceContext( Oge::OgeBase::OgeInterfaces::IInterfaceContext *context)
      {
        if( context )
        {
          _interfaceContexts.push_back( context );
          context->config();
        }
      }


      BaseViewer::IInterfaceContext* BaseViewer::getInterfaceContext(const unsigned int &index) const
      {
        if( index < _interfaceContexts.size() )
        {
          return _interfaceContexts.at( index ).get();
        }
        else
        {
          return 0x00;
        }
      }
    } 
  } 
}
