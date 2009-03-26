
#ifndef __MIRAGE_CORE_MATRIX_TRANSFORM_H__
#define __MIRAGE_CORE_MATRIX_TRANSFORM_H__

#include "Core/ITransform.h"
#include "Core/Group.h"

#include "Math/Matrix.h"
#include "Math/Vec.h"
#include "Math/AxisAngle.h"

using namespace Mirage::Math; 

namespace Mirage
{
  namespace Core
  {
    // Forward declaration. 
    class NodeVisitor;

    class MSG_EXPORT MatrixTransform : public Group, public ITransform
    {
      public: 
                                      MatrixTransform();

        inline const Matrix44f&       getMatrix() const { return _matrix; }
        void                          setMatrix( const Matrix44f& mat );        

        void                          preMult( const Matrix44f& mat ); 
        void                          postMult( const Matrix44f& mat );

        virtual void                  traverse( NodeVisitor &nv );

      public: 
     
        Matrix44f                     _matrix;


      protected: 
        
        virtual ~MatrixTransform();


      
    };
  }
}

#endif // __MIRAGE_CORE_MATRIX_TRANSFORM_H__