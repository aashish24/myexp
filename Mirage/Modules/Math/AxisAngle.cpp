
#include "AxisAngle.h"

namespace Mirage
{
  namespace MirageMath
  {    
    AxisAngle::AxisAngle() : 
      _axis   ( Vec3f(0.0, 0.0, 0.0), 
      _angle  ( 0.0 )
    {
    }

    
    AxisAngle::AxisAngle( Vec< DATA_TYPE, 3 > axis, const DATA_TYPE&  angle ) : 
      _axis ( axis ), 
      _angle( angle )
    {
    }

    AxisAngle::~AxisAngle()
    {
      // Do nothing. 
    }
  }
}

#endif // __MIRAGE_MATH_AXIS_ANGLE_H__
