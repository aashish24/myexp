
#include "MirageCore/Geode.h"
#include "MirageCore/NodeVisitor.h"

Mirage::MirageCore::Geode::~Geode()
{
}


void Mirage::MirageCore::Geode::compileDrawables()
{
}


void Mirage::MirageCore::Geode::traverse( NodeVisitor& nv )
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

	    for( size_t i=0; i < _drawables.size(); ++i )
	    {
		    _drawables[i]->draw();
	    }

      this->deActivateStateSet();

      break;
    }
  }; // end switch( ... )
}