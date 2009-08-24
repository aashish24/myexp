
#include "MsgCore/Uniform.h"

#ifdef _MSC_VER
  #include <windows.h>
#endif 

#include "MsgCore/GLSLProgram.h"

namespace Msg
{
  namespace MsgCore
  {
    Uniform::Uniform( const std::string& name, const int& location ) :
        Object      ( name ), 
        _location   ( location )
    {
    }


    Uniform::~Uniform()
    {
    }

    int Uniform::location() const 
    {
      return _location;
    }


    void Uniform::location( const int& location ) 
    {
      _location = location;
    }


    void Uniform::getAndSetLocation( GLSLProgram* glslProgram ) 
    {
      if( !glslProgram ) 
      {
        return;
      }

      _location = glGetUniformLocation( glslProgram->glObject(), _name.c_str() );      
    }
  }
}
