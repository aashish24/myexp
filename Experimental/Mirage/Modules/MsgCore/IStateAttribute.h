
#ifndef __MSG_CORE_STATE_I_ATTRIBUTE_H__
#define __MSG_CORE_STATE_I_ATTRIBUTE_H__

#include "MsgCore/Object.h"

namespace Msg
{
	namespace MsgCore
	{
    class Node;

    class IStateAttribute 
		{
			public:

        virtual std::string id() const        = 0;

        virtual void init()                   = 0;

        virtual void contextInit()            = 0;

        virtual bool dirty() const            = 0;

        virtual void dirty( const bool& flag )= 0;

				virtual void activate( Node* node )   = 0;

        virtual void deActivate( Node* node ) = 0;
		};
	}
}

#endif // __MSG_CORE_STATE_I_ATTRIBUTE_H__
