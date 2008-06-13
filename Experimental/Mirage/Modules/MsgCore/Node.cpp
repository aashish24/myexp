
#include "MsgCore/Node.h"
#include "MsgCore/NodeVisitor.h"

#include "MsgCore/Uniform.h"

using namespace Msg;
using namespace MsgCore;

Uniform1i* myUniform = new Uniform1i();

void Node::accept( NodeVisitor& nv )
{
	// Push onto node path. 
	// Traverse further down.  
	// Pop out. 
	nv.push( this );
	nv.apply( *this );
	nv.pop(); 
}
