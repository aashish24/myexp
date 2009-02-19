
#ifndef __MSG_CORE_NODE_VISITOR_H__
#define __MSG_CORE_NODE_VISITOR_H__

#include "Export.h"

#include "MirageCore/Node.h"
#include "MirageCore/Group.h"

namespace Mirage 
{
	namespace MirageCore
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

inline void Mirage::MirageCore::NodeVisitor::apply( Mirage::MirageCore::Node& node )
{
	traverse( node );
}


inline void Mirage::MirageCore::NodeVisitor::apply( Mirage::MirageCore::Group& group )
{
  Mirage::MirageCore::Group::Children children = group.children();

  Mirage::MirageCore::Group::Children::const_iterator itr = children.begin();

  for( itr; itr != children.end(); ++itr )
  {
    apply( *( itr->get() ) );
  }
}


inline void Mirage::MirageCore::NodeVisitor::apply( Mirage::MirageCore::Geode& geode )
{
	apply( ( Node& )geode ); 
}


inline void Mirage::MirageCore::NodeVisitor::traverse( Node& node )
{
	node.traverse( *this );
}


inline void Mirage::MirageCore::NodeVisitor::push( Node* node )
{
	_nodePath.push_back( node );
}


inline void Mirage::MirageCore::NodeVisitor::pop()
{
	_nodePath.pop_back();
}

#endif  __MSG_CORE_NODE_VISITOR_H__
