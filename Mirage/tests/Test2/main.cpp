
#ifndef WIN32
# define GL_GLEXT_PROTOTYPES
# define GL_GLEXT_LEGACY
#endif

#define _USE_MATH_DEFINES
#define NOMINMAX

#include <limits>
#include <cctype>

#ifdef WIN32
# define NOMINMAX
# include <windows.h>
#endif

#include <iostream>
#include <map>
#include <fstream>

#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

#include "TextFile.h"
#include "ShaderDebug.h"

#include "MsgCore/SmartPtr.h"
#include "MsgCore/Group.h"
#include "MsgCore/Node.h"
#include "MsgCore/Geode.h"
#include "MsgCore/Geometry.h"
#include "MsgCore/NodeVisitor.h"

#include "MsgDB/FileRead.h"

#include "sh/sh.hpp"
#include "shutil/shutil.hpp"
#include "sh/ShImage3D.hpp"

//#include "distancemap/distance.hpp"

//using namespace SH;


///////////////////////////////////////////////////////////////////////////////
//
// Global variables. 
//
///////////////////////////////////////////////////////////////////////////////

typedef Msg::MsgCore::SmartPtr< Msg::MsgCore::Node >    NodePtr;
typedef Msg::MsgCore::SmartPtr< Msg::MsgCore::NodeVisitor >  NodeVisitorPtr;

NodePtr                                         gNode;
NodeVisitorPtr                                  gNodeVisitor( new Msg::MsgCore::NodeVisitor() );

GLint                                           gVertexShader;
GLint                                           gFragmentShader;
GLint                                           gProgram;

GLfloat         gEyePosition[]      = { 0.0, 0.0, 50.0 };
  
GLfloat         gMatAmbient []      = { 0.2, 0.2, 0.2, 1.0 };
GLfloat         gMatDiffuse []      = { 1.0, 1.0, 1.0, 1.0 };
GLfloat         gMatSpecular[]      = { 1.0, 1.0, 1.0, 1.0 };
GLfloat         gMatShininess       = 100.0;

GLfloat         gLightAmbient  []   = { 0.2, 0.2, 0.2, 1.0 };
GLfloat         gLightDiffuse  []   = { 0.9, 0.9, 0.9, 1.0 };
GLfloat         gLightSpecular []   = { 0.8, 0.8, 0.8, 1.0 };
GLfloat         gLightPosition[]    = {  0.0, 10.0, 100.0, 1.0 };

///////////////////////////////////////////////////////////////////////////////
//
// Compute TBN matrix. 
//
///////////////////////////////////////////////////////////////////////////////

