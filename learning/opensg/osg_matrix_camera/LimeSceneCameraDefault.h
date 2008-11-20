
#ifndef __LIME_SCENE_CAMERA_DEFAULT_H__
#define __LIME_SCENE_CAMERA_DEFAULT_H__

class LimeSceneCameraDefault : public ILimeSceneCamera
{
  public: 
                                  LimeSceneCameraDefault();
    virtual                      ~LimeSceneCameraDefault();
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


inline LimeSceneCameraDefault::LimeSceneCameraDefault() : ILimeSceneCamera(),   
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


inline LimeSceneCameraDefault::~LimeSceneCameraDefault()
{  
}


inline const double* LimeSceneCameraDefault::getXDir() const
{
  return _modelViewMatrix[0].getValues();
}


inline const double* LimeSceneCameraDefault::getUpDir() const
{
  return _modelViewMatrix[1].getValues();
}


inline const double* LimeSceneCameraDefault::getLookDir() const
{
  return _modelViewMatrix[2].getValues();
}

  
inline const double* LimeSceneCameraDefault::getPosition() const
{  
  return _modelViewMatrix[3].getValues();
}


inline void LimeSceneCameraDefault::move(const OSG::Vec3d dir)
{
  OSG::Matrix4d transMatrix;
  transMatrix.setTranslate(dir); 

  _modelViewMatrix.multLeft(transMatrix);  
}


inline void LimeSceneCameraDefault::rotate(const OSG::Vec3d rot)
{
}


inline const OSG::Matrix4d& LimeSceneCameraDefault::getModelViewMatrix() const
{
  return _modelViewMatrix;
}

inline void LimeSceneCameraDefault::setBeacon(OSG::NodeRefPtr node)
{
}


inline OSG::NodeRefPtr LimeSceneCameraDefault::getBeacon()
{
  return _beacon;
}

#endif // __I_LIME_SCENE_CAMERA_H__

