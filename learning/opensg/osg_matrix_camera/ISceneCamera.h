
#ifndef __I_SCENE_CAMERA_H__
#define __I_SCENE_CAMERA_H__

struct ISceneCamera
{
  virtual                              ~ISceneCamera(){;}
  virtual       gmtl::Vec3d             getXDir()                               const   = 0;  
  
  virtual       gmtl::Vec3d             getUpDir()                              const   = 0;  

  virtual       gmtl::Vec3d             getLookDir()                            const   = 0;  

  virtual       gmtl::Vec3d             getPosition()                           const   = 0;
  virtual       void                    setPosition(const gmtl::Vec3d& pos)             = 0;

  virtual const gmtl::Matrix44d&        getViewMatrix()  const   = 0;  
};

#endif // __I_SCENE_CAMERA_H__
