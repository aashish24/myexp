
#ifdef WIN32
#include <windows.h>
#endif // WIN32 

#include "GL/glew.h"
#include "GL/glut.h"

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
    _lightPosition( 0.0, 0.0, -18.0, 1.0 ), 
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

    GLfloat lambient[] =  { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat ldiffuse[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   

    GLfloat mambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat mdiffuse[] = { 0.1f, 0.1f, 0.9f, 1.0f };
    GLfloat mspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv( GL_LIGHT0, GL_AMBIENT, lambient );	
    glLightfv( GL_LIGHT0, GL_DIFFUSE, ldiffuse );
	  glLightfv( GL_LIGHT0, GL_SPECULAR, lspecular );		   
    glLightfv( GL_LIGHT0, GL_POSITION, _lightPosition.front() );	

    glMaterialfv( GL_FRONT, GL_AMBIENT,   mambient   );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,   mdiffuse   );
    glMaterialfv( GL_FRONT, GL_SPECULAR,  mspecular  );
    glMaterialf ( GL_FRONT, GL_SHININESS, 10.0 );  
    
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
    gluPerspective( 40.0f, ( GLfloat ) w / ( GLfloat ) h, 0.1f, 10000.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
  }


  void App::display()
  {
    //glPushMatrix();
    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );   
    glLoadIdentity(); 
    gluLookAt( 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f );   
       
    // Draw scene. 
    glPushMatrix();
    glTranslatef( 0.0f, 0.0f, -20.0f );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Geode > ge = dynamic_cast< Msg::MsgCore::Geode* >( _root->getChild( 0 ) );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Geometry > geom = dynamic_cast< Msg::MsgCore::Geometry* >( ge->getDrawable( 0 ) );

    GLint program = _shader->program();
    glUseProgram( program );  
    // @Todo: Find a better way set this. 
    GLint locT  = glGetAttribLocation( program, "tangent" );
    glEnableVertexAttribArray( locT );    
    glVertexAttribPointer( locT, 3, GL_FLOAT, false, 0, geom->getTangentTBNArray()->getDataPointer() );  

    GLint locB  = glGetAttribLocation( program, "binormal" );
    glEnableVertexAttribArray( locB );    
    glVertexAttribPointer( locB, 3, GL_FLOAT, false, 0, geom->getBinormalTBNArray()->getDataPointer() );  

    GLint locC  = glGetAttribLocation( program, "normal" );
    glEnableVertexAttribArray( locC );    
    glVertexAttribPointer( locC, 3, GL_FLOAT, false, 0, geom->getNormalTBNArray()->getDataPointer() );  

    // Locate uniform for BumpMap sampler. 
    GLint loc = glGetUniformLocation( program, "normalMap" ); 
    glUniform1i ( loc, 0 );  

    GLint locLightPos = glGetUniformLocation( program, "lightPos" );
    glUniform3fv( locLightPos, 1, _lightPosition.front() );

    _root->accept( *( _nodeVisitor ) );    

    // Disabling generic attribute arrays. 
    glDisableVertexAttribArray( locB );
    glDisableVertexAttribArray( locT );    
    glPopMatrix();

    // Draw light object. 
    glPushMatrix();    
    glUseProgram( 0 );
    glDisable( GL_LIGHTING );
    glDisable( GL_LIGHT0 );    
    glTranslated( _lightPosition[0], _lightPosition[1], _lightPosition[2] );
    glutSolidSphere( 0.1, 10.0, 10.0 );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );        
    glPopMatrix();
    
    glPushMatrix();         
    glLightfv( GL_LIGHT0, GL_POSITION, _lightPosition.front() );    
    glPopMatrix();
  }


  void App::update()
  {
    static float theta = 0.0f;
    static float r = 1.0f;
    static const float incr = 0.01f;
    static const float minAngle = 0.0f;
    static const float maxAngle = 360.f;
    static const float startPosX = 0.0f;
    static const float startPosY = 0.0f;

    _lightPosition[0] = r * cos( theta ) + startPosX;
    _lightPosition[1] = r * sin( theta ) + startPosY;

    theta = ( theta + incr ); 
    
    if( theta > maxAngle )
    {
      theta = minAngle;
    }
  }
}
