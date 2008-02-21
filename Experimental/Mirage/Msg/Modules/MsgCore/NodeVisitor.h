#ifndef __NODE_VISITOR_H__
#define __NODE_VISITOR_H__

#include "Export.h"

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"
#include "MsgCore/Object.h"

namespace Msg 
{
	namespace MsgCore
	{
		class Node;
		class Group;
		class Geode;

		class MSG_EXPORT NodeVisitor : public Object 
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

inline void Msg::MsgCore::NodeVisitor::apply( Msg::MsgCore::Node& node )
{
	traverse( node );
}

inline void Msg::MsgCore::NodeVisitor::apply( Msg::MsgCore::Group& group )
{
  Msg::MsgCore::Group::Children children = group.getChildren();

  Msg::MsgCore::Group::Children::const_iterator itr = children.begin();

  for( itr; itr != children.end(); ++itr )
  {
    apply( *( itr->get() ) );
  }
}

inline void Msg::MsgCore::NodeVisitor::apply( Msg::MsgCore::Geode& geode )
{
	apply( ( Node& )geode ); 
}

inline void Msg::MsgCore::NodeVisitor::traverse( Node& node )
{
	node.traverse( *this );
}

inline void Msg::MsgCore::NodeVisitor::push( Node* node )
{
	mNodePath.push_back( node );
}

inline void Msg::MsgCore::NodeVisitor::pop()
{
	mNodePath.pop_back();
}

#endif  __NODE_VISITOR_H__
