
#include "MirageCore/GLSLProgram.h"

#include "MirageCore/GLSLShader.h"

namespace Mirage
{
  namespace MirageCore
  {
    GLSLProgram::GLSLProgram() : 
      Object    (), 
      _glObject ( 0 )
    {
    }


    GLSLProgram::~GLSLProgram()
    {
    }


    void GLSLProgram::contextInit() 
    {

    }


    int GLSLProgram::glObject() const
    {
      return _glObject;
    }

    
    void  GLSLProgram::attach( GLSLShader* shader )
    {
      glAttachShader( _glObject, shader->glObject() );
    }


    void  GLSLProgram::link()
    {
      glLinkProgram( _glObject );
    }    
  }
}

