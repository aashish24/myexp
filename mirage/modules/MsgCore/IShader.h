
#ifndef __MSG_CORE_I_SHADER_H__
#define __MSG_CORE_I_SHADER_H__

#include "GL/glew.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include "GL/gl.h"
#endif
#include <string>

namespace Msg
{
  namespace MsgCore
  {
    // Forward declaration. 
    class Program;

    class IShader
    {
      public: 

        // Types of shaders. 
        enum Type{ VERTEX    = GL_VERTEX_SHADER, 
                   FRAGMENT  = GL_FRAGMENT_SHADER };

        // Initialize context specific data. 
        virtual void  contextInit()                                   = 0;

        // Return OpenGL object. 
        virtual int   glObject() const                                = 0;

        // Set shader source as stream of string. 
        virtual void  setSource( const std::string& source )          = 0;

        // Set shader source as file. 
        virtual void  setSourceAsFile( const std::string& fileName )  = 0;

        // Compile the shader. 
        virtual void  compile()                                       = 0;         
    };
  }
}

#endif // __MSG_CORE_I_SHADER_H__

