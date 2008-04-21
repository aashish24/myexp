
#include "MsgCore/Geode.h"

using namespace Msg::MsgCore;

void Geode::compileDrawables()
{
}

Geode::~Geode()
{
}

void Geode::traverse( NodeVisitor& nv )
{
  this->activateStateSet();

	for( size_t i=0; i < mDrawables.size(); ++i )
	{
		mDrawables[i]->draw();
	}

  this->deActivateStateSet();
}