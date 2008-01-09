
#ifndef  __OGE_CORE_CAMERA_H__
#define  __OGE_CORE_CAMERA_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/ICamera.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/Pointer.h"

#include "gmtl/Math.h"
#include "gmtl/Vec.h"
#include "gmtl/VecOps.h"
#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/AxisAngleOps.h"
#include "gmtl/AxisAngle.h"
#include "gmtl/Generate.h"

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

          Camera();

          virtual IUnknown*                         queryInterface( const unsigned long& iid );
          
          virtual void                              set( float posX,  float posY,   float posZ, 
                                                         float viewX, float viewY,  float viewZ, 
                                                         float upX,   float upY,    float upZ );

          
          virtual void                              setModelViewMatrix();


          virtual const float&                      getSpeed() const;
          virtual void                              setSpeed( const float& speed );

          virtual const float&                      getRotationSpeed() const;
          virtual void                              setRotationSpeed( const float& rotationSpeed );

          virtual void                              move( float delX, float delY, float delZ ); 

          virtual void                              slide( float delX, float delY, float delZ ); 

          virtual void                              rotate( float angle, float vecX, float VecY, float vecZ );

          virtual void                              pitch( float angleX );

          virtual void                              yaw( float angleY );

          virtual void                              roll( float angleZ );
          
          const float*                              getMatrix();


        protected:
        
          virtual ~Camera(){;}
        

        protected: 

          float                                     _speed;

          float                                     _rotationSpeed;

          float                                     _pitch;


          gmtl::Vec3f                               _pos;
          gmtl::Vec3f                               _view;
          gmtl::Vec3f                               _up;

          gmtl::Vec3f                               _u;
          gmtl::Vec3f                               _v;
          gmtl::Vec3f                               _n;


          gmtl::Matrix44f                           _matrix;
          gmtl::Matrix44f                           _pitchMatrix;
      };
    }
  }
}

#endif // __OGE_CORE_CAMERA_H__
