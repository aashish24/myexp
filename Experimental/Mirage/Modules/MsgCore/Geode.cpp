
#include "MsgCore/Geode.h"
#include "MsgCore/NodeVisitor.h"

Msg::MsgCore::Geode::~Geode()
{
}


void Msg::MsgCore::Geode::compileDrawables()
{
}


void Msg::MsgCore::Geode::traverse( NodeVisitor& nv )
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

	    for( size_t i=0; i < _drawables.size(); ++i )
	    {
		    _drawables[i]->draw();
	    }

      this->deActivateStateSet();

      break;
    }
  }; // end switch( ... )
}