
#include "ShadersUtil.h"
#include "ShaderDebug.h"

#include "TextFile.h"

namespace Project2
{
  ShadersUtil::ShadersUtil()
  {
  }

  
  ShadersUtil::~ShadersUtil()
  {
  }


  GLint ShadersUtil::setAndLoadShaders( const std::string &vert, const std::string &frag )
  {
    if( vert.empty() && frag.empty() )
    {
      return -1;
    }

    // Create shaders. 
    GLint vertexShader    = glCreateShader( GL_VERTEX_SHADER ); 
  	GLint fragmentShader  = glCreateShader( GL_FRAGMENT_SHADER );	
    GLint program         = glCreateProgram();	

    const char* vs = textFileRead( _strdup( vert.c_str() ) );
    const char* fs = textFileRead( _strdup( frag.c_str() ) );

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

    // Use this program. 
	  glUseProgram( program );	

    return program;
  }
}