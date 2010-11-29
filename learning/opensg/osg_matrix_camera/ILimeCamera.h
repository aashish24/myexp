
#ifndef __I_LIME_CAMERA_H__
#define __I_LIME_CAMERA_H__

class ILimeCamera
{
  public: 
  virtual                  ~ILimeCamera(){;}

  virtual void              evaluate()        = 0;
};

#endif // __I_LIME_CAMERA_H__

