
#include "MsgCore/Shader.h"

#include "MsgDB/TextFileReadWrite.h"

namespace Msg
{
  namespace MsgCore
  {
    Shader::Shader( Type type ) : 
      Object    (),
      _type     ( type ),  
      _glObject ( 0 ), 
      _ss       ( "" )
    {
    }


    Shader::~Shader()
    {
    }


    void Shader::contextInit() 
    {
      _glObject = glCreateShader( _type ); 
      this->compile();
    }


    int Shader::glObject() const 
    {
      return _glObject;
    }


    void Shader::source( const std::string& source )
    {
      if( source.empty() )
      {
        // Warning?? 
      }

      _ss = source;
    }


    void Shader::sourceAsFile( const std::string& fileName )
    {
      _ss = std::string( MsgDB::TextFileReadWrite::read( const_cast< char* >( fileName.c_str() ) ) );

      if( _ss.empty() )
      {
        // Warning??
      }
    }

    
    void Shader::compile()
    { 
      const char* ss = _ss.c_str();

      glShaderSource( _glObject, 1, &ss, NULL );      
    }
  }
}
