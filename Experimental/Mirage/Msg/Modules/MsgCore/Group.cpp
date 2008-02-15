#include <oge/core/Group.h>

using namespace oge::core;

void Group::traverse( NodeVisitor &nv )
{
	if( mStateSet.valid() )
	{
		mStateSet->drawGLState();
	}

	// @Todo: Why use iterator here ?? 
	for( size_t i=0; i < mChildren.size(); ++i )
	{
		mChildren[i]->accept( nv );
	}
}
