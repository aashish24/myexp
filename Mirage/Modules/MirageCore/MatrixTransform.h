
#ifndef __MIRAGE_CORE_MATRIX_TRANSFORM_H__
#define __MIRAGE_CORE_MATRIX_TRANSFORM_H__

#include "MirageCore/ITransform.h"
#include "MirageCore/Group.h"

#include "MirageMath/Matrix.h"
#include "MirageMath/Vector.h"

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

        const MirageMath::Matrix44f&  getMatrix() const;
        void                          setMatrix( const MirageMath::Matrix44f& mat );


        const MirageMath::Vec3f&      getTranslate() const;
        void                          setTranslate( const MirageMath::Vec3f trans );

        // \todo Add rotate functions. 

        // \todo Add scale functions.        

        virtual void                  traverse( NodeVisitor &nv );

      public: 
     
        MirageMath::Matrix44f         _matrix;


      protected: 
        
        virtual ~MatrixTransform();


      
    };
  }
}

#endif // __MIRAGE_CORE_MATRIX_TRANSFORM_H__