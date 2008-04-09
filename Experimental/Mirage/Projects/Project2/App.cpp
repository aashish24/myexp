
#include "GL/glew.h"

#include "App.h"
#include "Shader.h"
#include "ShaderFactory.h"

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"
#include "MsgCore/NodeVisitor.h"
#include "MsgDB/FileRead.h"

namespace Project2
{
  App::App() :
    _shader( 0x00 ), 
    _nodeVisitor( new Msg::MsgCore::NodeVisitor() )
  {
  }


  App::~App()
  {
  }


  void App::init()
  {
    // Read config file here. 
    // ?? 

    // Set OpenGL states. 
    glEnable( GL_DEPTH_TEST);
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat lambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat ldiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lposition[] = { 0.0f, 10.0f, 0.0f, 1.0f };

    GLfloat mambient[] = { 0.1f, 0.1f, 0.2f, 1.0f };
    GLfloat mdiffuse[] = { 0.1f, 0.1f, 0.9f, 1.0f };
    GLfloat mspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv( GL_LIGHT0, GL_AMBIENT, lambient );	
    glLightfv( GL_LIGHT0, GL_DIFFUSE, ldiffuse );
	  glLightfv( GL_LIGHT0, GL_SPECULAR, lspecular );		   
    glLightfv( GL_LIGHT0, GL_POSITION, lposition );	

    glMaterialfv( GL_FRONT, GL_AMBIENT,   mambient   );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,   mdiffuse   );
    glMaterialfv( GL_FRONT, GL_SPECULAR,  mspecular  );
    glMaterialf ( GL_FRONT, GL_SHININESS, 1000.0 );  
    
    // Initialize scene graph now. 
    _root = new Msg::MsgCore::Group();

    // Initialize glew before any calls to compile shaders. 
    glewInit();

    // Initialize shaders now. 
    _shader = ShaderFactory::instance()->create( "PhongShader" );
    _shader->apply( _root.get() );

    // Load data and build scene graph.
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Node > node = Msg::MsgDB::FileRead::readFile( "./Data/Models/bunnyUVW.obj", false );

    if( node.valid() )
    {
      _root->addChild( node.get() );
    }
  }


  
  void App::reshape( int w, int h )
  {  
    glViewport( 0, 0, (GLsizei ) w, (GLsizei ) h );

    glMatrixMode( GL_PROJECTION );    glLoadIdentity();
    gluPerspective( 40.0, ( GLfloat ) w / ( GLfloat ) h, 0.1, 10000.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
  }


  void App::display()
  {
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );   
    glLoadIdentity(); 
    gluLookAt( 0.0, 0.0, 10.0, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f );   

    // Lets draw a bunny. 
    _nodeVisitor->apply( *( _root.get() ) );
  }


  void App::update()
  {
  }
}