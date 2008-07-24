
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

    class MSG_EXPORT StateSet : public MsgCore::Object 
		{
			public:

        ///////////////////////////////////////////////////////////////////////
        //
        // Define easy to remember names. 
        //
        ///////////////////////////////////////////////////////////////////////
        
        typedef std::list< SmartPtr< StateAttribute > >                                 Attributes;
        typedef std::map< unsigned int, std::pair< SmartPtr< StateAttribute >, bool > > TextureAttributes;


        ///////////////////////////////////////////////////////////////////////
        //
        // Constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				StateSet();


        ///////////////////////////////////////////////////////////////////////
        //
        // Copy constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				StateSet( const StateSet& stateset );


        ///////////////////////////////////////////////////////////////////////
        //
        // Return state of being dirty. 
        //
        ///////////////////////////////////////////////////////////////////////

        bool dirty() const;


        ///////////////////////////////////////////////////////////////////////
        //
        // Set state of being dirty. 
        //
        ///////////////////////////////////////////////////////////////////////

        void dirty( bool flag ); 


        ///////////////////////////////////////////////////////////////////////
        //
        // Return a attribute with given id. 
        //
        ///////////////////////////////////////////////////////////////////////

        void attribute( const std::string& id );


        ///////////////////////////////////////////////////////////////////////
        //
        // Return list of attributes. 
        //
        ///////////////////////////////////////////////////////////////////////

        Attributes& attributes();


        ///////////////////////////////////////////////////////////////////////
        //
        // Push an attribute. 
        // @Note: This will check for collision and perform operations 
        // based on the IStateAttribute::Values mask. 
        //
        ///////////////////////////////////////////////////////////////////////

        void pushAttribute( StateAttribute* attr );


        ///////////////////////////////////////////////////////////////////////
        //
        // Set attribute and its state. 
        //
        // @Note: Attribute with the same id will be removed if present. 
        //
        ///////////////////////////////////////////////////////////////////////

        void attribute( StateAttribute* attr, const int& mask = IStateAttribute::ON );


        ///////////////////////////////////////////////////////////////////////
        //        
        // Get list of texture attributes.         
        //
        // @Note: Texture attributes are handled differently because we can 
        // have multiple textures associate with any object. 
        // 
        ///////////////////////////////////////////////////////////////////////

        TextureAttributes& textureAttributes();


        ///////////////////////////////////////////////////////////////////////
        //
        // Set texture attribute and its state.         
        //
        ///////////////////////////////////////////////////////////////////////

        void textureAttribute( unsigned int unit, StateAttribute* attr, const int& mask = IStateAttribute::ON );

        
        ///////////////////////////////////////////////////////////////////////
        //
        // Active StateSet on the given node. 
        //
        ///////////////////////////////////////////////////////////////////////

				void activateStateSet( Node* node );


        ///////////////////////////////////////////////////////////////////////
        //
        // Deactive StateSet on the given node. 
        //
        ///////////////////////////////////////////////////////////////////////

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
