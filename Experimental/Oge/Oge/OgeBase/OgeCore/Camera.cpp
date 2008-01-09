
#include "Oge/OgeBase/OgeCore/Camera.h"



namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      Camera::Camera() : 
        _speed          ( 1.0 ), 
        _rotationSpeed  ( gmtl::Math::deg2Rad( 1.0 ) ),        
        _pos            ( 0.0, 0.0, 50.0 ), 
        _view           ( 0.0, 0.0, 0.0 ), 
        _up             ( 0.0, 1.0, 0.0 ), 
        _u              ( 1.0, 0.0, 0.0 ), 
        _v              ( 0.0, 1.0, 0.0 ), 
        _n              ( 0.0, 0.0, -1.0 ) 
      { 
      }


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


        this->setModelViewMatrix();
      }


      void Camera::setModelViewMatrix()
      {
        _n = _pos - _view;
        
        gmtl::cross( _u, _up, _n );
  
        gmtl::normalize( _n );
        gmtl::normalize( _u );

        gmtl::cross( _v, _n, _u );             
      }


      const float& Camera::getSpeed() const 
      {
        return _speed;
      }


      void Camera::setSpeed( const float& speed ) 
      {
        _speed = speed;
      }


      const float& Camera::getRotationSpeed() const 
      {
        return _rotationSpeed;
      }


      void Camera::setRotationSpeed( const float& rotationSpeed ) 
      {
        _rotationSpeed = rotationSpeed;
      }
      

      void Camera::move( float delX, float delY, float delZ )
      { 
        _pos  = _pos  + gmtl::Vec3f( delX, delY, delZ ) * _speed;
        //_view = _view + gmtl::Vec3f( delX, delY, delZ ) * _speed;
      }


      void Camera::slide( float delX, float delY, float delZ )
      { 
        gmtl::Matrix44f invMat;
        gmtl::Vec3f tempN = _n;
        gmtl::invertFull( invMat, _pitchMatrix );

        tempN = invMat * _n;

        _pos[ 0 ] = _pos[ 0 ] + ( delX * _u[ 0 ] + delY * _v[ 0 ] + delZ * tempN[ 0 ] ) * _speed;  
        _pos[ 1 ] = _pos[ 1 ] + ( delX * _u[ 1 ] + delY * _v[ 1 ] + delZ * tempN[ 1 ] ) * _speed;  
        _pos[ 2 ] = _pos[ 2 ] + ( delX * _u[ 2 ] + delY * _v[ 2 ] + delZ * tempN[ 2 ] ) * _speed; 
      }


      void Camera::rotate( float angle, float vecX, float VecY, float vecZ )
      {
        // Still needs to be implemented. 
      }


      void Camera::pitch( float angleX )
      {   
        angleX = gmtl::Math::deg2Rad( angleX );

        gmtl::Vec3f temp = _v;       

       /* _v.set( ( cos( angleX ) * temp[ 0 ] - sin( angleX ) * _n[ 0 ] ), 
                ( cos( angleX ) * temp[ 1 ] - sin( angleX ) * _n[ 1 ] ),
                ( cos( angleX ) * temp[ 2 ] - sin( angleX ) * _n[ 2 ] ) );

        _n.set( ( sin( angleX ) * temp[ 0 ] + cos( angleX ) * _n[ 0 ] ), 
                ( sin( angleX ) * temp[ 1 ] + cos( angleX ) * _n[ 1 ] ),
                ( sin( angleX ) * temp[ 2 ] + cos( angleX ) * _n[ 2 ] ) );*/

        gmtl::Vec3f tempU = _u;
        gmtl::normalize( tempU );

        gmtl::Matrix44f  rotMat;
        gmtl::AxisAnglef aa( angleX, tempU );
        gmtl::set( rotMat, aa );

        _v = rotMat * _v;
        _n = rotMat * _n;

        _pitchMatrix *= rotMat;
      }


      void Camera::yaw( float angleY )
      { 
        angleY = gmtl::Math::deg2Rad( angleY );

        gmtl::Vec3f temp = _n;
        
        /*_n.set( ( cos( angleY ) * temp[ 0 ] - sin( angleY ) * _u[ 0 ] ), 
                ( cos( angleY ) * temp[ 1 ] - sin( angleY ) * _u[ 1 ] ),
                ( cos( angleY ) * temp[ 2 ] - sin( angleY ) * _u[ 2 ] ) );
        
        _u.set( ( sin( angleY ) * temp[ 0 ] + cos( angleY ) * _u[ 0 ] ), 
                ( sin( angleY ) * temp[ 1 ] + cos( angleY ) * _u[ 1 ] ),
                ( sin( angleY ) * temp[ 2 ] + cos( angleY ) * _u[ 2 ] ) );       */

        gmtl::Matrix44f invMat;
        gmtl::invertFull( invMat, _pitchMatrix );

        gmtl::Vec3f tempV = invMat * _v;
        gmtl::normalize( tempV );

        gmtl::Matrix44f  rotMat;
        gmtl::AxisAnglef aa( angleY, tempV );
        gmtl::set( rotMat, aa );

        _n = invMat * _n;
        _n = rotMat * _n;
        _n = _pitchMatrix * _n;

        _u = rotMat * _u;


        //_v = invMat * _v;
        //gmtl::identity( _pitchMatrix );
      }


      void Camera::roll( float angleZ )
      {   
        angleZ = gmtl::Math::deg2Rad( angleZ );

        gmtl::Vec3f temp = _u;
        
        _u.set( ( cos( angleZ ) * temp[ 0 ] - sin( angleZ ) * _v[ 0 ] ), 
                ( cos( angleZ ) * temp[ 1 ] - sin( angleZ ) * _v[ 1 ] ),
                ( cos( angleZ ) * temp[ 2 ] - sin( angleZ ) * _v[ 2 ] ) );

        _v.set( ( sin( angleZ ) * temp[ 0 ] + cos( angleZ ) * _v[ 0 ] ), 
                ( sin( angleZ ) * temp[ 1 ] + cos( angleZ ) * _v[ 1 ] ),
                ( sin( angleZ ) * temp[ 2 ] + cos( angleZ ) * _v[ 2 ] ) );
      }


      /*void Camera::rotateView( float speed )
      {
        gmtl::Vec3f dir = _view - _pos;

        _view[ 2 ] = _pos[ 2 ] + ( sin( speed ) * dir[ 0 ] + cos( speed ) * dir[ 2 ] );
        _view[ 0 ] = _pos[ 0 ] + ( cos( speed ) * dir[ 0 ] - sin( speed ) * dir[ 2 ] );
      }*/


      /* void Camera::rotatePos( float speed )
        {
          gmtl::Vec3f dir = _pos - _view;
        
          _pos[ 2 ] = _view[ 2 ] + ( sin( speed ) * dir[ 0 ] + cos( speed ) * dir[ 2 ] );
          _pos[ 0 ] = _view[ 0 ] + ( cos( speed ) * dir[ 0 ] - sin( speed ) * dir[ 2 ] );
        }
      */


      const float* Camera::getMatrix()
      {
       /* gmtl::Vec3f pos;
        float temp;

        _n = _pos - _view;
        
        gmtl::cross( _u, _up, _n );

        gmtl::normalize( _n );
        gmtl::normalize( _u );        

        gmtl::cross( _v, _n, _u );
        */

        /*gmtl::normalize( _n );
        gmtl::normalize( _u );        
        gmtl::normalize( _v ); */       

        gmtl::Vec3f pos;
        float temp = gmtl::dot( -_pos, _u );
        pos[0] = temp;
        temp = 0.0;
              
        temp = gmtl::dot( -_pos, _v );
        pos[1] = temp;
        temp = 0.0;
        
        temp = gmtl::dot( -_pos, _n );
        pos[2]  = temp;

        _matrix.set( _u[0], _u[1], _u[2], pos[0], 
                     _v[0], _v[1], _v[2], pos[1], 
                     _n[0], _n[1], _n[2], pos[2], 
                     0.0,  0.0,  0.0,  1.0 );
       
        return _matrix.getData();
      }
    }
  }
}

