#include <oge/core/Node.h>
#include <oge/core/NodeVisitor.h>

using namespace oge;
using namespace core;
 
void Node::accept( NodeVisitor& nv )
{
	// Push onto node path. 
	// Traverse further down.  
	// Pop out. 
	nv.push( this );
	nv.apply( *this );
	nv.pop();
}