
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
    class Program;

    class IShader
    {
      public: 

        enum Type{ VERTEX_SHADER = GL_VERTEX_SHADER, FRAGMENT_SHADER = GL_FRAGMENT_SHADER };

        virtual void  contextInit() = 0;

        virtual int   glObject() const = 0;

        virtual void  source( const std::string& source ) = 0;

        virtual void  sourceAsFile( const std::string& fileName ) = 0;

        virtual void  compile() = 0;         
    };
  }
}

#endif // __MSG_CORE_I_SHADER_H__

