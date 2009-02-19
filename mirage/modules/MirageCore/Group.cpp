
#include "MirageCore/Group.h"
#include "MirageCore/NodeVisitor.h"

void Mirage::MirageCore::Group::traverse( NodeVisitor &nv )
{
  switch( nv.type() )
  {
    case Mirage::MirageCore::NodeVisitor::UPDATE: 
    {
      break;
    }

    case Mirage::MirageCore::NodeVisitor::DRAW: 
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
