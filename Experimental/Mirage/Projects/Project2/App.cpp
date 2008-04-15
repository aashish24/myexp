
#include "GL/glew.h"

#include "App.h"
#include "Shader.h"
#include "ShaderFactory.h"

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"
#include "MsgCore/Geode.h"
#include "MsgCore/Geometry.h"
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
    // Delete current shader and free the memory ( as the shader is created using new operator ). 
    delete _shader;
    _shader = 0x00;
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
    
    // Load data and build scene graph.
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Node > node = Msg::MsgDB::FileRead::readFile( "./Data/Models/plane.obj", false );

    if( node.valid() )
    {
      _root->addChild( node.get() );
    }

    // Glew initialization. 
    glewInit();

    // Initialize shaders now. 
    _shader = ShaderFactory::instance()->create( "BumpMapShader" );
    
    _shader->apply( _root.get() );   
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
    glPushMatrix();
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );   
    glLoadIdentity(); 
    gluLookAt( 0.0, 0.0, 20.0, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f );   

    // Call shader draw here. 
    _shader->draw();  

    Msg::MsgCore::SmartPtr< Msg::MsgCore::Geode > ge = dynamic_cast< Msg::MsgCore::Geode* >( _root->getChild( 0 ) );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Geometry > geom = dynamic_cast< Msg::MsgCore::Geometry* >( ge->getDrawable( 0 ) );

    GLint program = _shader->program();

    //GLint locT  = glGetAttribLocation( program, "tangent" );
    ////glEnableVertexAttribArray( locT );
    //glBindAttribLocation( program, locT, "tangent" );
    //glVertexAttribPointer( locT, 3, GL_FLOAT, false, 0, geom->getTangentArray()->getDataPointer() );  

    GLint locB  = glGetAttribLocation( program, "binormal" );
    glEnableVertexAttribArray( locB );
    //glBindAttribLocation( program, locB, "binormal" );
    glVertexAttribPointer( locB, 3, GL_FLOAT, false, 0, geom->getBinormalArray()->getDataPointer() );  

   // // Locate uniform for BumpMap sampler. 
   // GLint loc = glGetUniformLocation( program, "test" ); 
   // glUniform1f ( loc, 0.3 );  

    _root->accept( *( _nodeVisitor ) );    

   // glDisableVertexAttribArray( locB );
   // glDisableVertexAttribArray( locT );

    glPopMatrix();
  }


  void App::update()
  {
  }
}