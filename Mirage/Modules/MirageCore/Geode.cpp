
#include "Core/Geode.h"
#include "Core/NodeVisitor.h"

Mirage::Core::Geode::~Geode()
{
}


void Mirage::Core::Geode::compileDrawables()
{
}


void Mirage::Core::Geode::traverse( NodeVisitor& nv )
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

	    for( size_t i=0; i < _drawables.size(); ++i )
	    {
		    _drawables[i]->draw();
	    }

      this->deActivateStateSet();

      break;
    }
  }; // end switch( ... )
}