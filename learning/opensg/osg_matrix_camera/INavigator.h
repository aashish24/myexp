
#ifndef __I_NAVIGATOR_H__
#define __I_NAVIGATOR_H__


class INavigator
{
  public: 

    virtual                    ~INavigator(){;}

    virtual void                translate(const gmtl::Vec3d&  dir)                    = 0;    

    virtual void                rotate(const gmtl::Quatd& quat)                       = 0;
 
    virtual void                rotate(const gmtl::AxisAngled& aAngle)                = 0;    

    virtual void                setDofRot   (bool val1, bool val2, bool val3)         = 0;
    virtual void                setDofTrans (bool val1, bool val2, bool val3)         = 0;    
  
    virtual void                yaw   (double angle)                                  = 0;
 
    virtual void                pitch (double angle)                                  = 0;

    virtual void                roll  (double angle)                                  = 0;

    // \note Need to call this before we make call to any transform functions. 
    virtual void                updateTimeSec(double val)                             = 0;

    virtual void                update()                                              = 0;

    virtual void                reset()                                               = 0;     
};

#endif // __I_NAVIGATOR_H__

