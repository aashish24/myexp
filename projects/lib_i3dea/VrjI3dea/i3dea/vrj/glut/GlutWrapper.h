
#ifndef __I3DEA_VRJ_GLUT_WRAPPER_H__
#define __I3DEA_VRJ_GLUT_WRAPPER_H__

#include "i3dea/vrj/AppBase.h"

#include "i3dea/functors/DisplayFunctor.h"
#include "i3dea/functors/ContextInitFunctor.h"
#include "i3dea/functors/ExitFunctor.h"

#if defined( __USE_GLUT_HEADER )
#include <GL/glut.h>

#define glutSwapBuffers()   0x00
#define glutPostRedisplay() 0x00

#define __glut_h__ 1
#endif // defined( __USE_GLUT_HEADER )

namespace i3dea
{
  namespace vrj
  {
    namespace glut
    {
      template< typename T >
		  void glutDisplayFunc( T func ) 
		  {
			  AppBase::instance().displayFunc( new DisplayFunctor< T >( func ) );
		  }


      template< typename T >
		  void glutContextInitFunc( T func ) 
		  {
        AppBase::instance().contextInitFunc( new ContextInitFunctor< T >( func ) );
		  }


      template< typename T >
		  void glutExitFunc( T func ) 
		  {
        AppBase::instance().exitFunc( new ExitFunctor< T >( func ) );
		  }
      

      void glutMainLoop()
      {
        AppBase::instance().run();
        AppBase::exit();
      }
    }
  }
}

#endif // __I3DEA_VRJ_GLUT_WRAPPER_H__