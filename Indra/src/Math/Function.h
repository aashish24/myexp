
#ifndef __MATH_FUNCTIONS_H__
#define __MATH_FUNCTIONS_H__

#include "osg/Referenced" 
#include "osg/ref_ptr"

#include "Export.h"

namespace Math
{
  class MATH_EXPORT Function : public osg::Referenced
  {
    public:

      Function() : osg::Referenced()
      {
      }

      virtual double f( double& result, const double& input  )
      {
        return input;
      }

    protected: 

      virtual ~Function()
      {
      }

      
  };
}

#endif // __MATH_FUNCTIONS_H__
