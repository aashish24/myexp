
#include "MsgCore/Node.h"
#include "MsgCore/NodeVisitor.h"

using namespace Msg;
using namespace MsgCore;
 
void Node::accept( NodeVisitor& nv )
{
	// Push onto node path. 
	// Traverse further down.  
	// Pop out. 
	nv.push( this );
	nv.apply( *this );
	nv.pop();
}