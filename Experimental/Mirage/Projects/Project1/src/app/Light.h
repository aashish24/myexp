
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "oge/core/SmartPtr.h"
#include "oge/core/Referenced.h"

#include "gmtl/Vec.h"

class Light : public oge::core::Referenced
{
  public: 

    enum LightEnum
    {
      AMBIENT = 0, 
      DIFFUSE, 
      SPECULAR, 
      POSITION
    };

    Light()
    {
      mAmbient[0]  = 0.1;
      mAmbient[1]  = 0.1;
      mAmbient[2]  = 0.1;

      mDiffuse[0]  = 0.5;
      mDiffuse[1]  = 0.5;
      mDiffuse[2]  = 0.5;

      mSpecular[0] = 0.5;
      mSpecular[1] = 0.5;
      mSpecular[2] = 0.5;

      mPosition[0] = 0.0;
      mPosition[1] = 0.0;
      mPosition[2] = 0.0;
      mPosition[3] = 0.0;
    }

    float*            lightfv( LightEnum param );
    void              lightfv( LightEnum param, gmtl::Vec3f val );  

  protected:
    ~Light()
    {
    }

  private: 
    float             mAmbient[3];
    float             mDiffuse[3];
    float             mSpecular[3];
    float             mPosition[4];
};

inline float* Light::lightfv( Light::LightEnum param )
{
  switch( param )
  {
    case AMBIENT: 
    {
      return &mAmbient[0];
      break;
    }
    case DIFFUSE: 
    {
      return &mDiffuse[0];
      break;
    }
    case SPECULAR:
    {
      return &mSpecular[0];
      break;
    }
    case POSITION:
    {
      return &mPosition[0];
      break;
    }
    default:
    {
      return 0x00;
      break;
    }
  }; 
}

inline void Light::lightfv( Light::LightEnum param, gmtl::Vec3f val )
{
  switch( param )
  {
    case AMBIENT: 
    {
      mAmbient[0] = val[0];
      mAmbient[1] = val[1];
      mAmbient[2] = val[2];
      break;
    }
    case DIFFUSE:
    {
      mDiffuse[0] = val[0];
      mDiffuse[1] = val[1];
      mDiffuse[2] = val[2];
      break;
    }
    case SPECULAR:
    {
      mSpecular[0] = val[0];
      mSpecular[1] = val[1];
      mSpecular[2] = val[2];
      break;
    }
    case POSITION:
    {
      mPosition[0] = val[0];
      mPosition[1] = val[1];
      mPosition[2] = val[2];
      mPosition[3] = 1.0;
      break;
    }
  };
}
#endif // __LIGHT_H__
