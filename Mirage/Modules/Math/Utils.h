
#ifndef __MIRAGE_MATH_UTILS_H__
#define __MIRAGE_MATH_UTILS_H__

#include <cmath>

namespace Mirage
{
  namespace Math
  {
    class Utils
    {
      public: 
        
        template< typename RotationTypeT, typename SourceTypeT > 
        static RotationTypeT makeRot( const SourceTypeT& coord )                                         
        {
          RotationTypeT temp; 
          return setRot( temp, coord );
        }


        template< typename DataTypeT, unsigned ROWS, unsigned COLS > 
        static Matrix< DataTypeT, ROWS, COLS >& set( Matrix< DataTypeT, ROWS, COLS >& result, 
                                                     const AxisAngle< DataTypeT >&    axisAngle )
        {
          identity( result );
          setRot( result, axisAngle ); 
        }
          

        template< typename DataTypeT, unsigned ROWS, unsigned COLS > 
        static Matrix< DataTypeT, ROWS, COLS >& setRot( Matrix< DataTypeT, ROWS, COLS >& result, 
                                                        const AxisAngle< DataTypeT >&    axisAngle )        
        {
            // Make axis a unit vector first. 
            axisAngle._axis.normalize();

            DataTypeT c = cos( degToRad( axisAngle._angle ) );
            DataTypeT s = sin( degToRad( axisAngle._angle ) );
            DataTypeT t = DataTypeT( 1.0 ) - c ;

            result( 0,0 ) = t * ( axisAngle._axis[0] * axisAngle._axis[0] ) + ( c );
            result( 0,1 ) = t * ( axisAngle._axis[0] * axisAngle._axis[1] ) - ( s * axisAngle._axis[2] );
            result( 0,2 ) = t * ( axisAngle._axis[0] * axisAngle._axis[2] ) + ( s * axisAngle._axis[1] );            
            result( 1,0 ) = t * ( axisAngle._axis[0] * axisAngle._axis[1] ) + ( s * axisAngle._axis[2] );          
            result( 1,1 ) = t * ( axisAngle._axis[1] * axisAngle._axis[1] ) + ( c );
            result( 1,2 ) = t * ( axisAngle._axis[1] * axisAngle._axis[2] ) - ( s * axisAngle._axis[0] );            
            result( 2,0 ) = t * ( axisAngle._axis[0] * axisAngle._axis[1] ) - ( s * axisAngle._axis[1] );
            result( 2,1 ) = t * ( axisAngle._axis[1] * axisAngle._axis[2] ) + ( s * axisAngle._axis[0] );
            result( 2,2 ) = t * ( axisAngle._axis[2] * axisAngle._axis[2] ) + ( c );           

            return result;
        }


        template< typename DataTypeT, unsigned ROWS, unsigned COLS >
        static void identity( Matrix< DataTypeT, ROWS, COLS >& mat )
        { 
          mat( 0, 0 ) = ( DataTypeT ) 1.0;
          mat( 0, 1 ) = ( DataTypeT ) 0.0;
          mat( 0, 2 ) = ( DataTypeT ) 0.0;
          mat( 0, 3 ) = ( DataTypeT ) 0.0;
          mat( 1, 0 ) = ( DataTypeT ) 0.0;
          mat( 1, 1 ) = ( DataTypeT ) 1.0;
          mat( 1, 2 ) = ( DataTypeT ) 0.0;
          mat( 1, 3 ) = ( DataTypeT ) 0.0;
          mat( 2, 0 ) = ( DataTypeT ) 0.0;
          mat( 2, 1 ) = ( DataTypeT ) 0.0;
          mat( 2, 2 ) = ( DataTypeT ) 1.0;
          mat( 2, 3 ) = ( DataTypeT ) 0.0;
          mat( 3, 0 ) = ( DataTypeT ) 0.0;
          mat( 3, 1 ) = ( DataTypeT ) 0.0;
          mat( 3, 2 ) = ( DataTypeT ) 0.0;
          mat( 3, 3 ) = ( DataTypeT ) 1.0;
        }


        template< class DataTypeT >
        static DataTypeT degToRad( const DataTypeT& deg )
        {
          return ( deg * ( static_cast< DataTypeT >( 22.0 ) / ( 7.0 * 180.0 ) ) ); 
        }
    };
  }
}

#endif // __MIRAGE_MATH_UTILS_H__


