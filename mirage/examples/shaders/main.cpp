
#ifdef _MSC_VER
  #include <windows.h>
#endif

#include "GL/glew.h"
#include "GL/glut.h" 
#include "GL/gl.h"

#include "MsgCore/GLSLAttribute.h"
#include "MsgCore/GLSLShader.h"
#include "MsgCore/Viewer.h"
#include "MsgCore/Geode.h"
#include "MsgCore/Geometry.h"
#include "MsgCore/Group.h"

#include "MsgDB/FileRead.h"

using namespace Msg::MsgDB;
using namespace Msg::MsgCore; 

// This class constructs the scene. 
class Scene
{ 
  public: 

    Scene() : 
      _root( new Group() )
    {
    }


    Group* getScene() const 
    {
      return _root.get();
    }


    void buildScene();


  protected: 
  
    SmartPtr<Group> _root;
};


void Scene::buildScene()
{
  // Read geometry files. 
  SmartPtr< Node > model1 =  
    FileRead::readFile( std::string("C:\\aashish\\src\\osve\\data\\models\\Box.obj" ) );

  if( model1.valid() )
  {
    _root->addChild( model1.get() );
  }
  else
  {
    std::cerr << " ERROR: Model not found error: " << std::endl;
    std::exit(0);
  }

  SmartPtr< Node > model2 =  
    FileRead::readFile( std::string(".//..//../..//..//data//Models//Cone.obj" ) );
  if(model2.valid())
  {
    _root->addChild( model2.get() );
  }
  else
  {
    std::cerr << " ERROR: Model not found error: " << std::endl;
    std::exit(0);
  }

  // Load shaders now. 
  SmartPtr< GLSLAttribute > glslAttrib = new GLSLAttribute();
  SmartPtr< GLSLShader > vertShader = new GLSLShader( IShader::VERTEX );
  SmartPtr< GLSLShader > fragShader = new GLSLShader( IShader::FRAGMENT );

  vertShader->setSourceAsFile( ".//..//..//..//..//data/shaders/blinn_phong.vert" );
  fragShader->setSourceAsFile( ".//..//..//..//..//data/shaders/blinn_phong.frag" );  

  glslAttrib->addShader( vertShader.get() );
  glslAttrib->addShader( fragShader.get() );

  // Add uniforms. 
  SmartPtr< Uniform3f > uniform_1 = new Uniform3f();
  uniform_1->setName( "color" ); 
  uniform_1->set( 0.0, 1.0, 0.0 );
  glslAttrib->addUniform( uniform_1.get() );

  _root->getOrCreateStateSet()->attribute( glslAttrib.get() );
}


// Global objects. 
Scene scene;
SmartPtr< Viewer > _viewer( new Viewer() );

GLfloat lightPos[] = {0.0, 100.0, 0.0, 1.0};
GLfloat lightColor[] = {0.0, 1.0, 0.0, 1.0};

void init()
{  
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );

  glClearColor( 0.0, 0.0, 0.0, 1.0 );

  // Build the scene first. 
  scene.buildScene();

  // Initialize viewer. 
  _viewer->init();  
  
  // Set the data. 
  _viewer->setSceneData( scene.getScene() );
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


void keyboard( unsigned char key, int x, int y )
{
  glutPostRedisplay();
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );

  glutInitWindowPosition( 0, 0 );
  glutInitWindowSize( 800, 800 );

  glutCreateWindow( "example: shaders author: Aashish Chaudhary" ); 

  GLenum err = glewInit();

  if( GLEW_OK == err ) 
  { 
    // Successfully initialized glue. 
  }
  else
  {
    // Failed to initialize glue. 
  }

  init(); 

  glutDisplayFunc( display ); 
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  
  glutMainLoop();
}