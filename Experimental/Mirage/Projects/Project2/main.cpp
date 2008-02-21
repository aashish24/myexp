
#ifdef _MSC_VER
#include <windows.h>
#endif 

#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glut.h"

void display()
{
  glutSwapBuffers();
}


void init()
{
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( "Project 2" ); 

  // Application initialization function. 
  init(); 

  glutDisplayFunc( display );
  glutMainLoop();
}
