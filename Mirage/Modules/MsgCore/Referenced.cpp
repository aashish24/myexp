
#include "MsgCore/Referenced.h"

#include <iostream>

using namespace Msg::MsgCore;

Referenced::Referenced() :
	_refCount( 0 )
{

}

Referenced::Referenced( const Msg::MsgCore::Referenced &ref ) :
	_refCount( 0 )
{

}


Referenced::~Referenced()
{
	if( _refCount > 0 )
	{
    std::cerr << "WARNING 1746864110: Deleting still referenced object: " 
			        << std::endl;
	}
}


void Referenced::ref()
{
	++_refCount;
}


void Referenced::unref()
{	
	--_refCount;

	if( _refCount <= 0 )
	{
		delete this;
	}
}


void Referenced::unrefDoNotDelete()
{
	--_refCount;
}

