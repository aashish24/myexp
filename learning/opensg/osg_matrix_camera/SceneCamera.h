
#ifndef __SCENE_CAMERA_H__
#define __SCENE_CAMERA_H__

#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Generate.h"


class SceneCamera : public ISceneCamera
{
  public: 
                                          SceneCamera();
    virtual                              ~SceneCamera();
    virtual       gmtl::Vec4d             getXDir()     const;
    virtual       gmtl::Vec4d             getUpDir()    const;
    virtual       gmtl::Vec4d             getLookDir()  const;  
    virtual       gmtl::Vec4d             getPosition() const;

    //virtual       void            move  (const OSG::Vec3d dir);
    //virtual       void            rotate(const OSG::Vec3d rot);

    virtual const gmtl::Matrix44d&        getModelViewMatrix() const;
    
    virtual       void                    setBeacon(OSG::NodeRefPtr node);
    virtual const OSG::NodeRefPtr         getBeacon() const;


  protected:

    // \note Prerequisite that beacon node should contain a transform core. 
    OSG::NodeRefPtr                 _beacon;

    gmtl::Matrix44d                 _modelViewMatrix;
};


inline SceneCamera::SceneCamera() : ISceneCamera(),  
  _beacon         (0x00)  
{  
  _modelViewMatrix.set(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0,-1.0, 0.0,
                       0.0, 0.0, 5.0, 1.0);

  try
  {    
  }
  catch(std::bad_alloc& e)
  {
  }
  catch(...)
  {
  }
}


inline SceneCamera::~SceneCamera()
{  
}


inline gmtl::Vec4d SceneCamera::getXDir() const
{
  return gmtl::Vec4d(_modelViewMatrix[0][0], _modelViewMatrix[0][1], 
                     _modelViewMatrix[0][2], _modelViewMatrix[0][3]);   
}


inline gmtl::Vec4d SceneCamera::getUpDir() const
{
  return gmtl::Vec4d(_modelViewMatrix[1][0], _modelViewMatrix[1][1], 
                     _modelViewMatrix[1][2], _modelViewMatrix[1][3]);
}


inline gmtl::Vec4d SceneCamera::getLookDir() const
{
  return gmtl::Vec4d(_modelViewMatrix[2][0], _modelViewMatrix[2][1], 
                     _modelViewMatrix[2][2], _modelViewMatrix[2][3]);
}

  
inline gmtl::Vec4d SceneCamera::getPosition() const
{  
  return gmtl::Vec4d(_modelViewMatrix[3][0], _modelViewMatrix[3][1], 
                     _modelViewMatrix[3][2], _modelViewMatrix[3][3]);
}


// inline void SceneCamera::move(const OSG::Vec3d dir)
// {
//   OSG::Matrix4d transMatrix;
//   transMatrix.setTranslate(dir); 
// 
//   _modelViewMatrix.multLeft(transMatrix);  
// }
// 
// 
// inline void SceneCamera::rotate(const OSG::Vec3d rot)
// {


inline const gmtl::Matrix44d& SceneCamera::getModelViewMatrix() const
{
  return _modelViewMatrix;
}


inline void SceneCamera::setBeacon(OSG::NodeRefPtr node)
{
}


inline const OSG::NodeRefPtr SceneCamera::getBeacon() const
{
  return _beacon;
}

#endif // __SCENE_CAMERA_H__


