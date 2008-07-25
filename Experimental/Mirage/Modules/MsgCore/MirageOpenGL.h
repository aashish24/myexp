
#ifndef __MSG_CORE_CONFIG__
#define __MSG_CORE_CONFIG__

#ifdef WIN32
  #include <windows.h>
#endif 

#include "GL/glew.h" 
#include "GL/gl.h"

namespace Msg
{
  namespace MsgCore
  {
    enum OpenGLDrawMethod
    {
      INDIVIDUAL   = 0,   
      VERTEX_ARRAYS, 
      VBO    
    };

    ///////////////////////////////////////////////////////////////////////
    //
    // Define types of faces.
    //
    ///////////////////////////////////////////////////////////////////////

		enum Face
		{
			FRONT			      = GL_FRONT, 
			BACK			      = GL_BACK, 
			FRONT_AND_BACK  = GL_FRONT_AND_BACK
		};


      ///////////////////////////////////////////////////////////////////////
      //
      // Define types of ColorMode. 
      //
      ///////////////////////////////////////////////////////////////////////

			enum LightMode
			{
				AMBIENT				      = GL_AMBIENT,
				DIFFUSE				      = GL_DIFFUSE, 
				SPECULAR			      = GL_SPECULAR, 
				AMBIENT_AND_DIFFUSE	= GL_AMBIENT_AND_DIFFUSE,
        SHININESS           = GL_SHININESS
			};
  }
}


#endif //  __MSG_CORE_CONFIG__
