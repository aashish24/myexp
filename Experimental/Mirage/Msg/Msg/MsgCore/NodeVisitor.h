#ifndef __NODE_VISITOR_H__
#define __NODE_VISITOR_H__

#include "oge/Export.h"

#include "oge/core/Node.h"
#include "oge/core/Group.h"
#include "oge/core/Object.h"

namespace oge 
{
	namespace core
	{
		class Node;
		class Group;
		class Geode;

		class OGE_EXPORT NodeVisitor : public Object 
		{
			public:
				typedef std::vector< Node* > NodePath;

				NodeVisitor() : 
					Object() 
				{
				}

				NodeVisitor( const NodeVisitor& nodeVisitor ) :
					Object( nodeVisitor )
				{
				}

				virtual void apply( Node& node );
				
				virtual void apply( Group& group );

				virtual void apply( Geode& geode );

				virtual void traverse( Node& node );

				virtual void push( Node* node );

				virtual void pop();
			
			protected:
				virtual ~NodeVisitor()
				{}

			private:
				NodePath	mNodePath;

		};
	}
}

inline void oge::core::NodeVisitor::apply( oge::core::Node& node )
{
	traverse( node );
}

inline void oge::core::NodeVisitor::apply( oge::core::Group& group )
{
  oge::core::Group::Children children = group.getChildren();

  oge::core::Group::Children::const_iterator itr = children.begin();

  for( itr; itr != children.end(); ++itr )
  {
    apply( *( itr->get() ) );
  }
}

inline void oge::core::NodeVisitor::apply( oge::core::Geode& geode )
{
	apply( ( Node& )geode ); 
}

inline void oge::core::NodeVisitor::traverse( Node& node )
{
	node.traverse( *this );
}

inline void oge::core::NodeVisitor::push( Node* node )
{
	mNodePath.push_back( node );
}

inline void oge::core::NodeVisitor::pop()
{
	mNodePath.pop_back();
}

#endif  __NODE_VISITOR_H__
