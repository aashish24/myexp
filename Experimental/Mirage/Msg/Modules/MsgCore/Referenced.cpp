#include <oge/core/Referenced.h>

#include <iostream>

using namespace oge::core;

Referenced::Referenced() :
	mRefCount( 0 )
{

}

Referenced::Referenced( const oge::core::Referenced &ref ) :
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

