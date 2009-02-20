
#include "MirageCore/Node.h"
#include "MirageCore/NodeVisitor.h"

#include "MirageCore/Group.h"
#include "MirageCore/Geode.h"

#include "MirageCore/Uniform.h"

using namespace Mirage;
using namespace MirageCore;

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
