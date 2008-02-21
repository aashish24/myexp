
#include "MsgCore/Referenced.h"

#include <iostream>

using namespace Msg::MsgCore;

Referenced::Referenced() :
	mRefCount( 0 )
{

}

Referenced::Referenced( const Msg::MsgCore::Referenced &ref ) :
	mRefCount( 0 )
{

}

Referenced::~Referenced()
{
	if( mRefCount > 0 )
	{
		std::cerr << "Warning: Deleting still referenced object: " 
			<< std::endl;
	}
}

void Referenced::ref()
{
	++mRefCount;
}

void Referenced::unref()
{	
	--mRefCount;

	if( mRefCount <= 0 )
	{
		delete this;
	}
}

void Referenced::unrefDoNotDelete()
{
	--mRefCount;
}

