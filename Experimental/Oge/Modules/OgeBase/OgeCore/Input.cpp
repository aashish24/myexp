
#include "Oge/OgeBase/OgeCore/Input.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      Input::Input( const std::string& id ) : 
        Referenced(), 
        _id( id ), 
        _callbacks()
      {
      }


      Input::~Input()
      {
      }


      OgeBase::OgeInterfaces::IUnknown* Input::queryInterface( const unsigned long &iid )
      {
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID :
          case OgeBase::OgeInterfaces::IInput::IID:
          {
            return static_cast< OgeBase::OgeInterfaces::IUnknown* >( this );
          }
          default:
          {
            return 0x00;
          }
        };
      }


      void Input::addInputCallback( OgeBase::OgeInterfaces::IEvent::Type type, 
                                    OgeBase::OgeInterfaces::IInputCallback* callback, 
                                    bool executeNext )
      { 
        _callbacks[ type ].push_back( Pair( executeNext, callback ) );        
      }


      void Input::setInputCallback( OgeBase::OgeInterfaces::IEvent::Type type, 
                                    OgeBase::OgeInterfaces::IInputCallback* callback, 
                                    bool executeNext )
      { 
      }


      void Input::call( IEvent::Type type )
      {
        Callbacks::iterator itr;
        for( itr = _callbacks.begin(); itr != _callbacks.end(); ++itr )
        {
          if( itr->first == type )
          {
            bool cont = true;
            std::vector< Pair >::iterator sItr = itr->second.begin();
            while( cont && ( sItr != itr->second.end() ) )
            { 
              cont = sItr->first;
              if( sItr->second.valid() )
              {
                sItr->second->operator ()( this );
              }
              ++sItr;
            }
          }
        }
      }
    }
  }
}
