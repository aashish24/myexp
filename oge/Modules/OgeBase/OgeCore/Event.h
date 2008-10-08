
#ifndef __OGE_CORE_EVENT_H__
#define __OGE_CORE_EVENT_H__

#include "OgeBase/Export.h"

#include "OgeBase/OgeInterfaces/IEvent.h"

#include "OgeBase/OgeCore/Referenced.h"
#include "OgeBase/OgeCore/Pointer.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      struct OGE_BASE_EXPORT Event : public OgeBase::OgeInterfaces::IEvent, 
                                public OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( Event );

        IMPLEMENT_IUNKNOWN_MEMBERS( Event, OgeBase::OgeCore::Referenced );

        typedef OgeBase::OgeInterfaces::IEvent    IEvent;
        typedef OgeBase::OgeInterfaces::IUnknown  IUnknown;

        Event( IEvent::Type type );       

        virtual IEvent::Type                      type() const;

        virtual IUnknown*                         queryInterface( const unsigned long& iid );

        protected: 
          
          virtual ~Event();


        protected: 
          
          Type                                    _type;
      };
    }
  }
}

#endif // __OGE_CORE_EVENT_H__
