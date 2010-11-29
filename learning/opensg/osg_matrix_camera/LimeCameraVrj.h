
#ifndef __LIME_CAMERA_BASE_H__
#define __LIME_CAMERA_BASE_H__

#include "ILimeCamera.h"

class LimeVrjCamera  : public ILimeCamera
{
  public: /*
    enum AttachToBeaconMode
    {
      POSITION        = 0, 
      ORIENTATION     = 1,
      SCALE           = 2 */

                  LimeVrjCamera();
    virtual      ~LimeVrjCamera();    

    ILimeSceneCamera*         getSceneCamera();
    virtual void              setSceneCamera(ILimeSceneCamera* sCamera);

    virtual void              setOSGCamera(OSG::MatrixCameraRefPtr osgCamera);
    
    virtual void              evaluate();    

  protected:
 
    OSG::MatrixCameraRefPtr _osgCamera;
    ILimeSceneCamera*       _sceneCamera;
};


inline LimeVrjCamera::LimeVrjCamera() : ILimeCamera(),
  _osgCamera      (0x00),
  _sceneCamera    (0x00), 
  _modelViewMatrix(1.0, 0.0, 0.0, 0.0,
                   0.0, 1.0, 0.0, 0.0,
                   0.0, 0.0,-1.0, 10.0,
                   0.0, 0.0, 0.0, 1.0)
{  
}


inline LimeVrjCamera::~LimeVrjCamera()
{  
}

inline ILimeSceneCamera* LimeVrjCamera::getSceneCamera()  
{
  return _sceneCamera;
}


inline void LimeVrjCamera::setSceneCamera(ILimeSceneCamera* sCamera)
{ 
 _osgCamera = sCamera;  
}


inline void LimeVrjCamera::setOSGCamera(OSG::MatrixCameraRefPtr osgCamera)
{
  _osgCamera = osgCamera;  
}


inline void LimeVrjCamera::evaluate()
{
  // Calculate project and modelview matrix here. 
  OSG::Vec4f x    (_sceneCamera->getXDir());     
  OSG::Vec4f up   (_sceneCamera->getUpDir());    
  OSG::Vec4f look (_sceneCamera->getLookDir());  
  OSG::Vec4f pos  (_sceneCamera->getPosition());

  // OSG takes row major args. 
  OSG::Matrix matrix(x[0],    x[1],    x[2],    -((x[0]*pos[0])     - (x[1]*pos[1])     - (x[2]*pos[2])),
                     up[0],   up[1],   up[2],   -((up[0]*pos[0])    - (up[1]*pos[1])    - (up[2]*pos[2])),
                     look[0], look[1], look[2], -((look[0]*pos[0])  - (look[1]*pos[1])  - (look[2]*pos[2])),
                     0.0,     0.0,     0.0,     1.0);  
    
  _osgCamera->setModelviewMatrix(matrix);
}

#endif // __LIME_CAMERA_H__

