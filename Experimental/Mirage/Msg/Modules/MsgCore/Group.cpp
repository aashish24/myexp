
#include "MsgCore/Group.h"

void Msg::MsgCore::Group::traverse( NodeVisitor &nv )
{
  this->activateStateSet();

	// @Todo: Why use iterator here ?? 
	for( size_t i=0; i < _children.size(); ++i )
	{
		_children[i]->accept( nv );
	}

  this->deActivateStateSet();
}
