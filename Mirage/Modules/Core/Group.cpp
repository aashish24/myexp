
#include "Core/Group.h"
#include "Core/NodeVisitor.h"

void Mirage::Core::Group::traverse( NodeVisitor &nv )
{
  switch( nv.type() )
  {
    case Mirage::Core::NodeVisitor::UPDATE: 
    {
      break;
    }

    case Mirage::Core::NodeVisitor::DRAW: 
    {
      this->activateStateSet();

	    // @Todo: Why use iterator here ?? 
	    for( size_t i=0; i < _children.size(); ++i )
	    {
		    _children[i]->accept( nv );
	    }

      this->deActivateStateSet();
      break;
    }
  }; // end switch( ... )
}
