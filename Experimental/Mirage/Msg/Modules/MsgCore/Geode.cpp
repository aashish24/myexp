#include <oge/core/Geode.h>

using namespace oge::core;

void Geode::compileDrawables()
{
}

Geode::~Geode()
{
}

void Geode::traverse( NodeVisitor& nv )
{
	if( mStateSet.valid() )
	{
		mStateSet->drawGLState();
	}

	for( size_t i=0; i < mDrawables.size(); ++i )
	{
		mDrawables[i]->draw();
	}
}