
#ifndef __MSG_CORE_GROUP_H__
#define __MSG_CORE_GROUP_H__

#include "MsgCore/Node.h"

namespace Msg
{
	namespace MsgCore
	{		
    class MSG_EXPORT Group : public Msg::MsgCore::Node 
		{
			public:
        
        // Typedefs. 
		    typedef std::vector< SmartPtr< Node > > Children;

				Group() :
					Node(),
					_children()
				{
        }


				Group( const Group& group ) :
					Node( group ),
					_children()
				{
        }


				virtual	Node* child( unsigned int index )
				{
					if( index < _children.size() )
					{
						return _children[index].get();
					}
					else
					{
						return 0x00;
					}
				}


				virtual const Children& children() const
				{
					return _children;
				}	
	

				virtual	void addChild( Node* child )
				{
					// As of now the a child can be 
					// added sequentially and not randomly. 
					_children.push_back( child );

					// Register as parent of child. 
					child->addParent( this );

					// Make the bound dirty here.

					// Force the traversal.
				}


				virtual void traverse( NodeVisitor& nv );


			protected:

				virtual ~Group()
				{
        }


			protected:

				Children  _children;
		};
	}
}

#endif // __MSG_CORE_GROUP_H__
