
#ifndef _OPENSG_NAVIGATOR_ADAPTER_H_
#define _OPENSG_NAVIGATOR_ADAPTER_H_

#include <NavigatorAdapterBase.h>

#include <OpenSG/OSGTransform.h>

class OpenSGNavigatorAdapter : public NavigatorAdapterBase
{
  public:
    typedef OpenSGNavigatorAdapter Self;
    typedef NavigatorAdapterBase   Inherited;

    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             OpenSGNavigatorAdapter(void);
    virtual ~OpenSGNavigatorAdapter(void); 
    
    /*=======================================================================*/
    /* Forwarding                                                            */
    
    virtual void navigate(void);
    
    /*=======================================================================*/
    /* Access                                                                */
    
    OSG::TransformRefPtr const &getTransform(void) const;
    void                     setTransform(OSG::TransformRefPtr const &transform);
    
  private:
    OSG::TransformRefPtr mTransform;
};

inline OSG::TransformRefPtr const &
OpenSGNavigatorAdapter::getTransform(void) const
{
    return mTransform;
}

inline void
OpenSGNavigatorAdapter::setTransform(OSG::TransformRefPtr const &transform)
{
    mTransform = transform;
}

#endif // _OPENSG_NAVIGATOR_ADAPTER_H_
