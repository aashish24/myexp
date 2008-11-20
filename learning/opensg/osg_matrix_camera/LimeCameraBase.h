
#ifndef __LIME_CAMERA_BASE_H__
#define __LIME_CAMERA_BASE_H__

#include "ILimeCamera.h"

class LimeCameraVrj  : public ILimeCamera
{
  public: 
    enum AttachToBeaconMode
    {
      POSITION        = 0, 
      ORIENTATION     = 1,
      SCALE           = 2 
    };

                  LimeCameraVrj();
    virtual      ~LimeCameraVrj();

    virtual const OSG::Vec4f& getPosition()   const; 
    virtual const OSG::Vec4f& getUpDir()      const;
    virtual const OSG::Vec4f& getLookDir()    const;
    virtual const OSG::Vec4f& getXDir()       const;

    virtual void              set3dCamera(OSG::MatrixCameraRefPtr camera);

    virtual void              setVrjModelViewMatrix (const OSG::Matrix& mat);
    virtual void              setVrjProjectionMatrix(const OSG::Matrix& mat);

    virtual void              evaluate();   

    virtual void              move(const OSG::Vec3f& dir);

  protected: 

    OSG::MatrixCameraRefPtr _camera;
    OSG::Matrix             _modelViewMatrix;
    
    AttachToBeaconMode      _abMode;
    bool                    _useBeacon;
};


inline LimeCameraVrj::LimeCameraVrj() : ILimeCamera(), 
  _camera         (0x00), 
  _modelViewMatrix(1.0, 0.0, 0.0, 0.0,
                   0.0, 1.0, 0.0, 0.0,
                   0.0, 0.0,-1.0, 10.0,
                   0.0, 0.0, 0.0, 1.0), 
  _abMode         (POSITION), 
  _useBeacon      (false)      
{
}


inline LimeCameraVrj::~LimeCameraVrj()
{
}


inline const OSG::Vec4f& LimeCameraVrj::getPosition() const
{
  return _modelViewMatrix[3];
}


inline const OSG::Vec4f& LimeCameraVrj::getUpDir() const
{
  return _modelViewMatrix[1];
}


inline const OSG::Vec4f& LimeCameraVrj::getLookDir() const
{
  return _modelViewMatrix[2];
}
    

inline const OSG::Vec4f& LimeCameraVrj::getXDir() const
{
  return _modelViewMatrix[0];
}


inline void LimeCameraVrj::set3dCamera(OSG::MatrixCameraRefPtr camera)
{
  _camera = camera;
  _camera->setUseBeacon(false);
}


inline void LimeCameraVrj::move(const OSG::Vec3f& dir)
{
  OSG::Matrix transMatrix;
  transMatrix.setTranslate(dir); 
  _modelViewMatrix.multLeft(transMatrix);  
}  


inline void LimeCameraVrj::evaluate()
{
  // Calculate project and modelview matrix here. 
  OSG::Vec4f x    (this->getXDir());     
  OSG::Vec4f up   (this->getUpDir());    
  OSG::Vec4f look (this->getLookDir());  
  OSG::Vec4f pos  (this->getPosition()); 

//   OSG::Matrix  matrix( x[0],     up[0],   look[0],      0.0,
//                        x[1],     up[1],   look[1],      0.0,
//                        x[2],     up[2],   look[2],      0.0,
//                        -((x[0]*pos[0])     - (x[1]*pos[1])     - (x[2]*pos[2])),
//                        -((up[0]*pos[0])    - (up[1]*pos[1])    - (up[2]*pos[2])),
//                        -((look[0]*pos[0])  - (look[1]*pos[1])  - (look[2]*pos[2])),

  // OSG takes row major args. 
  OSG::Matrix matrix(x[0],    x[1],    x[2],    -((x[0]*pos[0])     - (x[1]*pos[1])     - (x[2]*pos[2])),
                     up[0],   up[1],   up[2],   -((up[0]*pos[0])    - (up[1]*pos[1])    - (up[2]*pos[2])),
                     look[0], look[1], look[2], -((look[0]*pos[0])  - (look[1]*pos[1])  - (look[2]*pos[2])),
                     0.0,     0.0,     0.0,     1.0);

  if(_useBeacon) 
  {
    // Implement this. 
  }
  else
  {
    //std::cout << "Matrix is " << std::endl;
    //std::cout << matrix       << std::endl;

    _camera->setModelviewMatrix(matrix);
  }  
}

#endif // __LIME_CAMERA_H__
