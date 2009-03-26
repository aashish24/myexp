
#ifndef __MSG_CORE_CONFIG__
#define __MSG_CORE_CONFIG__

#if defined( _WIN32 ) || ( _WIN64 )
  #include <windows.h>
#endif 

// glew.h needs to be included before gl.h gets included.
#include "GL/glew.h" 

#include "GL/gl.h"

namespace Mirage
{
  namespace Core
  {
    enum OpenGLDrawMethod
    {
      INDIVIDUAL   = 0,   
      VERTEX_ARRAYS, 

      // If we are forcing to use vertex arrays only ( file reader or geomtry handles may have to 
      // do some extra work if used this option. This is specially true for OBJ reader with unmatched 
      // vertex, normal and texture indices for a given vertex point. 
      FORCED_VERTEX_ARRAYS,
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
