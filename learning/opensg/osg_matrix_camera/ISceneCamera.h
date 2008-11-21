
#ifndef __I_SCENE_CAMERA_H__
#define __I_SCENE_CAMERA_H__

struct ISceneCamera
{
  virtual                              ~ISceneCamera(){;}
  virtual       gmtl::Vec4d             getXDir()             const   = 0;
  virtual       gmtl::Vec4d             getUpDir()            const   = 0;
  virtual       gmtl::Vec4d             getLookDir()          const   = 0;  
  virtual       gmtl::Vec4d             getPosition()         const   = 0;
  virtual const gmtl::Matrix44d&        getModelViewMatrix()  const   = 0;  
};

#endif // __I_SCENE_CAMERA_H__
