
#ifndef __SCENE_CAMERA_H__
#define __SCENE_CAMERA_H__

class SceneCamera : public ILimeSceneCamera
{
  public: 
                                  SceneCamera();
    virtual                      ~SceneCamera();
    virtual const double*         getXDir()     const;
    virtual const double*         getUpDir()    const;
    virtual const double*         getLookDir()  const;  
    virtual const double*         getPosition() const;

    //virtual       void            move  (const OSG::Vec3d dir);
    //virtual       void            rotate(const OSG::Vec3d rot);

    virtual const OSG::Matrix4d&  getModelViewMatrix() const;
    
    virtual       void            setBeacon(OSG::NodeRefPtr node);
    virtual       OSG::NodeRefPtr getBeacon();
  
  protected:

    // \note Prerequisite that beacon node should contain a transform core. 
    OSG::NodeRefPtr               _beacon;

    OSG::Matrix4d                 _modelViewMatrix;
};


inline SceneCamera::SceneCamera() : ILimeSceneCamera(),   
  _modelViewMatrix(1.0, 0.0, 0.0, 0.0,
                   0.0, 1.0, 0.0, 0.0,
                   0.0, 0.0,-1.0, 5.0,
                   0.0, 0.0, 0.0, 1.0)
{
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


inline const double* SceneCamera::getXDir() const
{
  return _modelViewMatrix[0].getValues();
}


inline const double* SceneCamera::getUpDir() const
{
  return _modelViewMatrix[1].getValues();
}


inline const double* SceneCamera::getLookDir() const
{
  return _modelViewMatrix[2].getValues();
}

  
inline const double* SceneCamera::getPosition() const
{  
  return _modelViewMatrix[3].getValues();
}


inline void SceneCamera::move(const OSG::Vec3d dir)
{
  OSG::Matrix4d transMatrix;
  transMatrix.setTranslate(dir); 

  _modelViewMatrix.multLeft(transMatrix);  
}


inline void SceneCamera::rotate(const OSG::Vec3d rot)
{
}


inline const OSG::Matrix4d& SceneCamera::getModelViewMatrix() const
{
  return _modelViewMatrix;
}

inline void SceneCamera::setBeacon(OSG::NodeRefPtr node)
{
}


inline OSG::NodeRefPtr SceneCamera::getBeacon()
{
  return _beacon;
}

#endif // __SCENE_CAMERA_H__


