
#ifndef __I3DEA_FUNCTORS_GLOBAL_DISPLAY_FUNCTOR_H__
#define __I3DEA_FUNCTORS_GLOBAL_DISPLAY_FUNCTOR_H__

#include "Export.h"
#include "IFunctor.h"
#include <algorithm>

#include <functional>

typedef void (*DisplayFunc)( void );

template< typename T >
class  GlobalDisplayFunctor : public IFunctor
{
public:
	GlobalDisplayFunctor( T func ) : mDisplayFunc( func ) 
	{
		//func();
	}

	virtual void call()
	{
		//(*mDisplayFunc)( true );
		mDisplayFunc();
	}

private:
	T mDisplayFunc;
};

#endif // __I3DEA_FUNCTORS_GLOBAL_DISPLAY_FUNCTOR_H__