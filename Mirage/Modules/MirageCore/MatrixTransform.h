
#ifndef __MIRAGE_CORE_MATRIX_TRANSFORM_H__
#define __MIRAGE_CORE_MATRIX_TRANSFORM_H__

#include "MirageCore/ITransform.h"
#include "MirageCore/Group.h"

#include "MirageMath/Matrix.h"
#include "MirageMath/Vec.h"
#include "MirageMath/AxisAngle.h"

using namespace Mirage::MirageMath; 

namespace Mirage
{
  namespace MirageCore
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