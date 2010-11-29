
#ifndef __I_SCENE_CAMERA_H__
#define __I_SCENE_CAMERA_H__

struct ISceneCamera
{
  virtual                ~ISceneCamera(){;}
  virtual const double*   getXDir()     const   = 0;
  virtual const double*   getUpDir()    const   = 0;
  virtual const double*   getLookDir()  const   = 0;  
  virtual const double*   getPosition() const   = 0;
};

#endif // __I_SCENE_CAMERA_H__
