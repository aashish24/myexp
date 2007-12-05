

#ifndef __OGE_INTERFACES_I_CAMERA_H__
#define __OGE_INTERFACES_I_CAMERA_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    { 
      struct ICamera : public Oge::OgeBase::OgeInterfaces::IUnknown
      {
        OGE_DELCARE_SMART_PTR( ICamera );

        enum                  { IID = 0 };

        virtual void          set( float posX,  float posY,  float posZ, 
                                   float viewX, float viewY, float viewZ, 
                                   float upX,   float upY,   float upZ ) = 0;

        virtual float         move( float speed ) = 0; 

        virtual void          moveWorld( float delX, float delY, float delZ ) = 0;

        virtual const float*  getMatrix() = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_CAMERA_H__
