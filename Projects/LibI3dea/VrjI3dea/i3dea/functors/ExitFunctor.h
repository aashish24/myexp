
#ifndef __I3DEA_FUNCTORS_EXIT_FUNCTOR_H__
#define __I3DEA_FUNCTORS_EXIT_FUNCTOR_H__

#include "Export.h"
#include "IFunctor.h"

template< typename T >
class  ExitFunctor : public IFunctor
{
public:
	ExitFunctor( T func ) : _exitFunc( func ) 
	{		
	}

	virtual void call()
	{
		_exitFunc();
	}

private:
	T _exitFunc;
};

#endif // __I3DEA_FUNCTORS_EXIT_FUNCTOR_H__