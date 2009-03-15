
#include "MirageCore/MatrixTransform.h"
#include "MirageCore/NodeVisitor.h"

#include "GL/glew.h"
#include "GL/gl.h"

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


    const MirageMath::Matrix44f&  MatrixTransform::getMatrix() const
    {
      return _matrix;
    }


    void MatrixTransform::setMatrix( const MirageMath::Matrix44f& mat )
    {
      _matrix = mat;
    }


    const MirageMath::Vec3f& MatrixTransform::getTranslate() const
    {
      return MirageMath::Vec3f();
    }


    void MatrixTransform::setTranslate( const MirageMath::Vec3f trans )
    {
    }


    // \todo Add rotate functions. 

    // \todo Add scale functions.        

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
