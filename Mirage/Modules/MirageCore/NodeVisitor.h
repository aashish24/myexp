
#ifndef __MSG_CORE_NODE_VISITOR_H__
#define __MSG_CORE_NODE_VISITOR_H__

#include "Export.h"

#include "Core/Node.h"
#include "Core/Group.h"

namespace Mirage 
{
	namespace Core
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

inline void Mirage::Core::NodeVisitor::apply( Mirage::Core::Node& node )
{
	traverse( node );
}


inline void Mirage::Core::NodeVisitor::apply( Mirage::Core::Group& group )
{
  Mirage::Core::Group::Children children = group.children();

  Mirage::Core::Group::Children::const_iterator itr = children.begin();

  for( itr; itr != children.end(); ++itr )
  {
    apply( *( itr->get() ) );
  }
}


inline void Mirage::Core::NodeVisitor::apply( Mirage::Core::Geode& geode )
{
	apply( ( Node& )geode ); 
}


inline void Mirage::Core::NodeVisitor::traverse( Node& node )
{
	node.traverse( *this );
}


inline void Mirage::Core::NodeVisitor::push( Node* node )
{
	_nodePath.push_back( node );
}


inline void Mirage::Core::NodeVisitor::pop()
{
	_nodePath.pop_back();
}

#endif  __MSG_CORE_NODE_VISITOR_H__
