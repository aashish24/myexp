
#ifndef __SCENE_CAMERA_H__
#define __SCENE_CAMERA_H__

#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Generate.h"


class SceneCamera : public ISceneCamera
{
  public: 
                                          SceneCamera();
                                          SceneCamera(const gmtl::Vec3d& xDir, 
                                                      const gmtl::Vec3d& upDir, 
                                                      const gmtl::Vec3d& lookDir, 
                                                      const gmtl::Vec3d& position);
                                                                                     
    virtual                              ~SceneCamera();
    virtual       gmtl::Vec3d             getXDir()     const;        

    virtual       gmtl::Vec3d             getUpDir()    const;         

    virtual       gmtl::Vec3d             getLookDir()  const;
    
    virtual       gmtl::Vec3d             getPosition() const;    
    virtual       void                    setPosition(const gmtl::Vec3d& position);

    virtual const gmtl::Matrix44d&        getViewMatrix() const;
    
    virtual       void                    setBeacon(OSG::NodeRefPtr node);
    virtual const OSG::NodeRefPtr         getBeacon() const;     


  protected: 

                  void                    constructViewMatrix();


  protected:

    // \note Prerequisite that beacon node should contain a transform core. 
    OSG::NodeRefPtr                 _beacon;

    // Camera's X axis.
    gmtl::Vec3d                     _initXDir;

    // Camera's Y axis.
    gmtl::Vec3d                     _initUpDir;

    // Camera's Z axis. 
    gmtl::Vec3d                     _initLookDir;

    // Camera's origin. 
    gmtl::Vec3d                     _initPosition;

    gmtl::Matrix44d                 _viewMatrix;    
};


inline SceneCamera::SceneCamera() : ISceneCamera(),  
  _beacon         (0x00), 
  _initXDir       (1.0, 0.0, 0.0), 
  _initUpDir      (0.0, 1.0, 0.0),
  _initLookDir    (0.0, 0.0, 1.0),
  _initPosition   (1.0, 0.0, 5.0)  
{ 
  this->constructViewMatrix();  
}


inline SceneCamera::SceneCamera(const gmtl::Vec3d& xDir, 
                                const gmtl::Vec3d& upDir, 
                                const gmtl::Vec3d& lookDir, 
                                const gmtl::Vec3d& position) : ISceneCamera(), 
  _initXDir     (xDir), 
  _initUpDir    (upDir), 
  _initLookDir  (lookDir), 
  _initPosition (position)
{ 
  this->constructViewMatrix();
}


inline SceneCamera::~SceneCamera()
{  
}


inline gmtl::Vec3d SceneCamera::getXDir() const
{
  return gmtl::Vec3d(_viewMatrix[0][0], _viewMatrix[1][0], _viewMatrix[2][0]);   
}


inline gmtl::Vec3d SceneCamera::getUpDir() const
{
  return gmtl::Vec3d(_viewMatrix[0][1], _viewMatrix[1][1], _viewMatrix[2][1]);
}


inline gmtl::Vec3d SceneCamera::getLookDir() const
{
  return gmtl::Vec3d(_viewMatrix[0][2], _viewMatrix[1][2], _viewMatrix[2][2]);
}

  
inline gmtl::Vec3d SceneCamera::getPosition() const
{  
  return gmtl::Vec3d(_viewMatrix[0][3], _viewMatrix[1][3], _viewMatrix[2][3]);
}


inline void SceneCamera::setPosition(const gmtl::Vec3d& position) 
{  
  _viewMatrix[0][3] = position[0];
  _viewMatrix[1][3] = position[1];
  _viewMatrix[2][3] = position[2];
}


inline const gmtl::Matrix44d& SceneCamera::getViewMatrix() const
{
  return _viewMatrix;
}


inline void SceneCamera::setBeacon(OSG::NodeRefPtr node)
{
}


inline const OSG::NodeRefPtr SceneCamera::getBeacon() const
{
  return _beacon;
}


inline void SceneCamera::constructViewMatrix()
{
  _viewMatrix.set(_initXDir[0],  _initUpDir[0], _initLookDir[0], _initPosition[0], 
                  _initXDir[1],  _initUpDir[1], _initLookDir[1], _initPosition[1],
                  _initXDir[2],  _initUpDir[2], _initLookDir[2], _initPosition[2],
                  0.0,           0.0,           0.0,             1.0);
}

#endif // __SCENE_CAMERA_H__


