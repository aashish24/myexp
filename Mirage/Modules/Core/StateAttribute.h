
#ifndef __MSG_CORE_STATE_ATTRIBUTE_H__
#define __MSG_CORE_STATE_ATTRIBUTE_H__

#include "Export.h"

#include "Core/Object.h"
#include "Core/IStateAttribute.h"

namespace Mirage
{
	namespace Core
	{   
    class MSG_EXPORT StateAttribute : public Core::IStateAttribute, public Core::Object 
		{
			public:                

        StateAttribute( const bool& flag = true, const int& mask = IStateAttribute::ON );

        virtual bool dirty() const;
        virtual void dirty( const bool& flag );
        
        virtual const int& mask() const;
        virtual void mask( const int& maskVal );


      protected:

        virtual ~StateAttribute();

      
      protected: 

        bool         _dirty;

        int          _mask;
		};
	}
}

#endif // __MSG_CORE_STATE_ATTRIBUTE_H__
