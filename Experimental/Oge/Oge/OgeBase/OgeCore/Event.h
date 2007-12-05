
#ifndef __OGE_CORE_EVENT_H__
#define __OGE_CORE_EVENT_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IEvent.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/Pointer.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      typedef Oge::OgeBase::OgeInterfaces::IEvent::Type Type;

      struct OGE_EXPORT Event : 
        public Oge::OgeBase::OgeInterfaces::IEvent, 
        public Oge::OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( Event );


                            Event( Type type );       

        virtual Type        type() const;


        protected: 
          
          virtual          ~Event();


        protected: 
          
          Type             _type;
      };
    }
  }
}

#endif // __OGE_CORE_EVENT_H__
