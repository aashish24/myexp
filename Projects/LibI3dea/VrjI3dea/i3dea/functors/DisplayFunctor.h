
#ifndef __I3DEA_FUNCTORS_DISPLAY_FUNCTOR_H__
#define __I3DEA_FUNCTORS_DISPLAY_FUNCTOR_H__

#include "Export.h"
#include "IFunctor.h"

template< typename T >
class  DisplayFunctor : public IFunctor
{
public:
	DisplayFunctor( T func ) : _displayFunc( func ) 
	{		
	}

	virtual void call()
	{
		_displayFunc();
	}

private:
	T _displayFunc;
};

#endif // __I3DEA_FUNCTORS_DISPLAY_FUNCTOR_H__