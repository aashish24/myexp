
#ifndef __OGE_INTERFACES_I_CAMERA_H__
#define __OGE_INTERFACES_I_CAMERA_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    { 
      // Interface for the camera class is not yet completed. 
      struct ICamera : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( ICamera );

        enum                  { IID = 5267652420 };

        virtual void          set( float posX,  float posY,  float posZ, 
                                   float viewX, float viewY, float viewZ, 
                                   float upX,   float upY,   float upZ ) = 0;        

        virtual const float&  getSpeed() const = 0;
        virtual void          setSpeed( const float& speed ) = 0;

        virtual const float&  getRotationSpeed() const = 0;
        virtual void          setRotationSpeed( const float& rotationSpeed ) = 0;
        
        virtual void          move( float delX, float delY, float delZ ) = 0; 
        virtual void          slide( float delX, float delY, float delZ ) = 0; 

        // Camera will rotate about its own axis. 
        virtual void          rotate( float angleX, float vecX, float vecY, float vecZ ) = 0;

        // For this we would need an angle and a vector about which camera will rotate. 
        virtual void          pitch( float angleX ) = 0; 

        // For this we would need an angle and a vector about which camera will rotate. 
        virtual void          yaw( float angleY ) = 0; 

        // For this we would need an angle and a vector about which camera will rotate. 
        virtual void          roll( float angleZ ) = 0; 

        virtual const float*  getMatrix() = 0;

        virtual void          reset() = 0;  
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_CAMERA_H__
