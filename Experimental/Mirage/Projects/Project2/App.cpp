
#ifdef WIN32
#include <windows.h>
#endif // WIN32 

#include "GL/glew.h"
#include "GL/glut.h"

#include "App.h"
#include "ShaderFactory.h"
#include "BumpMapShader.h"

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"
#include "MsgCore/Geode.h"
#include "MsgCore/Geometry.h"
#include "MsgDB/FileRead.h"

namespace Project2
{
  App::App() :
    _lightPosition( 0.0, 0.0, -10.0, 1.0 ), 
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

    GLfloat lambient[] =  { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat ldiffuse[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   

    GLfloat mambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat mdiffuse[] = { 0.3f, 0.8f, 0.8f, 1.0f };
    GLfloat mspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv( GL_LIGHT0, GL_AMBIENT, lambient );	
    glLightfv( GL_LIGHT0, GL_DIFFUSE, ldiffuse );
	  glLightfv( GL_LIGHT0, GL_SPECULAR, lspecular );		   
    glLightfv( GL_LIGHT0, GL_POSITION, _lightPosition.front() );	

    glMaterialfv( GL_FRONT, GL_AMBIENT,   mambient   );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,   mdiffuse   );
    glMaterialfv( GL_FRONT, GL_SPECULAR,  mspecular  );
    glMaterialf ( GL_FRONT, GL_SHININESS, 100.0 );  
    
    // Initialize scene graph now. 
    _root = new Msg::MsgCore::Group();

    // Glew initialization. 
    glewInit();    
    
    // Parse arguments. 
    parseArguments();
    
    _root->getOrCreateStateSet()->setAttribute( _shader.get() );
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
    
    GLint program = _shader->program();
    glUseProgram( program );      

    _root->accept( *( _nodeVisitor.get() ) );    
    
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


  void App::arguments( int& argc, char** argv ) 
  {
    for( int i = 0; i < argc; ++i ) 
    {
      _arguments.push_back( std::string(  argv[i] ) );
    }
  }


  void App::parseArguments() 
  {
    for( size_t i = 0; i < _arguments.size(); ++i )
    {
      if( _arguments[i] == "--shader_type" )
      {
        _shader = ShaderFactory::instance()->create( _arguments[i+1] );

        if( _shader.valid() )
        {
          // Shader needs to extract the information from arguments. 
          _shader->parseArguments( _arguments );     
        }
      }
      if( _arguments[i] == "--model" )
      {
        // Load data and build scene graph.
        Msg::MsgCore::SmartPtr< Msg::MsgCore::Node > node = 
          Msg::MsgDB::FileRead::readFile( _arguments[i+1], false );

        if( node.valid() )
        {
          _root->addChild( node.get() );
        }
      }
    }
  }


  void App::update()
  {
    static float theta = 0.0f;
    static float r = 3.0f;
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
