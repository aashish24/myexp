
#ifndef __I3DEA_FUNCTORS_GLOBAL_DISPLAY_FUNCTOR_H__
#define __I3DEA_FUNCTORS_GLOBAL_DISPLAY_FUNCTOR_H__

#include "Export.h"
#include "IFunctor.h"

template< typename T >
struct VRJ_I3DEA_EXPORT GlobalDisplayFunctor : public IFunctor 
{	
	typedef (*DisplayFunc)();

	GlobalDisplayFunctor( DisplayFunc* displayFunc ) : 
		mDisplayFunc( displayFunc )
	{
	}

	virtual void call()
	{
		*mdisplayFunc();
	}

private:
	DisplayFunc* mDisplayFunc;
};

#endif // __I3DEA_FUNCTORS_GLOBAL_DISPLAY_FUNCTOR_H__