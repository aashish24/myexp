
#ifndef _NAVIGATOR_ADAPTER_BASE_H_
#define _NAVIGATOR_ADAPTER_BASE_H_

#include <NavigatorBase.h>

class NavigatorAdapterBase
{
  public:
    typedef NavigatorAdapterBase Self;
    
    // Navigation mode: whether the transformation to apply represents the changes since last frame (default)
    // or whether it's absolute
    enum NavigationModeE{
    	NAV_INCREMENTAL = 0,
    	NAV_FULL
    };
    
  
    /*=======================================================================*/
    /* Construction/Destruction                                              */
             
             NavigatorAdapterBase(void);
    virtual ~NavigatorAdapterBase(void);
    
    /*=======================================================================*/
    /* Navigator                                                             */
    
    NavigatorBase *getNavigator(void) const;
    void           setNavigator(NavigatorBase *navigator);
    void 		   setNavigationMode(NavigationModeE);
    
    /*=======================================================================*/
    /* Forwarding                                                            */
    
    virtual void initialize(void                     );
    virtual void updateTime(vpr::Interval const &time);
    virtual void navigate  (void                     ) = 0;
    
    float getRotateFactor(void) const;
    void  setRotateFactor(float rotFactor);
    
    float getTranslateFactor(void) const;
    void  setTranslateFactor(float transFactor);    
    
  protected:
    NavigatorBase   *mNavigator;  
    NavigationModeE  mNavMode;
};


inline NavigatorBase *
NavigatorAdapterBase::getNavigator(void) const
{
    return mNavigator;
}

inline void
NavigatorAdapterBase::setNavigator(NavigatorBase *navigator)
{
    mNavigator = navigator;
}

inline  void 
	NavigatorAdapterBase::setNavigationMode(NavigationModeE tmode)
{
	mNavMode = tmode;
}


inline float
NavigatorAdapterBase::getRotateFactor(void) const
{
    return mNavigator->getRotateFactor();
}

inline void
NavigatorAdapterBase::setRotateFactor(float rotFactor)
{
    mNavigator->setRotateFactor(rotFactor);
}

inline float
NavigatorAdapterBase::getTranslateFactor(void) const
{
    return mNavigator->getTranslateFactor();
}

inline void
NavigatorAdapterBase::setTranslateFactor(float transFactor)
{
    mNavigator->setTranslateFactor(transFactor);
}

#endif // _NAVIGATOR_ADAPTER_BASE_H_
