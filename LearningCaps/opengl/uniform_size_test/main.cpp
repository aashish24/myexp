
#if defined( WIN32  ) || defined( WINDOWS )
  #include <windows.h>
#endif 

#if defined( WIN32 ) || defined( WINDOWS )
  #include "GL/glew.h"
#else
  #define glewInit void
#endif 

#include "GL/gl.h"
#include "GL/glut.h"

#include <fstream>
#include <iostream>

void init()
{
  int size_uniforms[2];
  int size_varying;

  // Write query function here. 
  glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB, &size_uniforms[0] );
  glGetIntegerv( GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB,   &size_uniforms[1] );
  glGetIntegerv( GL_MAX_VARYING_FLOATS_ARB, &size_varying );

  // Open a file and write the outout. 
  std::ofstream file( "out.txt" );
  if( file.good() )
  {
    file << "Uniforms size for Vertex   shader is : " << size_uniforms[0] << std::endl;
    file << "Uniforms size for Fragment shader is : " << size_uniforms[0] << std::endl;
    file << "Varying  size for GLSL is: " << size_varying << std::endl;
    file.close();

    std::exit( 0 );
  }
  else
  {
    std::cerr << "ERROR: Unable to open or create file: " << std::endl;
    std::exit(0);
  }
}

int main( int argc, char** argv )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  glutCreateWindow("uniforms_size_test");

  glewInit();

  init();
  
  return 1;
}
