
#include "Core/Node.h"
#include "Core/NodeVisitor.h"

#include "Core/Group.h"
#include "Core/Geode.h"

#include "Core/Uniform.h"

using namespace Mirage;
using namespace Core;

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
