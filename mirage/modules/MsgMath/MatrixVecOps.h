
#ifndef __MSG_MATH_MATRIX_VEC_OPS_H__
#define __MSG_MATH_MATRIX_VEC_OPS_H__

#include "Export.h"

namespace Msg
{
  namespace MsgMath 
  {
    class MatrixVecOps 
    {
      public:        

        // Check for number of elements in Matrix and vector. 
        template< class MATRIX, class VECTOR >
        static VECTOR& mult( MATRIX& mat, VECTOR& vec )
        {
          if( mat.cols() != vec.size() )
          {
            throw; 
          }

          VECTOR temp;

          for( size_t i=0; i < vec.size(); ++i )
          {
            for( size_t j=0; j < mat.cols(); ++j )
            {
              temp[i] = vec[j] * mat( i, j ) + temp[i];
            }
          }

          vec = temp;

          return vec;
        }
    };
  }
}

#endif // __MSG_MATH_MATRIX_VEC_OPS_H__
