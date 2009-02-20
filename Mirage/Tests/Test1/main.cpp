
#include <iostream>

#if defined( _WIN32  ) || defined( _WIN64 )
#include <windows.h>
#endif 

#include "MirageCore/SmartPtr.h"
#include "MirageCore/Group.h"
#include "MirageCore/NodeVisitor.h"

#include "MirageDB/FileRead.h"

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

using namespace Mirage;

MirageCore::SmartPtr< MirageCore::Group >       root  = new MirageCore::Group();
MirageCore::SmartPtr< MirageCore::NodeVisitor > nv    = 
  new MirageCore::NodeVisitor(MirageCore::NodeVisitor::DRAW);

void init()
{
	//glClearDepth( 1.0 );
	glClearColor( 0.5, 0.5, 0.5, 1.0 );	
	
	glShadeModel( GL_SMOOTH );
	
	GLfloat gWhiteLight0 []	   = { 1.0, 1.0, 1.0 };
	GLfloat gWhiteLight1 []	   = { 0.1, 0.1, 0.1 };
	GLfloat glPos []	   = { 0.0, 1000.0, 500.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_AMBIENT,  gWhiteLight1 );	
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  gWhiteLight0 );
	glLightfv( GL_LIGHT0, GL_SPECULAR, gWhiteLight0 );	
	glLightfv( GL_LIGHT0, GL_POSITION, glPos );
	
	// Enable GL states. 
	glEnable( GL_SMOOTH );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_DEPTH_TEST );	

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();  
	glOrtho( -40, 40, -40, 40, -40, 40 );

	glMatrixMode( GL_MODELVIEW );
	glTranslatef( -1031583, -1950734, 0.0 );
	glLoadIdentity();		

  std::string path = getenv("MSG_ROOT_DIR");
  MirageCore::SmartPtr< MirageCore::Node > node = 
    MirageDB::FileRead::readFile( path + std::string( "/data/cube.obj" ) );
	if( !node.valid() )
	{
		std::cerr << " File not found: " << std::endl;
		std::exit(0);
	}

	root->addChild( node.get() );
}

void idle()
{
	static float angle = 0.0;
	glMatrixMode( GL_MODELVIEW );
	//glTranslatef( 0.0, 0.0, 0.0 );

	glLoadIdentity();
	float totalAngle = -75.0;
	glRotatef( totalAngle, 1.0, 0.0, 0.0 );
	glRotatef( angle, 0.0, 0.0, 1.0 );

	angle += 1.0;
	
	if( angle >= 360.0 ) { angle = 0.0; }	

	glutPostRedisplay();
}

void display()
{	
	
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );		
	//glLoadIdentity();
	//glRotatef( -45, 0.0, 1.0, 0.0 );
	//glRotatef( -45, 1.0, 0.0, 0.0 );	
	//glTranslatef( -1500.0, 0.0, 0.0 );
	root->accept( *( nv.get() ) );	
	glutSwapBuffers();
}

int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( 800, 800 );
	glutCreateWindow( "Test Draw" );
	init();
	glutDisplayFunc( display );
	glutIdleFunc( idle );
	glutMainLoop();
	return 1;
}




