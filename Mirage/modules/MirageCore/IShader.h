
#ifndef __MSG_CORE_I_SHADER_H__
#define __MSG_CORE_I_SHADER_H__

#include "GL/glew.h"
#include "GL/gl.h"

#include <string>

namespace Mirage
{
  namespace MirageCore
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

