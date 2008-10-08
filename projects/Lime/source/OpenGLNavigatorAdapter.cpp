
#include <OpenGLNavigatorAdapter.h>

/*=======================================================================*/
/* Construction/Destruction                                              */

OpenGLNavigatorAdapter::OpenGLNavigatorAdapter(void)
    : Inherited()
{
}

OpenGLNavigatorAdapter::~OpenGLNavigatorAdapter(void)
{
}

/*=======================================================================*/
/* Forwarding                                                            */

void
OpenGLNavigatorAdapter::navigate(void)
{
    gmtl::Matrix44f newMatrix;

    // read current Modelview matrix into mMatrix
    
    mNavigator->navigate(mMatrix, newMatrix);
    
    // push newMatrix * mMatrix onto matrix stack
    
}
