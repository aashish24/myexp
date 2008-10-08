
#ifndef _NAVIGATOR_BASE_H_
#define _NAVIGATOR_BASE_H_

#include <vrj/Kernel/App.h>
#include <vpr/Util/Interval.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/PositionProxy.h>

#include <gmtl/Matrix.h>

class NavigatorBase
{
  public:
    typedef NavigatorBase Self;
    
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             NavigatorBase(vrj::App *pApp);
    virtual ~NavigatorBase(void);
    
    /*=======================================================================*/
    /* Access                                                                */
            
    vrj::App const *getApp(void) const;
    vrj::App       *getApp(void);
    
    float getRotateFactor(void) const;
    float getFPSNormalizedRotateFactor(void) const;
    void  setRotateFactor(float rotFactor);
    
    float getTranslateFactor(void) const;
    float getFPSNormalizedTranslateFactor(void) const;
    void  setTranslateFactor(float transFactor);
    
    bool  getEnabled(void) const;
    void  setEnabled(bool enabled);
    
    /*=======================================================================*/
    /* Initialization                                                        */
            
    virtual void initialize(void);
    
    /*=======================================================================*/
    /* Navigation                                                            */
    
    virtual void updateTime(vpr::Interval   const &time     );
    virtual void navigate  (gmtl::Matrix44f const &matrix,
                            gmtl::Matrix44f       &newMatrix);
                              
  protected:
    bool getInitialized(void) const;
    
    float readAdjustedAnalog(gadget::AnalogInterface &analog,
                             bool                    &hasData,
                             float                    deadZone = 0.025f) const;
                             
    float adjustAnalog      (float                    analogIn,
                             float                    deadZone = 0.025f) const;
        
    bool           mInitialized;
    bool           mEnabled;
    
  private:
    vrj::App      *mApp;
    vpr::Interval  mTime;
    float          mFPSNormalizationFactor;
    float          mRotateFactor;
    float          mTranslateFactor;
    
};

/*=======================================================================*/
/* Access                                                                */

inline vrj::App const *
NavigatorBase::getApp(void) const
{
    return mApp;
}

inline vrj::App *
NavigatorBase::getApp(void)
{
    return mApp;
}

inline float
NavigatorBase::getRotateFactor(void) const
{
    return mRotateFactor;
}

inline float
NavigatorBase::getFPSNormalizedRotateFactor(void) const
{
    return mFPSNormalizationFactor * mRotateFactor;
}

inline void
NavigatorBase::setRotateFactor(float rotFactor)
{
    mRotateFactor = rotFactor;
}

inline float
NavigatorBase::getTranslateFactor(void) const
{
    return mTranslateFactor;
}

inline float
NavigatorBase::getFPSNormalizedTranslateFactor(void) const
{
    return mFPSNormalizationFactor * mTranslateFactor;
}

inline void
NavigatorBase::setTranslateFactor(float transFactor)
{
    mTranslateFactor = transFactor;
}

inline bool
NavigatorBase::getEnabled(void) const
{
    return mEnabled;
}

inline void
NavigatorBase::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

inline bool
NavigatorBase::getInitialized(void) const
{
    return mInitialized;
}

#endif // _NAVIGATOR_BASE_H_
