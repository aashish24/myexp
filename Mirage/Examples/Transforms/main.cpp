
#ifdef _MSC_VER 
#include <windows.h>
#endif // __MSC_VER

#include "GL/glew.h"
#include "GL/glut.h" 
#include "GL/gl.h"


#include "Core/Group.h"
#include "Core/Node.h"
#include "Core/Viewer.h"
#include "Core/MatrixTransform.h"
#include "Core/SmartPtr.h"
#include "Core/Texture.h"

#include "System/FileRead.h"

#include "Math/AxisAngle.h"
#include "Math/Vec.h"
#include "Math/Utils.h"

#include <string>
#include <sstream>

using namespace Mirage;
using namespace Mirage::Core;

static SmartPtr< Group >            _root; 
static SmartPtr< NodeVisitor >      _nv;
static SmartPtr< MatrixTransform >  _transform;
static SmartPtr< Viewer >           _viewer;


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

  _viewer     = new Viewer();
  _root       = new Group();
  _transform  = new MatrixTransform();  

  // Initialize viewer. 
  _viewer->init();  

  // Apply some transformations here. 
  Math::Matrix44f mat = Math::Utils::makeRot< Math::Matrix44f >
    ( Math::AxisAnglef( Math::Vec3f( 0.0, 1.0, 0.0 ), 45.0 ) );
  _transform->setMatrix( mat );

  _root->addChild( _transform.get() );
  
  if( argv[1] != 0x00 )
  {
    SmartPtr< Node > node = System::FileRead::readFile( argv[1] );
    SmartPtr< Image > image = System::FileRead::readImageFile( argv[2] );
    if( node.valid() )
    {
      // Add one to the transform and one directly to the root node. 
      _transform->addChild( node.get() );      
      
      if( image.valid() )
      {
        SmartPtr< Texture > texture( new Texture() );
        texture->setImage( image.get() );
        _transform->getOrCreateStateSet()->textureAttribute( 0, texture.get() );
      }
    }
    else
    {
      std::cerr << "Invalid node. Exiting." << std::endl;
      std::exit(0);
    }   

    if( _viewer.valid() )
    {
      _viewer->sceneData( _root.get() );
    }
    else
    {
      std::cerr << "Invalid viewer. Exiting." << std::endl;
      std::exit(0);
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


void idle()
{
  static float angle = 0.0; 

  Math::Matrix44f mat = Math::Utils::makeRot< Math::Matrix44f >
    ( Math::AxisAnglef( Math::Vec3f( 1.0, 0.0, 0.5 ), angle ) );
  _transform->setMatrix( mat );  

  angle += 1.0;

  glutPostRedisplay();
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
  glutIdleFunc   ( idle );

  glutMainLoop();
}
