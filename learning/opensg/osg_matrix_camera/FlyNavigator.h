
#ifndef __FLY_NAVIGATOR_H__
#define __FLY_NAVIGATOR_H__

#include "INavigator.h"
#include "SceneCamera.h"

// OpenSG includes. 
#include "OpenSG/OSGMatrix.h"
#include "OpenSG/OSGVector.h"

// GMTL includes. 
#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Generate.h"
#include "gmtl/Vec.h"
#include "gmtl/AxisAngle.h"
#include "gmtl/Xforms.h"

class FlyNavigator : public INavigator, public SceneCamera 
{
  public:
                                FlyNavigator();  
    
    virtual                    ~FlyNavigator();

    virtual       void          translate(const gmtl::Vec3d&  dir); 
    
    virtual       void          translate(double val1, double val2, double val3);

    virtual       void          rotate(const gmtl::Quatd& quat);
 
    virtual       void          rotate(const gmtl::AxisAngled& aAngle);

    virtual       void          rotate(double angle, double x, double y, double z);  

    virtual       void          rotate(double x, double y, double z);    

    virtual       void          setDofRot   (bool val1, bool val2, bool val3);
    virtual       void          setDofTrans (bool val1, bool val2, bool val3);

    virtual       void          yaw   (double angle);
 
    virtual       void          pitch (double angle);

    virtual       void          roll  (double angle);


  protected:

    bool                        _dofRot[3]; 
    bool                        _dofTrans[3];        
};


inline FlyNavigator::FlyNavigator() : INavigator(), SceneCamera()    
{    
  for(size_t i=0; i < 3; ++i)
  {
    _dofRot[i]    = true;
    _dofTrans[i]  = true; 
  }  
}


inline FlyNavigator::~FlyNavigator() 
{
}


inline void FlyNavigator::translate(const gmtl::Vec3d&  dir)
{  
  gmtl::preMult(_modelViewMatrix, gmtl::makeTrans<gmtl::Matrix44d>(dir));
} 
 
   
inline void FlyNavigator::translate(double val1, double val2, double val3)
{
}


inline void FlyNavigator::rotate(const gmtl::Quatd& quat)
{
}


inline void FlyNavigator::rotate(const gmtl::AxisAngled& aAngle)
{  
}


inline void FlyNavigator::rotate(double angle, double x, double y, double z)
{
}  


inline void FlyNavigator::rotate(double x, double y, double z)
{
}


inline void FlyNavigator::setDofRot(bool val1, bool val2, bool val3)
{
  _dofRot[0] = val1;
  _dofRot[1] = val2;
  _dofRot[2] = val3;  
}


inline void FlyNavigator::setDofTrans (bool val1, bool val2, bool val3)
{
  _dofTrans[0] = val1;
  _dofTrans[1] = val2;
  _dofTrans[2] = val3;
}


inline void FlyNavigator::yaw(double value)
{
  gmtl::Vec3d axis      (0.0, 1.0, 0.0);  
  gmtl::xform(axis, _modelViewMatrix, axis);
  gmtl::preMult(_modelViewMatrix, gmtl::makeRot<gmtl::Matrix44d>(gmtl::AxisAngled(value, axis)));  
}


inline void FlyNavigator::pitch(double value)
{
  gmtl::Vec3d axis      (1.0, 0.0, 0.0);
  gmtl::preMult(_modelViewMatrix, gmtl::makeRot<gmtl::Matrix44d>(gmtl::AxisAngled(value, axis)));
}


inline void FlyNavigator::roll(double value)
{
}
#endif // __FLY_NAVIGATOR_H__

