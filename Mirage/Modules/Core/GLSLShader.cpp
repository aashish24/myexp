
#include "Core/GLSLShader.h"

#include "System/TextFileReadWrite.h"

namespace Mirage
{
  namespace Core
  {
    GLSLShader::GLSLShader( Type type ) : 
      Object    (),
      _type     ( type ),  
      _glObject ( 0 ), 
      _ss       ( "" )
    {
    }


    GLSLShader::~GLSLShader()
    {
    }


    void GLSLShader::contextInit() 
    {
      _glObject = glCreateShader( _type ); 
      this->compile();
    }


    int GLSLShader::glObject() const 
    {
      return _glObject;
    }


    void GLSLShader::source( const std::string& source )
    {
      if( source.empty() )
      {
        // Warning?? 
      }

      _ss = source;
    }


    void GLSLShader::sourceAsFile( const std::string& fileName )
    {
      try
      {
        _ss = std::string( System::TextFileReadWrite::read( const_cast< char* >( fileName.c_str() ) ) );
        if( _ss.empty() )
        {
          // Warning??
        }
      }
      catch( std::exception& e )
      {
        std::cerr << " ERROR NUMBER: " << e.what() << std::endl;
      }
      catch( ... )
      {
        std::cerr << " ERROR NUMBER: Unknown error " << std::endl;
      }
    }

    
    void GLSLShader::compile()
    { 
      const char* ss = _ss.c_str();

      glShaderSource( _glObject, 1, &ss, NULL );      
    }
  }
}
