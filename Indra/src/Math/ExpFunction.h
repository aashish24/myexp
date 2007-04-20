
#ifndef __MATH_EXPFUNCTION_H__
#define __MATH_EXPFUNCTION_H__

#include <cmath>

#include "Math/Function.h"

#include "Export.h"

namespace Math
{  
  class MATH_EXPORT ExpFunction : public Function
  {
    public: 
      ExpFunction() : 
        mBase( 1.0 )
      {        
      }

      ExpFunction( const double& base ) :
        mBase( base )  
      {
      }

      virtual void base( const double& base )
      {
        mBase = base;
      }
      
      virtual double f( double& result, const double& input )
      {
        double absInput = fabs( input );
        if( input < 0.0 )
        {          
          result = -pow( absInput, mBase );
        }
        else
        {
          result =  pow( absInput, mBase );
        }

        return result;
      }

    protected: 
      virtual ~ExpFunction()
      {
      }

      double mBase;

  };
}

#endif // __MATH_EXPFUNCTION_H__
