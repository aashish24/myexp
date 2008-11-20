
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGVector.h>

class SceneCamera : public OSG::MatrixCamera
{
  public:
                              SceneCamera(); 
    virtual                  ~SceneCamera();

    virtual const OSG::Vec3f& getPosition()   const; 
    virtual const OSG::Vec3f& getUpDir()      const;
    virtual const OSG::Vec3f& getLookDir()    const;
    virtual const OSG::Vec3f& getXDir()       const;

    virtual void              move(OSG::Vec3f& dir);

  private:
    OSG::Vec3f  _position;
    OSG::Vec3f  _upDir;
    OSG::Vec3f  _lookDir;
    OSG::Vec3f  _xDir;  
};


inline SceneCamera::SceneCamera() : OSG::MatrixCamera(),
  _position(0.0, 0.0, 5.0), 
  _upDir   (0.0, 1.0, 0.0), 
  _lookDir (0.0, 0.0, 0.0), 
  _xDir    (1.0, 0.0, 0.0) 
{
}


inline SceneCamera::~SceneCamera()
{  
}


inline const OSG::Vec3f& SceneCamera::getPosition() const
{
  return _position;
}


inline const OSG::Vec3f& SceneCamera::getUpDir() const
{
  return _upDir;
}


inline const OSG::Vec3f& SceneCamera::getLookDir() const
{
  return _lookDir;
}
    

inline const OSG::Vec3f& SceneCamera::getXDir() const
{
  return _xDir;
}

    
inline void SceneCamera::move(OSG::Vec3f& dir)
{
  // \todo Need to implement this. 
  _position = _position + dir;
}

#endif // __CAMERA_H__
 