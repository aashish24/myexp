
#include "MsgCore/Node.h"
#include "MsgCore/NodeVisitor.h"

#include "MsgCore/Group.h"
#include "MsgCore/Geode.h"

#include "MsgCore/Uniform.h"

using namespace Msg;
using namespace MsgCore;

Uniform1i* myUniform = new Uniform1i();

Group* Node::asGroup() 
{
  return dynamic_cast< Group* >( this );
}


Geode* Node::asGeode()
{
  return dynamic_cast< Geode* >( this );
}


void Node::accept( NodeVisitor& nv )
{
	// Push onto node path. 
	// Traverse further down.  
	// Pop out. 
	nv.push( this );
	nv.apply( *this );
	nv.pop(); 
}
