
#ifndef __MSG_CORE_STATE_I_ATTRIBUTE_H__
#define __MSG_CORE_STATE_I_ATTRIBUTE_H__

#include "MirageCore/Object.h"

namespace Mirage
{
	namespace MirageCore
	{
    class Node;

    class IStateAttribute 
		{
			public:

        enum Values
        {
          OFF       = 0x0,
          ON        = 0x1,
          OVERRIDE  = 0x2, 
          PROTECTED = 0x4,
          INHERIT   = 0x8
        };

        virtual std::string id() const              = 0;

        virtual void init()                         = 0;

        virtual void contextInit()                  = 0;

        virtual bool dirty() const                  = 0;

        virtual void dirty( const bool& flag )      = 0;

        virtual void mask( const int& maskVal ) = 0;

        virtual const int& mask() const        = 0;

				virtual void activate( Node* node )         = 0;

        virtual void deActivate( Node* node )       = 0;
		};
	}
}

#endif // __MSG_CORE_STATE_I_ATTRIBUTE_H__
