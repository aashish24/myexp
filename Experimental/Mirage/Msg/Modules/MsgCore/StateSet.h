
#ifndef __STATE_SET_H__
#define __STATE_SET_H__

#include "MsgCore/Object.h"
#include "MsgCore/StateAttribute.h"

#include <list>
#include <map>

namespace Msg
{
	namespace MsgCore
	{
    class Node; 

		class MSG_EXPORT StateSet : public Object 
		{
			public:

        ///////////////////////////////////////////////////////////////////////
        //
        // Define easy to remember names. 
        //
        ///////////////////////////////////////////////////////////////////////
        
        typedef std::list< std::pair< SmartPtr< StateAttribute >, bool > > Attributes;
        typedef std::map< unsigned int, std::pair< SmartPtr< StateAttribute >, bool > > TextureAttributes;

				StateSet();

				StateSet( const StateSet& stateset );

        bool dirty() const;

        void dirty( bool flag ); 

        void getAttribute( const std::string& id );

        Attributes& getAttributes();

        void setAttribute( StateAttribute* attr, const bool& state = 1 );

        TextureAttributes& getTextureAttributes();

        void setTextureAttribute( unsigned int unit, StateAttribute* attr, const bool& state = 1 );

				void activateStateSet( Node* node );

        void deActivateStateSet( Node* node );


			protected:
				
        virtual ~StateSet();
      

      protected: 

        bool              _dirty;

        Attributes        _attributes;
        TextureAttributes _textureAttributes;      
		};
	}
}

#endif // __STATE_SET_H__
