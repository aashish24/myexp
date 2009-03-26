
#include "Core/Uniform.h"

#ifdef _MSC_VER
  #include <windows.h>
#endif 

#include "Core/GLSLProgram.h"

namespace Mirage
{
  namespace Core
  {
    Uniform::Uniform( const std::string& name, const int& location ) :
        Object      (), 
        _name       ( name ), 
        _location   ( location )
    {
    }


    Uniform::~Uniform()
    {
    }


    std::string Uniform::name() const 
    {
      return _name;
    }


    void Uniform::name( const std::string& name ) 
    {
      _name = name;
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
