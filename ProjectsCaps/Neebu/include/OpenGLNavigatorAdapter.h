
#ifndef _OPENGL_NAVIGATOR_ADAPTER_H_
#define _OPENGL_NAVIGATOR_ADAPTER_H_

#include <NavigatorAdapterBase.h>

class OpenGLNavigatorAdapter : public NavigatorAdapterBase
{
  public:
    typedef OpenGLNavigatorAdapter Self;
    typedef NavigatorAdapterBase   Inherited;
    
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             OpenGLNavigatorAdapter(void);
    virtual ~OpenGLNavigatorAdapter(void);
    
    /*=======================================================================*/
    /* Forwarding                                                            */
    
    virtual void navigate(void);

    /*=======================================================================*/
    /* Access                                                                */
    
    gmtl::Matrix44f const &getMatrix(void) const;
    void                   setMatrix(gmtl::Matrix44f const &matrix);    
    
  private:
    gmtl::Matrix44f mMatrix;
};

inline gmtl::Matrix44f const &
OpenGLNavigatorAdapter::getMatrix(void) const
{
    return mMatrix;
}

inline void
OpenGLNavigatorAdapter::setMatrix(gmtl::Matrix44f const & matrix)
{
    mMatrix = matrix;
}

#endif // _OPENGL_NAVIGATOR_ADAPTER_H_
