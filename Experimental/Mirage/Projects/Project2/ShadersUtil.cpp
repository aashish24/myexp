
#include "ShadersUtil.h"
#include "ShaderDebug.h"

#include "Shader.h"

#include "TextFile.h"

namespace Project2
{
  ShadersUtil::ShadersUtil()
  {
  }

  
  ShadersUtil::~ShadersUtil()
  {
  }


  GLint ShadersUtil::compileAndLinkShaders( const char* vs, const char* fs )
  {
    if( ( vs == 0x00 ) || ( fs == 0x00 ) )
    {
      return Shader::SHADER_NULL_PROGRAM;
    }

    // Create shaders. 
    GLint vertexShader    = glCreateShader( GL_VERTEX_SHADER ); 
  	GLint fragmentShader  = glCreateShader( GL_FRAGMENT_SHADER );	
    GLint program         = glCreateProgram();	

    //const char* vs = textFileRead( _strdup( vert.c_str() ) );
    //const char* fs = textFileRead( _strdup( frag.c_str() ) );

	  glShaderSource( vertexShader, 1, &vs, NULL );
	  glShaderSource( fragmentShader, 1, &fs, NULL );
	  
    // Compile shaders now. 
	  glCompileShader( vertexShader );
  	glCompileShader( fragmentShader );

    // Print log info. 
	  printShaderInfoLog( vertexShader );  
	  printShaderInfoLog( fragmentShader );
	
    // Attach it to the program. 
	  glAttachShader( program, vertexShader );
	  glAttachShader( program, fragmentShader );

    // Link program. 
	  glLinkProgram( program );

    // Print log info. 
	  printProgramInfoLog( program );    

    return program;
  }


  GLint ShadersUtil::compileAndLinkFiles( std::string &vsFile, std::string &fsFile )
  {
    if( vsFile.empty() || fsFile.empty() )
    {
      return Shader::SHADER_NULL_PROGRAM;
    }

    const char* vs = textFileRead( _strdup( vsFile.c_str() ) );
    const char* fs = textFileRead( _strdup( fsFile.c_str() ) );
    
    return compileAndLinkShaders( vs, fs );
  }
}