
#ifndef __MSG_CORE_STATE_ATTRIBUTE_H__
#define __MSG_CORE_STATE_ATTRIBUTE_H__

#include "Export.h"

#include "MsgCore/Object.h"
#include "MsgCore/IStateAttribute.h"

namespace Msg
{
	namespace MsgCore
	{   
    class MSG_EXPORT StateAttribute : public MsgCore::IStateAttribute, public MsgCore::Object 
		{
			public:                

        StateAttribute( const bool& flag = true );

        virtual bool dirty() const;

        virtual void dirty( const bool& flag );


      protected:

        virtual ~StateAttribute();

      
      protected: 

        bool         _dirty;
		};
	}
}

#endif // __MSG_CORE_STATE_ATTRIBUTE_H__
