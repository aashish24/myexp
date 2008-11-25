
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
    virtual       gmtl::Vec3d             getXDir()     const;
    virtual       gmtl::Vec3d             getUpDir()    const;
    virtual       gmtl::Vec3d             getLookDir()  const;  
    virtual       gmtl::Vec3d             getPosition() const;    

    virtual const gmtl::Matrix44d&        getModelViewMatrix() const;
    
    virtual       void                    setBeacon(OSG::NodeRefPtr node);
    virtual const OSG::NodeRefPtr         getBeacon() const;     

  protected:

    // \note Prerequisite that beacon node should contain a transform core. 
    OSG::NodeRefPtr                 _beacon;

    // Camera's X axis.
    gmtl::Vec3d                     _xDir;

    // Camera's Y axis.
    gmtl::Vec3d                     _upDir;

    // Camera's Z axis. 
    gmtl::Vec3d                     _lookDir;

    // Camera's origin. 
    gmtl::Vec3d                     _position;

    gmtl::Matrix44d                 _modelViewMatrix;    
};


inline SceneCamera::SceneCamera() : ISceneCamera(),  
  _beacon         (0x00), 
  _xDir           (1.0, 0.0, 0.0), 
  _upDir          (0.0, 1.0, 0.0),
  _lookDir        (0.0, 0.0, 1.0),
  _position       (1.0, 0.0, 5.0)  
{  
  /*_modelViewMatrix.set(_xDir[0],      _xDir[0],     _xDir[0],     _xDir[0], 
                       _upDir[0],     _upDir[0],    _upDir[0],    _upDir[0],
                       _lookDir[0],   _lookDir[0],  _lookDir[0],  _lookDir[0],
                       _position[0],  _position[0], _position[0], _position[0]);*/

  _modelViewMatrix.set(_xDir[0],  _upDir[0], _lookDir[0], _position[0], 
                       _xDir[1],  _upDir[1], _lookDir[1], _position[1],
                       _xDir[2],  _upDir[2], _lookDir[2], _position[2],
                       0.0,       0.0,       0.0,         1.0);  

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


inline gmtl::Vec3d SceneCamera::getXDir() const
{
  return gmtl::Vec3d(_modelViewMatrix[0][0], _modelViewMatrix[1][0], _modelViewMatrix[2][0]);   
}


inline gmtl::Vec3d SceneCamera::getUpDir() const
{
  return gmtl::Vec3d(_modelViewMatrix[0][1], _modelViewMatrix[1][1], _modelViewMatrix[2][1]);
}


inline gmtl::Vec3d SceneCamera::getLookDir() const
{
  return gmtl::Vec3d(_modelViewMatrix[0][2], _modelViewMatrix[1][2], _modelViewMatrix[2][2]);
}

  
inline gmtl::Vec3d SceneCamera::getPosition() const
{  
  return gmtl::Vec3d(_modelViewMatrix[0][3], _modelViewMatrix[1][3], _modelViewMatrix[2][3]);
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


