
#ifndef __OGE_CORE_EVENT_H__
#define __OGE_CORE_EVENT_H__

#include "Oge/OgeBase/OgeInterfaces/IEvent.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      struct Event : public IEvent, public Referenced
      {
        Event( Type type ) : _type( type )
        {
        }
        
        virtual void Type type() const
        {
          return 
        }

        protected: 
          
          virtual ~Event()
          {
          }

        protected: 
          
          Type  _type;
      };
    }
  }
}

#endif // __OGE_CORE_EVENT_H__
