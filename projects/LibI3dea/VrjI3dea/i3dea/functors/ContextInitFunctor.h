

#ifndef __I3DEA_FUNCTORS_CONTEXT_INIT_FUNCTOR_H__
#define __I3DEA_FUNCTORS_CONTEXT_INIT_FUNCTOR_H__

#include "Export.h"
#include "IFunctor.h"

template< typename T >
class  ContextInitFunctor : public IFunctor
{
public:
  ContextInitFunctor( T func ) : _contextInitFunc( func ) 
	{		
	}

	virtual void call()
	{
		_contextInitFunc();
	}

private:
	T _contextInitFunc;
};

#endif // __I3DEA_FUNCTORS_CONTEXT_INIT_FUNCTOR_H__