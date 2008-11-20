
#ifndef __I_LIME_SCENE_CAMERA_H__
#define __I_LIME_SCENE_CAMERA_H__

struct ILimeSceneCamera
{
  virtual                ~ILimeSceneCamera(){;}
  virtual const double*   getXDir()     const   = 0;
  virtual const double*   getUpDir()    const   = 0;
  virtual const double*   getLookDir()  const   = 0;  
  virtual const double*   getPosition() const   = 0;
};

#endif // __I_LIME_SCENE_CAMERA_H__
