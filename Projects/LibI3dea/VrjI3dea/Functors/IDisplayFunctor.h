

#ifndef __I3DEA_FUNCTORS_IDISPLAY_FUNCTOR_H__
#define __I3DEA_FUNCTORS_IDISPLAY_FUNCTOR_H__

struct IDisplayFunctor : public IFunctors 
{
	virtual void call{ draw() );
	virtual void draw() = 0
};

#endif // __I3DEA_FUNCTORS_IDISPLAY_FUNCTOR_H__