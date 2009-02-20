
#ifdef _WIN32 || defined( _WINDOWS ) 
  #include "windows.h"
#endif 

#include "GL/gl.h"
#include "GL/glut.h"

#include "MsgMath/Vector.h"


using namespace Msg; 

 MsgMath::Vec3f _gControlPoints[] = 
{
  MsgMath::Vec3f( 0.0, 0.0, 0.0 ), 
  MsgMath::Vec3f( 1.0, 1.0, 0.0 ), 
  MsgMath::Vec3f( 2.0,-1.0, 0.0 ), 
  MsgMath::Vec3f( 4.0, 0.0, 0.0 ) 
};

void init()
{
  // Enable gl states. 
  glEnable( GL_MAP1_VERTEX_3 );
  glMap1f( GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, _gControlPoints[0].front() ); 
}


// Application display function. 
void display()
{
  // Clear color and depth buffers. 
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glBegin( GL_LINE_STRIP );
  for( unsigned int i=0; i < 32; ++i )
  {
    glEvalCoord1f( ( float ) i / 32.0f );
  }

  glBegin( GL_POINTS );

  glEnd();

  glEnd();

  glutSwapBuffers();
}


void reshape( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 60.0, static_cast< float >( w ) / h, 0.1, 10000.0 );

  glMatrixMode( GL_MODELVIEW );
  gluLookAt( 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}


int main( int argc, char** argv ) 
{
  // Init glut. 
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE ); 
  glutInitWindowSize( 800, 800 );
  glutInitWindowPosition( 10, 10 );
  glutCreateWindow( "Drawing Bezier Curve:" );

  // Init application specific things. 
  init(); 

  // Register application display function with glut. 
  glutDisplayFunc( display );


  // Reshape handler. 
  glutReshapeFunc( reshape );
 
  // Hand control to glut. 
  glutMainLoop();
}