void findTBN( Vec3Array* vertices, Vec3Array* texCoords, Vec3Array* normal,  Vec3Array* binormal, Vec3Array* tangent )
{
    /* Calculate the vectors from the current vertex
       to the two other vertices in the triangle */

  if( !vertices && !texCoords && !normal ) return;
  
  for( size_t i=0; i < (*vertices).size() - 2 ; ++ i )
  {
    Vec3f v2v1 = vertices->at( i )    - vertices->at( i+2 );
    Vec3f v3v1 = vertices->at( i+1 )  - vertices->at( i+2 );

    float c2c1_T = texCoords->at( i )[0] - texCoords->at( i+2 )[0];
    float c2c1_B = texCoords->at( i )[1] - texCoords->at( i+2 )[1];

    // Calculate c3c1_T and c3c1_B
    float c3c1_T = texCoords->at( i+1 )[0] - texCoords->at( i+2 )[0];
    float c3c1_B = texCoords->at( i+1 )[1] - texCoords->at( i+2 )[1];

    //Look at the references for more explanation for this one.
    float fDenominator = c2c1_T * c3c1_B - c3c1_T * c2c1_B;  
    /*ROUNDOFF here is a macro that sets a value to 0.0f if the value is a very small
      value, such as > -0.001f and < 0.001. */
    if ( fDenominator > -0.001 || fDenominator < 0.001 ) 
    {
           /* We won't risk a divide by zero, so set the tangent matrix to the
              identity matrix */
            tangent->push_back( Vec3f( 1.0f, 0.0f, 0.0f ) );
            binormal->push_back( Vec3f( 0.0f, 1.0f, 0.0f ) );
            normal->push_back( Vec3f( 0.0f, 0.0f, 1.0f ) );
    }
    else
    {            
      // Calculate the reciprocal value once and for all (to achieve speed)
      float fScale1 = 1.0f / fDenominator;

      /* Time to calculate the tangent, binormal, and normal.
         Look at Søren’s article for more information. */
      Vec3f T, B, N;
      T =           Vec3f((c3c1_B * v2v1[0] - c2c1_B * v3v1[0]) * fScale1,
                   (c3c1_B * v2v1[1] - c2c1_B * v3v1[1]) * fScale1,
                   (c3c1_B * v2v1[2] - c2c1_B * v3v1[2]) * fScale1);

      B =           Vec3f((-c3c1_T * v2v1[0] + c2c1_T * v3v1[0]) * fScale1,
                   (-c3c1_T * v2v1[1] + c2c1_T * v3v1[1]) * fScale1,
                   (-c3c1_T * v2v1[2] + c2c1_T * v3v1[2]) * fScale1);

      tangent->push_back( T );
      binormal->push_back( B );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// Load bump map. 
//
///////////////////////////////////////////////////////////////////////////////

void loadBumpMap()
{
  #if 0
	glEnable( GL_TEXTURE_2D );
    
  glGenTextures( 1, &gSampleObjects[ 1 ] );
	
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[ 1 ] );

	IMAGE image;
	image.Load( "../data/Normal.bmp" );  
	image.ExpandPalette();
		
	glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height,
							  0, image.format, GL_UNSIGNED_BYTE, image.data );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );    
	
  glDisable( GL_TEXTURE_2D );
  #endif  

  ShImage normalmap;
  ShUtil::load_PNG( normalmap, "./Data/Textures/NormalMap.png" );
  GLuint ntex;
  glGenTextures( 1,  &ntex );
  glBindTexture(GL_TEXTURE_2D, ntex );
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                    normalmap.width(), normalmap.height(),
                    GL_RGB,
                    GL_FLOAT, normalmap.data());

}


//////////////////////////////////////////////////////////////////////////////
//
// Upload shader in the GL pipeline. 
//
///////////////////////////////////////////////////////////////////////////////

