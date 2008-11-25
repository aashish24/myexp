
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

#include "vpr/Util/Interval.h"

class FlyNavigator : public INavigator, public SceneCamera 
{
  public:
                                FlyNavigator();  
                                FlyNavigator(const gmtl::Vec3d& xDir, 
                                             const gmtl::Vec3d& upDir, 
                                             const gmtl::Vec3d& lookDir, 
                                             const gmtl::Vec3d& position);
    
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

    virtual       void          updateTimeSec(double val);
    
    virtual       void          update(){;}

    virtual       void          reset();

      
  protected:

    bool                        _dofRot[3]; 
    bool                        _dofTrans[3];

    double                      _transSpeed;
    double                      _rotSpeed;
    double                      _fpsFactor;        

    vpr::Interval               _time;
};


inline FlyNavigator::FlyNavigator() : INavigator(), SceneCamera(),
  _transSpeed(15.0), 
  _rotSpeed  (1.0), 
  _fpsFactor (0.05)
{ 
  _time.setNow();

  for(size_t i=0; i < 3; ++i)
  {
    _dofRot[i]    = true;
    _dofTrans[i]  = true; 
  }  
}


inline FlyNavigator::FlyNavigator(const gmtl::Vec3d& xDir, 
                                  const gmtl::Vec3d& upDir, 
                                  const gmtl::Vec3d& lookDir, 
                                  const gmtl::Vec3d& position) : SceneCamera(xDir, upDir, lookDir, position)
{  
}


inline FlyNavigator::~FlyNavigator() 
{
}


inline void FlyNavigator::translate(const gmtl::Vec3d&  dir)
{  
  //std::cout << "mat before mult: " << _viewMatrix << std::endl;
  //std::cout << "calculate mat is : " << gmtl::makeTrans<gmtl::Matrix44d>(dir) << std::endl;
  //std::cout << "_viewMatrix mat is : " << _viewMatrix << std::endl;  
  gmtl::postMult(_viewMatrix, gmtl::makeTrans<gmtl::Matrix44d>(dir * _transSpeed * _fpsFactor));
  //std::cout << "mat after  mult: " << _viewMatrix << std::endl;
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
  gmtl::Matrix44d invMat;
  gmtl::invert(invMat, _viewMatrix);  
  gmtl::Vec3d localAxis;  
  gmtl::xform(localAxis, invMat, _initUpDir);
  gmtl::normalize(localAxis);
  gmtl::postMult(_viewMatrix, gmtl::makeRot<gmtl::Matrix44d>(gmtl::AxisAngled((value * _rotSpeed * _fpsFactor), localAxis)));    
}


inline void FlyNavigator::pitch(double value)
{    
  gmtl::postMult(_viewMatrix, gmtl::makeRot<gmtl::Matrix44d>(gmtl::AxisAngled((value * _rotSpeed * _fpsFactor), _initXDir)));  
}


inline void FlyNavigator::roll(double value)
{
}


inline void FlyNavigator::updateTimeSec(double val)
{
  _fpsFactor = (val - (_time.secd()));  
  _time.setd(val, vpr::Interval::Sec);
  
  //std::cout << "_fpsFactor" << _fpsFactor   << std::endl;
  //std::cout << "_time"      << _time.msec() << std::endl;
}


inline void FlyNavigator::reset()
{
  this->constructViewMatrix();  
}

#endif // __FLY_NAVIGATOR_H__

