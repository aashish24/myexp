
#ifdef _MSC_VER 
#include <windows.h>
#endif // __MSC_VER

#include "GL/glew.h"
#include "GL/glut.h" 
#include "GL/gl.h"


#include "MsgCore/Group.h"
#include "MsgCore/Node.h"
#include "MsgCore/NodeVisitor.h"

#include "MsgDB/FileRead.h"


using namespace Msg; 

MsgCore::SmartPtr< MsgCore::Group > _root; 
MsgCore::SmartPtr< MsgCore::NodeVisitor > _nv;


void init()
{
  _nv = new MsgCore::NodeVisitor( MsgCore::NodeVisitor::DRAW );
  _root = new MsgCore::Group();
  SmartPtr< Node > node = MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\current\\osve\\trunk\\Experimental\\Mirage\\Data\\Models\\plane.obj" );
  
  if( node.valid() )
  {
    _root->addChild( node.get() );
  }
}


void display()
{
  _root->accept( *_nv.get() );

  glutSwapBuffers();
}


void reshape( int width, int height )
{
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA );
  glutInitWindowPosition( 0, 0 );
  glutInitWindowSize( 800, 800 );
  glutCreateWindow( "Test1Msg" );

  init();

  glutDisplayFunc( display );
 
  glutReshapeFunc( reshape );

  glutMainLoop();
}
