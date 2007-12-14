
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
#include <string>

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
        
        IMPLEMENT_IUNKNOWN_MEMBERS( Input, Oge::OgeBase::OgeCore::Referenced );      

        typedef OgeInterfaces::IInputCallback               IInputCallback; 
        typedef OgeInterfaces::IEvent                       IEvent;         
        typedef OgeInterfaces::IEvent::Type                 Type;        
        typedef std::pair< bool, IInputCallback* >          Pair;
        typedef std::pair< Type, std::vector< Pair > >      BasePair;   

        typedef std::map< Type, std::vector < Pair > >      Callbacks;          

        Input( const std::string& id="", const std::string& proxy="", Callbacks& callbacks=Callbacks() );

        virtual void                                        addInputCallback( IEvent::Type type, 
                                                                              IInputCallback* callback, 
                                                                              bool executeNext= true );

        virtual void                                        setInputCallback( IEvent::Type type, 
                                                                              IInputCallback* callback, 
                                                                              bool executeNext= true );

        virtual void                                        call( IEvent::Type type );


        protected: 
          
          virtual                                           ~Input();


        protected:
        
          std::string                                       _id;

          std::string                                       _proxy;

          // Map of event to callbacks.           
          Callbacks                                         _callbacks;
      };
    }
  }
}

#endif // __OGE_CORE_INPUT_H__
