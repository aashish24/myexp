
#include "MsgCore/Geode.h"

Msg::MsgCore::Geode::~Geode()
{
}


void Msg::MsgCore::Geode::compileDrawables()
{
}


void Msg::MsgCore::Geode::traverse( NodeVisitor& nv )
{
  this->activateStateSet();

	for( size_t i=0; i < _drawables.size(); ++i )
	{
		_drawables[i]->draw();
	}

  this->deActivateStateSet();
}