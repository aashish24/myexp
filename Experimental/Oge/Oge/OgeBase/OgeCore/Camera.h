
#ifndef  __OGE_CORE_CAMERA_H__
#define  __OGE_CORE_CAMERA_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/ICamera.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/Pointer.h"

#include "gmtl/Vec.h"
#include "gmtl/VecOps.h"
#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Math.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      class OGE_EXPORT Camera : 
        public OgeBase::OgeInterfaces::ICamera, 
        public OgeBase::OgeCore::Referenced
      {
        public:
                
          OGE_DELCARE_SMART_PTR( Camera );

          IMPLEMENT_IUNKNOWN_MEMBERS( Camera, OgeBase::OgeCore::Referenced );
          
          typedef OgeBase::OgeInterfaces::IUnknown  IUnknown;

          virtual IUnknown*                         queryInterface( const unsigned long& iid );
          
          void                                      set( float posX,  float posY,   float posZ, 
                                                         float viewX, float viewY,  float viewZ, 
                                                         float upX,   float upY,    float upZ );

          float                                     move( float speed );

          void                                      moveWorld( float delX, float delY, float delZ  );

          const float*                              getMatrix();


        protected:
        
          virtual ~Camera(){;}
        

        protected: 

          gmtl::Vec3f                               _pos;
          gmtl::Vec3f                               _view;
          gmtl::Vec3f                               _up;

          gmtl::Matrix44f                           _matrix;
        
      };
    }
  }
}

#endif // __OGE_CORE_CAMERA_H__
