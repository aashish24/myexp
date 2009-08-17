
#include <iostream>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>


#include <oge/SmartPtr.h>

#include <oge/core/Node.h>
#include <oge/core/Group.h>
#include <oge/core/Geode.h>
#include <oge/core/Geometry.h>
#include <oge/core/PrimitiveSet.h>
#include <oge/core/NodeVisitor.h>

#include <oge/db/OgeDB.h>

using namespace oge;

SmartPtr< core::Group > root = new core::Group();
SmartPtr< core::NodeVisitor > nv = new core::NodeVisitor();

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

	SmartPtr< core::Node > node = db::OgeDB::readFile("..//data/maze.obj", true );
	if( !node.valid() )
	{
		std::cerr << " File not found: " << std::endl;
		std::exit(0);
	}

	SmartPtr< Material > mat = new Material();
	mat->setAmbient( Vec4f( 1.0, 0.0, 0.0, 1.0 ) );
	mat->setDiffuse( Vec4f( 1.0, 0.0, 0.0, 1.0 ) );
	mat->setSpecular( Vec4f( 0.1, 0.1, 0.1, 1.0 ) );

	node->getStateSet()->setMaterial( mat.get() );
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




