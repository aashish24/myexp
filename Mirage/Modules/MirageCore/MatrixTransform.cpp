
#include "GL/glew.h"
#include "GL/gl.h"

#include "MirageCore/MatrixTransform.h"
#include "MirageCore/NodeVisitor.h"
#include "MirageMath/Utils.h"
#include "MirageMath/Matrix.h"

namespace Mirage
{
  namespace MirageCore
  {
    MatrixTransform::MatrixTransform() : Group(), ITransform(), 
      _matrix()
    {
    }


    MatrixTransform::~MatrixTransform()
    {      
    }
   
    void MatrixTransform::setMatrix( const MirageMath::Matrix44f& mat )
    {
      _matrix = mat;
    }


    void MatrixTransform::preMult( const Matrix44f& mat )
    {
      _matrix.preMult( mat );
    }


    void MatrixTransform::postMult( const Matrix44f& mat )
    {
      _matrix.postMult( mat );
    }


    void MatrixTransform::traverse( NodeVisitor &nv )
    {      
      switch( nv.type() )
      {
        case NodeVisitor::UPDATE: 
        {
          break;
        }
        case NodeVisitor::DRAW: 
        {
          glPushMatrix();
          
          // Multiply current matrix by transformation matrix. 
          glMultMatrixf( _matrix._data );

          // Now traverse all children. 
          Group::traverse( nv );

          // Throw the modified matrix. 
          glPopMatrix();

          break;
        }
      }
    }
  }
}
