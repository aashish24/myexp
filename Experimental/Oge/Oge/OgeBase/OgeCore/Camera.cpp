
#include "Oge/OgeBase/OgeCore/Camera.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      OgeInterfaces::IUnknown* Camera::queryInterface( const unsigned long& iid )
      {        
        return 0x00;
      }

      void Camera::set( float posX,  float posY,   float posZ, 
                           float viewX, float viewY,  float viewZ, 
                           float upX,   float upY,    float upZ )
      {
        _pos  = gmtl::Vec3f( posX, posY, posZ );
        _view = gmtl::Vec3f( viewX, viewY, viewZ );
        _up   = gmtl::Vec3f( upX, upY, upZ );
      }


      float Camera::move( float speed ) 
      {
        gmtl::Vec3f dir = _view - _pos;
        gmtl::normalize( dir );

        _pos = _pos + dir * speed;

        return 1.0;
      }


      void Camera::moveWorld( float delX, float delY, float delZ )
      {
        gmtl::Vec3f dir = gmtl::Vec3f( 1.0 * delX, 1.0 * delY, 1.0 * delZ ); 
        _view = _view + dir;
        _pos  = _pos + dir;
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

