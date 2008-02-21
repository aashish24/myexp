
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
        public OgeBase::OgeInterfaces::IInput,
        public OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( Input ); 
        
        IMPLEMENT_IUNKNOWN_MEMBERS( Input, OgeBase::OgeCore::Referenced );      

        typedef OgeBase::OgeInterfaces::IUnknown            IUnknown;
        typedef OgeBase::OgeInterfaces::IInputCallback      IInputCallback; 
        typedef OgeBase::OgeInterfaces::IEvent              IEvent;         
        typedef OgeBase::OgeInterfaces::IEvent::Type        Type;        

        typedef std::pair< bool, IInputCallback::RefPtr >   Pair;
        typedef std::pair< Type, std::vector< Pair > >      BasePair;   
        typedef std::map< Type, std::vector < Pair > >      Callbacks;          

        Input( const std::string& id="" );

        virtual IUnknown*                                   queryInterface( const unsigned long& iid );

        virtual void                                        addInputCallback( IEvent::Type type, 
                                                                              IInputCallback* callback, 
                                                                              bool executeNext= true );

        virtual void                                        setInputCallback( IEvent::Type type, 
                                                                              IInputCallback* callback, 
                                                                              bool executeNext= true );

        virtual void                                        call( IEvent::Type type );


        protected: 
          
          virtual ~Input();


        protected:
        
          std::string                                       _id;
          Callbacks                                         _callbacks;
      };
    }
  }
}

#endif // __OGE_CORE_INPUT_H__
