
#ifdef _MSC_VER 
#include <windows.h>
#endif // __MSC_VER

#include "GL/glew.h"
#include "GL/glut.h" 
#include "GL/gl.h"


#include "MirageCore/Group.h"
#include "MirageCore/Node.h"
#include "MirageCore/Viewer.h"

#include "MirageDB/FileRead.h"
#include "MirageCore/SmartPtr.h"

#include <string>
#include <sstream>

using namespace Mirage;
using namespace Mirage::MirageCore;

static SmartPtr< Group >       _root; 
static SmartPtr< NodeVisitor > _nv;
static SmartPtr< Viewer >      _viewer( new Viewer() );


std::string help()
{
  std::ostringstream strStream; 
  strStream << "Run program: \n LoadData < input_data_file > " << std::endl;
  return strStream.str();
}


void init( const int& argc, char** argv )
{  
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );   

  glClearColor( 0.0, 0.0, 0.0, 1.0 );

  // Initialize viewer. 
  _viewer->init();  

  _root = new Group();
  
  if( argv[1] != 0x00 )
  {
    SmartPtr< Node > node = MirageDB::FileRead::readFile( argv[1] );
    if( node.valid() )
    {
      _root->addChild( node.get() );
    }

    if( _viewer.valid() )
    {
      _viewer->sceneData( _root.get() );
    }
  }
  else
  {
    std::cout << help() << std::endl;
  }
}


void display()
{  
  _viewer->draw();
  glutSwapBuffers();
}


void reshape( int w, int h )
{
  glViewport( 0, 0, w, h );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  gluPerspective( 45.0, ( double )w/h, 1.0, 1000.0 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( 0.0, 0.0, 60.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA );
  glutInitWindowPosition( 0, 0 );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( "Load Data" );

  init( argc, argv );

  glutDisplayFunc( display );
 
  glutReshapeFunc( reshape );

  glutMainLoop();
}
