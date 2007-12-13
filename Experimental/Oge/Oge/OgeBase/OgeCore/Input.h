
#ifndef __OGE_CORE_INPUT_H__
#define __OGE_CORE_INPUT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IInputCallback.h"
#include "Oge/OgeBase/OgeInterfaces/IInput.h"
#include "Oge/OgeBase/OgeInterfaces/IEvent.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/Pointer.h"

#include <vector>
#include <map>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    { 
      struct OGE_EXPORT Input : 
        public OgeInterfaces::IInput,
        public Oge::OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( Input ); 
        
              

        typedef OgeInterfaces::IInputCallback               IInputCallback; 
        typedef OgeInterfaces::IEvent                       IEvent;         
        typedef OgeInterfaces::IEvent::Type                 Type;        
        typedef std::pair< bool, IInputCallback* >          Pair;
        typedef std::pair< Type, std::vector< Pair > >      BasePair;   

        typedef std::map< Type, std::vector < Pair > >      Callbacks;          

        virtual void ref()
        {
          OgeBase::OgeCore::Referenced::ref();
        }


        virtual void unref()
        {
          OgeBase::OgeCore::Referenced::unref();
        }


        virtual void unrefDoNotDelete()
        {
          OgeBase::OgeCore::Referenced::unrefDoNotDelete();
        }


        virtual void addActionCallback( IEvent::Type type, IInputCallback* callback, bool executeNext= true )
        {        
          //_callbacks.insert( BasePair( type, Pair( executeNext, ftor ) ) );
          _callbacks[ type ].push_back( Pair( executeNext, callback ) );
        }


        virtual void setActionCallback( IEvent::Type type, IInputCallback* callback, bool executeNext= true )
        {
          /*_callbacks.clear();
          _callbacks.insert( Pair( executeNext, ftor ) ):*/
        }


        virtual void call( IEvent::Type type )
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
                sItr->second->operator ()( this );
                ++sItr;
              }
            }
          }
        }

        protected: 
          
          virtual ~Input()
          {
          }

        protected:
        
          std::string         _id;

          std::string         _proxy;

          // Map of event to callbacks.           
          Callbacks           _callbacks;
      };
    }
  }
}

#endif // __OGE_CORE_INPUT_H__
