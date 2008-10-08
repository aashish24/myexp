
#ifndef _ANIMATIONTOOLS_H_
#define _ANIMATIONTOOLS_H_

#include <gmtl/gmtl.h>



template <class DataTypeT, unsigned int SizeI>
void
    bezierEval(
        gmtl::Vec<DataTypeT, SizeI>       &res,
        DataTypeT                          t,
        gmtl::Vec<DataTypeT, SizeI> const &p0,
        gmtl::Vec<DataTypeT, SizeI> const &p1,
        gmtl::Vec<DataTypeT, SizeI> const &p2,
        gmtl::Vec<DataTypeT, SizeI> const &p3 );


template <class DataTypeT, unsigned int SizeI>
inline void
    bezierEval(
        gmtl::Vec<DataTypeT, SizeI>       &res,
        DataTypeT                          t,
        gmtl::Vec<DataTypeT, SizeI> const &p0,
        gmtl::Vec<DataTypeT, SizeI> const &p1,
        gmtl::Vec<DataTypeT, SizeI> const &p2,
        gmtl::Vec<DataTypeT, SizeI> const &p3 )
{
    gmtl::Vec<DataTypeT, SizeI> scratch[4];
    
    scratch[0] = p0;
    scratch[1] = p1;
    scratch[2] = p2;
    scratch[3] = p3;
    
    float s = 1.0f - t;
    
    for(unsigned int i = 0; i < 4; ++i)
    {
        for(unsigned int j = 0; j < 3 - i; ++j)
        {
            scratch[j] = s * scratch[j] + t * scratch[j + 1];
        }
    }
    
    res = scratch[0];
}


template <typename T>
inline T
	fbezierEval (
			T const& t,
			T const& p0,
			T const& p1,
			T const& p2,
			T const& p3		
			)
{
	T ot = 1 - t;

	/****  this one "the" bezier equation ***
	return  gmtl::Math::pow(ot,3)         * p0 + 
			3 * t * gmtl::Math::pow(ot,2) * p1 + 
			3 * gmtl::Math::pow(t,2) * ot * p2 +
			gmtl::Math::pow(t,3)          * p3;
	*/
	
	/****  http://www.niksula.cs.hut.fi/~hkankaan/Homepages/bezierfast.html  ***/	
	T temp = t * t;

	T f = p0;
	T fd = 3 * (p1 - p0) * t;
	T fdd_per_2 = 3 * (p0 - 2 * p1 + p2) * temp;
	T fddd_per_2 = 3 * (3 * (p1 - p2) + p3 - p0) * temp * t;

	T fddd_per_6 = fddd_per_2 * (1.0 / 3);

	return (f + fd + fdd_per_2 + fddd_per_6);
	
}


//tnormalize
// used to calculate normalized value of time t
// between time ta and time tb
template <typename T>
inline T 
	tnormalize(T t, T ta, T tb)
{
	return ((t-ta) / (tb-ta));
}

template <typename T>
inline std::vector<T>
	calcBezier(	T const& tstep,
				T const& p0,
				T const& p1,
				T const& p2,
				T const& p3		
)
{
	std::vector<T> result;
	/*** http://www.niksula.cs.hut.fi/~hkankaan/Homepages/bezierfast.html **/
	//the amount of steps in the bezier curve
	unsigned int steps = static_cast<unsigned int>((T) 1 / tstep);
	
	//== The algorithm itself begins here ==
	T f, fd, fdd, fddd, fdd_per_2, fddd_per_2, fddd_per_6;
	T temp = tstep * tstep;
	
	//I've tried to optimize the amount of
	//multiplications here, but these are exactly
	//the same formulas that were derived earlier
	//for f(0), f'(0)*t etc.
	f = p0;
	fd = 3 * (p1 - p0) * tstep;
	fdd_per_2 = 3 * (p0 - 2 * p1 + p2) * temp;
	fddd_per_2 = 3 * (3 * (p1 - p2) + p3 - p0) * temp * tstep;
	
	fddd = fddd_per_2 + fddd_per_2;
	fdd = fdd_per_2 + fdd_per_2;
	fddd_per_6 = fddd_per_2 * (1.0 / 3);
	
	for (unsigned int loop=0; loop < steps; loop++) {
	  result.push_back(f);
	
	  f = f + fd + fdd_per_2 + fddd_per_6;
	  fd = fd + fdd + fddd_per_2;
	  fdd = fdd + fddd;
	  fdd_per_2 = fdd_per_2 + fddd_per_2;
	}
	
	result.push_back(f);
	return result;
}


#endif // _ANIMATIONTOOLS_H_

