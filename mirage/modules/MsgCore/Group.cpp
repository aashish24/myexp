
#include "MsgCore/Group.h"
#include "MsgCore/NodeVisitor.h"

void Msg::MsgCore::Group::traverse( NodeVisitor &nv )
{
  switch( nv.type() )
  {
    case Msg::MsgCore::NodeVisitor::UPDATE: 
    {
      break;
    }

    case Msg::MsgCore::NodeVisitor::DRAW: 
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
