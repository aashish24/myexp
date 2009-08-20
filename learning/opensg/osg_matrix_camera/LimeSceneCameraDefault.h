
#ifndef __SCENE_CAMERA_DEFAULT_H__
#define __SCENE_CAMERA_DEFAULT_H__

class SceneCameraDefault : public ILimeSceneCamera
{
  public: 
                                  SceneCameraDefault();
    virtual                      ~SceneCameraDefault();
    virtual const double*         getXDir()     const;
    virtual const double*         getUpDir()    const;
    virtual const double*         getLookDir()  const;  
    virtual const double*         getPosition() const;

    virtual       void            move  (const OSG::Vec3d dir);
    virtual       void            rotate(const OSG::Vec3d rot);

    virtual const OSG::Matrix4d&  getModelViewMatrix() const;
    
    virtual       void            setBeacon(OSG::NodeRefPtr node);
    virtual       OSG::NodeRefPtr getBeacon();
  
  protected:

    // \note Prerequisite that beacon node should contain a transform core. 
    OSG::NodeRefPtr               _beacon;

    OSG::Matrix4d                 _modelViewMatrix;
};


inline SceneCameraDefault::SceneCameraDefault() : ILimeSceneCamera(),   
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


inline SceneCameraDefault::~SceneCameraDefault()
{  
}


inline const double* SceneCameraDefault::getXDir() const
{
  return _modelViewMatrix[0].getValues();
}


inline const double* SceneCameraDefault::getUpDir() const
{
  return _modelViewMatrix[1].getValues();
}


inline const double* SceneCameraDefault::getLookDir() const
{
  return _modelViewMatrix[2].getValues();
}

  
inline const double* SceneCameraDefault::getPosition() const
{  
  return _modelViewMatrix[3].getValues();
}


inline void SceneCameraDefault::move(const OSG::Vec3d dir)
{
  OSG::Matrix4d transMatrix;
  transMatrix.setTranslate(dir); 

  _modelViewMatrix.multLeft(transMatrix);  
}


inline void SceneCameraDefault::rotate(const OSG::Vec3d rot)
{
}


inline const OSG::Matrix4d& SceneCameraDefault::getModelViewMatrix() const
{
  return _modelViewMatrix;
}

inline void SceneCameraDefault::setBeacon(OSG::NodeRefPtr node)
{
}


inline OSG::NodeRefPtr SceneCameraDefault::getBeacon()
{
  return _beacon;
}

#endif // __SCENE_CAMERA_DEFAULT_H__


