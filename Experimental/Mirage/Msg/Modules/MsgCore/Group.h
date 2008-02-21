///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////				

#ifndef __GROUP_H__
#define __GROUP_H__

#include "MsgCore/Node.h"

namespace Msg
{
	namespace MsgCore
	{		
		class OGE_EXPORT Group : public Node 
		{
			public:
        
        // Typedefs. 
		    typedef std::vector< SmartPtr< Node > > Children;

				Group() :
					Node(),
					mChildren()
				{
        }

				Group( const Group& group ) :
					Node( group ),
					mChildren()
				{
        }

				virtual	Node* getChild( unsigned int index )
				{
					if( index < mChildren.size() )
					{
						return mChildren[index].get();
					}
					else
					{
						return 0;
					}
				}

				virtual const Children& getChildren() const
				{
					return mChildren;
				}	
	
				virtual	void addChild( Node* child )
				{
					// As of now the a child can be 
					// added sequentially and not randomly. 
					mChildren.push_back( child );

					// Register as parent of child. 
					child->addParent( this );

					// Make the bound dirty here.

					// Force the traversal.
				}

				virtual void traverse( NodeVisitor& nv );

			protected:
				virtual ~Group()
				{}

			protected:
				Children mChildren;
		};
	}
}

#endif // __GROUP_H__