void setShader( char* vs, char* fs )
{
  if( vs == NULL || fs == NULL ) 
  {
    return;
  }

	const char * vv = vs;
	const char * ff = fs;  

  gVertexShader   = glCreateShader( GL_VERTEX_SHADER );
	gFragmentShader = glCreateShader( GL_FRAGMENT_SHADER );	
  gProgram        = glCreateProgram();	
	
	glShaderSource( gVertexShader, 1, &vv, NULL );
	glShaderSource( gFragmentShader, 1, &ff, NULL );

	free( vs ); 
	free( fs );

	glCompileShader( gVertexShader );
	glCompileShader( gFragmentShader );

	printShaderInfoLog( gVertexShader );  
	printShaderInfoLog( gFragmentShader );
	
	glAttachShader( gProgram, gVertexShader );
	glAttachShader( gProgram, gFragmentShader );

	glLinkProgram( gProgram );

	printProgramInfoLog( gProgram );

	glUseProgram( gProgram );	
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load bump map shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setBumpMapShader()
{
  char* vs, *fs ;

  vs  = textFileRead( "./Data/Shaders/BumpMapShader.vert" );
  fs  = textFileRead( "./Data/Shaders/BumpMapShader.frag" );

  setShader( vs, fs );  

  glActiveTexture( GL_TEXTURE0 );    
  //glBindTexture( GL_TEXTURE_2D, gSampleObjects[1] );

  //GLint locS = glGetUniformLocation( gProgram, gSampleNames[1].c_str() ); 

  //glUniform1i ( locS, 0 );    
}


///////////////////////////////////////////////////////////////////////////////
//
// Draw obj file. 
//
///////////////////////////////////////////////////////////////////////////////


void drawObj()
{
  glPushMatrix();
  //glLoadIdentity();

  Msg::MsgCore::SmartPtr< Msg::MsgCore::Geode > geode = dynamic_cast< Msg::MsgCore::Geode* > ( gNode.get() );
  if( geode.valid() )
  { 
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Geometry > geom = dynamic_cast< Msg::MsgCore::Geometry* > ( geode->getDrawable( 0 ) );    
    if( geom.valid() )
    {
      SmartPtr< Vec3Array > vertices   = geom->getVertexArray();
      SmartPtr< Vec3Array > normals    = geom->getNormalArray();
      SmartPtr< Vec3Array > texcoords  = geom->getTexCoordArray();
      SmartPtr< Vec3iArray > indices   = geom->getVertexIndices();

      SmartPtr< Vec3Array > t( new Vec3Array() );
      SmartPtr< Vec3Array > b( new Vec3Array() );
      SmartPtr< Vec3Array > n( new Vec3Array() );
      
      findTBN( vertices.get(), texcoords.get(), n.get(), b.get(), t.get() );
    
     /* GLint locT  = glGetAttribLocation( gProgram, "tangent" );
      glBindAttribLocation( gProgram, locT, "tangent" );  
      glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, t->getDataPointer() );  */
      GLint locB  = glGetAttribLocationARB( gProgram, "binormal" );
      glEnableVertexAttribArrayARB( locB );

      //glBindAttribLocation( gProgram, locB, "binormal" );  
      glVertexAttribPointerARB( locB, 3, GL_FLOAT, false, 0, b->getDataPointer() );  
      glDisableVertexAttribArrayARB( locB );
    }
  }    

  gNode->accept( *( gNodeVisitor.get() ) );	
  glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////
//
// Set current material. 
// 
///////////////////////////////////////////////////////////////////////////////

void setCurrentMaterial()
{
  glLightfv( GL_LIGHT0, GL_AMBIENT,  gLightAmbient );	
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  gLightDiffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, gLightSpecular );		   

  glMaterialfv( GL_FRONT, GL_AMBIENT,   gMatAmbient   ) ;
  glMaterialfv( GL_FRONT, GL_DIFFUSE,   gMatDiffuse   ) ;
  glMaterialfv( GL_FRONT, GL_SPECULAR,  gMatSpecular  );
  glMaterialf ( GL_FRONT, GL_SHININESS, gMatShininess );  
}

///////////////////////////////////////////////////////////////////////////////
//
// Set current object need to be drawn. 
// 
///////////////////////////////////////////////////////////////////////////////

void setCurrentObject()
{
  // Set the material first. 
  setCurrentMaterial();  
  glUseProgram( gProgram );
  drawObj();
}


///////////////////////////////////////////////////////////////////////////////
//
// Initialization functions. 
//
///////////////////////////////////////////////////////////////////////////////

void init()
{
  glShadeModel( GL_SMOOTH );	
	
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_DEPTH_TEST );	

  glClearDepth( 1.0 );
	glClearColor( 0.4, 0.4, 0.4, 1.0 );			
  
	glLightfv( GL_LIGHT0, GL_AMBIENT,  gLightAmbient );	
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  gLightDiffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, gLightSpecular );		    

	// Lets read this from a text file. 
  gNode = Msg::MsgDB::FileRead::readFile( "./Data/Models/plane.obj" );

  // Initialize glew and create vertex and fragment shaders. 
  glewInit();        

  setBumpMapShader();
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT display function. 
// 
///////////////////////////////////////////////////////////////////////////////

void display()
{		
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );      
  
  glMatrixMode( GL_MODELVIEW );   
  glLoadIdentity(); 
  gluLookAt( gEyePosition[0], gEyePosition[1], gEyePosition[2], 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f );   

  glPushMatrix();      
  glLoadIdentity();
  glLightfv( GL_LIGHT0, GL_POSITION, gLightPosition );
  glPopMatrix();  
  
  setCurrentObject();  

	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT reshape function. 
// 
///////////////////////////////////////////////////////////////////////////////

void reshapeFunc( int w, int h )
{ 
  glViewport( 0, 0, (GLsizei ) w, (GLsizei ) h );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 40.0, ( GLfloat ) w / ( GLfloat ) h, 0.1, 10000.0 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}


///////////////////////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  // Glut initialization. 	
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize( 800, 800 );
  glutCreateWindow( "Author: Aashish Chaudhary - Demo Software" );  
	init();  	  
  loadBumpMap();
  
	glutDisplayFunc ( display );
  glutReshapeFunc ( reshapeFunc ); 

	glutMainLoop();	
}
