
#ifdef _MSC_VER
#include <windows.h>
#endif 

#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glut.h"

#include "App.h"

// Application object. 
Project2::App _gApp;

void display()
{
  _gApp.display();
  glutSwapBuffers();
}


void reshape( int w, int h )
{
  _gApp.reshape( w, h );
}


void idle()
{
  _gApp.update();
  glutPostRedisplay();
}

void init()
{
  _gApp.init();
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( "Project 2" ); 
 
  // Set display function. 
  glutDisplayFunc( display );

  // Reshape function.
  glutReshapeFunc( reshape );

  // Idle function. 
  glutIdleFunc( idle );

  // Application initialization function. 
  init(); 

  // Run the loop. 
  glutMainLoop();
}
