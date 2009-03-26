
#ifndef __MIRAGE_MATH_AXIS_ANGLE_H__
#define __MIRAGE_MATH_AXIS_ANGLE_H__

#include "Vec.h"

namespace Mirage
{
  namespace Math
  {
    // Forward declaration. 
    class Utils;

    ///////////////////////////////////////////////////////////////////////////
    //
    // \c AxisAngle defines rotation aroung arbitraty axis. 
    //
    ///////////////////////////////////////////////////////////////////////////

    template< class DataTypeT >
    class AxisAngle
    {      
      friend Utils;

      public: 
     
        // Constructor. 
        AxisAngle() : 
          _axis   ( Vec< DataTypeT, 3 >( 0.0, 0.0, 0.0 ) ), 
          _angle  ( 0.0 )
        {
        }

        // Copy constructor. 
        AxisAngle( const Vec< DataTypeT, 3 >& axis, const DataTypeT&  angle ) : 
          _axis ( axis ), 
          _angle( angle )
        {
        }


       // Destructor. 
       ~AxisAngle()
       {
         // Do nothing. 
       }

      private: 

        // Arbitrary axis. 
        mutable Vec< DataTypeT, 3 > _axis;

        // Angle of rotation. 
        mutable DataTypeT           _angle;
    };

    // Useful instantiations. 
    typedef AxisAngle< float >  AxisAnglef;
    typedef AxisAngle< double > AxisAngled;
  }
}

#endif // __MIRAGE_MATH_AXIS_ANGLE_H__
