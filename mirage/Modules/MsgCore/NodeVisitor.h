
#ifndef __MSG_CORE_NODE_VISITOR_H__
#define __MSG_CORE_NODE_VISITOR_H__

#include "Export.h"

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"

namespace Msg 
{
	namespace MsgCore
	{
		class Node;
		class Group;
		class Geode;

    class MSG_EXPORT NodeVisitor : public Referenced
		{
			public:

				typedef std::vector< Node* > NodePath;

        enum Type
        {
          UPDATE = 0, 
          DRAW
        };


				NodeVisitor( const Type& type ) :          
          Referenced(), 
          _type( type )
				{
				}


				NodeVisitor( const NodeVisitor& nodeVisitor ) :
					Referenced( nodeVisitor )
				{
				}


        const Type&                 type() const 
        {
          return _type;
        }
        

				virtual void                apply( Node& node );
				
				virtual void                apply( Group& group );

				virtual void                apply( Geode& geode );

				virtual void                traverse( Node& node );

				virtual void                push( Node* node );

				virtual void                pop();
			

			protected:

				virtual ~NodeVisitor()
				{
        }


			protected:

        Type                        _type;

				NodePath	                  _nodePath;

		};
	}
}

inline void Msg::MsgCore::NodeVisitor::apply( Msg::MsgCore::Node& node )
{
	traverse( node );
}


inline void Msg::MsgCore::NodeVisitor::apply( Msg::MsgCore::Group& group )
{
  Msg::MsgCore::Group::Children children = group.children();

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
	_nodePath.push_back( node );
}


inline void Msg::MsgCore::NodeVisitor::pop()
{
	_nodePath.pop_back();
}

#endif  __MSG_CORE_NODE_VISITOR_H__
