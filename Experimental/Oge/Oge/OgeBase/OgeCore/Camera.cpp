
#include "Oge/OgeBase/OgeCore/Camera.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      OgeBase::OgeInterfaces::IUnknown* Camera::queryInterface( const unsigned long& iid )
      {    
        switch( iid )
        {
          case OgeBase::OgeInterfaces::IUnknown::IID :
          case OgeBase::OgeInterfaces::ICamera::IID: 
          {
            return static_cast< OgeBase::OgeInterfaces::ICamera* >( this );
          }
          default:
          {
            return 0x00;
          }
        };
      }


      void Camera::set( float posX,  float posY,   float posZ, 
                           float viewX, float viewY,  float viewZ, 
                           float upX,   float upY,    float upZ )
      {
        _pos  = gmtl::Vec3f( posX, posY, posZ );
        _view = gmtl::Vec3f( viewX, viewY, viewZ );
        _up   = gmtl::Vec3f( upX, upY, upZ );
      }


      void Camera::move( float speed ) 
      {
        gmtl::Vec3f dir = _view - _pos;
        //gmtl::normalize( dir );

        _pos  = _pos + dir * speed;
        _view = _view + dir * speed;
      }


      void Camera::rotateView( float speed )
      {
        gmtl::Vec3f dir = _view - _pos;

        _view[ 2 ] = _pos[ 2 ] + ( sin( speed ) * dir[ 0 ] + cos( speed ) * dir[ 2 ] );
        _view[ 0 ] = _pos[ 0 ] + ( cos( speed ) * dir[ 0 ] - sin( speed ) * dir[ 2 ] );
      }


      void Camera::rotatePos( float speed )
      {
        gmtl::Vec3f dir = _pos - _view;
      
        _pos[ 2 ] = _view[ 2 ] + ( sin( speed ) * dir[ 0 ] + cos( speed ) * dir[ 2 ] );
        _pos[ 0 ] = _view[ 0 ] + ( cos( speed ) * dir[ 0 ] - sin( speed ) * dir[ 2 ] );
      }


      const float* Camera::getMatrix()
      {
        gmtl::Vec3f u, v, n, pos;
        float temp;

        n = _pos - _view;
        
        gmtl::cross( u, _up, n );

        gmtl::normalize( n );
        gmtl::normalize( u );        

        gmtl::cross( v, n, u );

        temp = gmtl::dot( -_pos, u );
        pos[0] = temp;
        temp = 0.0;
              
        temp = gmtl::dot( -_pos, v );
        pos[1] = temp;
        temp = 0.0;
        
        temp = gmtl::dot( -_pos, n );
        pos[2]  = temp;

        _matrix.set( u[0], u[1], u[2], pos[0], 
                     v[0], v[1], v[2], pos[1], 
                     n[0], n[1], n[2], pos[2], 
                     0.0,  0.0,  0.0,  1.0 );
       
        return _matrix.getData();
      }
    }
  }
}

