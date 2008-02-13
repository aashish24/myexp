
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
#include "GL/glui.h"

#include "oge/core/SmartPtr.h"
#include "oge/core/Group.h"
#include "oge/core/Node.h"
#include "oge/core/Geode.h"
#include "oge/core/Geometry.h"
#include "oge/core/NodeVisitor.h"

#include "oge/db/OgeDB.h"

#include "app/Light.h"
#include "app/TextFile.h"
#include "app/ShaderDebug.h"
#include "app/TORUS.h"

#include "image/IMAGE.h"

#include "gmtl/Vec.h"
#include "gmtl/VecOps.h"
#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"

#include "sh/sh.hpp"
#include "shutil/shutil.hpp"
#include "sh/ShImage3D.hpp"

#include "distancemap/distance.hpp"

using namespace SH;
using namespace oge;

///////////////////////////////////////////////////////////////////////////////
//
// Data types. 
//
///////////////////////////////////////////////////////////////////////////////

enum ShaderType
{
  PHONG_LIGHTING              = 0, 
  PHONG_PER_PIXEL,  
  BLINN_PHONG_PER_PIXEL, 
  SCHLICK_PER_PIXEL, 
  CUBE_MAP_REFLECTION,  
  SPHERE_MAP_REFLECTION,
  REFRACTION, 
  REFRACTION_WITH_DISPERSION, 
  BUMP_MAP, 
  BUMP_MAP_ENV_MAP,
  DISPLACEMENT,
  PER_PIXEL_DISPLACEMENT,
  PROJECTION_SHADOWS
};


///////////////////////////////////////////////////////////////////////////////
//
// Global variables. 
//
///////////////////////////////////////////////////////////////////////////////

typedef oge::SmartPtr< oge::core::Node >        NodePtr;
typedef oge::SmartPtr< oge::core::Group >       GroupPtr;

typedef std::map< std::string, NodePtr >        Models;

typedef oge::SmartPtr< Light >                  LightPtr;
typedef oge::SmartPtr< oge::core::NodeVisitor > NodeVisitorPtr;

LightPtr                                        gLight0( new Light() );
NodeVisitorPtr                                  gNodeVisitor( new oge::core::NodeVisitor() );

GroupPtr                                        gRoot( new oge::core::Group() );
Models                                          gModels;  

GLint                                           gVertexShader;
GLint                                           gFragmentShader;
GLint                                           gProgram;

GLuint                                          gSampleObjects[6];
GLuint                                          gEnvMapObjects[6];

const std::string                               gSampleNames[] = { "uCubeMap", 
                                                                   "uNormalMap", 
                                                                   "uSphereMap", 
                                                                    "uDisplacementMap", 
                                                                   "uDistanceMap", 
                                                                   "uBaseMap" };

std::string                                     gPerPixelBase   = "../data/stone-color.png";
std::string                                     gPerPixelNormal = "../data/stone-normal.png";
std::string                                     gPerPixelHeight = "../data/stone-height.png";

// Navigation related variables. 

float                 gWinBottomLeftCorner  ( 0.0 );
float                 gWinBottomRightCorner ( 800.0 );
float                 gWinTopLeftCorner     ( 0.0 );
float                 gWinTopRightCorner    ( 800.0 );

float                 gTrackBallDiameter     ( 800.0 );  

gmtl::Vec3f           gCurrentPosition;
gmtl::Vec3f           gLastPosition;

bool                  gUseMouseLeftButton   ( false );
bool                  gUseMouseMiddleButton ( false );
bool                  gUseMouseRightButton  ( false );

// Geometry class. 

TORUS           gTorus;

// GLUI code. 
GLUI_RadioGroup *radioObj;
GLUI_RadioGroup *radioShader;

GLUI_Spinner    *spinner1;
GLUI_Spinner    *spinner2;
GLUI_Spinner    *spinner3;
GLUI_Spinner    *spinner4;
GLUI_Spinner    *spinner5;
GLUI_Spinner    *spinner6;
GLUI_Spinner    *spinner7;
GLUI_Spinner    *spinner8;
GLUI_Spinner    *spinner9;
GLUI_Spinner    *spinner10;
GLUI_Spinner    *spinner11;
GLUI_Spinner    *spinner12;
GLUI_Spinner    *spinner13;
GLUI_Spinner    *spinner14;
GLUI_Spinner    *spinner15;
GLUI_Spinner    *spinner16;
GLUI_Spinner    *spinner17;
GLUI_Spinner    *spinner18;
GLUI_Spinner    *spinner19;
GLUI_Spinner    *spinner20;
GLUI_Spinner    *spinner21;
GLUI_Spinner    *spinner22;
GLUI_Spinner    *spinner23;
GLUI_Spinner    *spinner24;

int             gCurrentWindow;

int             gCurrentObject  ( 0 );
int             gCurrentShader  ( PHONG_LIGHTING );

std::string     gCurrentObjectId( "plane" );

GLfloat         gEyePosition[]      = { 0.0, 0.0, 10.0 };
  
GLfloat         gMatAmbient []      = { 0.2, 0.2, 0.2, 1.0 };
GLfloat         gMatDiffuse []      = { 1.0, 1.0, 1.0, 1.0 };
GLfloat         gMatSpecular[]      = { 1.0, 1.0, 1.0, 1.0 };
GLfloat         gMatShininess       = 100.0;

GLfloat         gLightAmbient  []   = { 0.2, 0.2, 0.2, 1.0 };
GLfloat         gLightDiffuse  []   = { 0.9, 0.9, 0.9, 1.0 };
GLfloat         gLightSpecular []   = { 0.8, 0.8, 0.8, 1.0 };
GLfloat         gLightPosition[]    = {  0.0, 10.0, 100.0, 1.0 };

GLfloat         gEta                = 0.66;
GLfloat         gEtaR               = 0.65;
GLfloat         gEtaG               = 0.66;
GLfloat         gEtaB               = 0.67;
GLfloat         gFresnel            = 5.0;
GLfloat         gBumpDepth          = 1.0;

GLfloat         gNavigationMatrix[16];
gmtl::Matrix44f gGmtlNavigationMatrix;

#define         MAX_ZOOM_OUT  -10.0
#define         MAX_ZOOM_IN    2.0

GLfloat         gAngle    ( 0.0 );
GLfloat         gPosition ( 0.0 );

int             dmapDepth = 64;


///////////////////////////////////////////////////////////////////////////////
//
// Read config. 
//
///////////////////////////////////////////////////////////////////////////////

void readConfig( const std::string& fileName )
{
  std::ifstream file( fileName.c_str() );
  if( file.good() )
  {
    std::string   id;
    std::string   data;

    std::cout << std::endl << "Start reading config: ";

    while( !file.eof() )
    {
      file >> id >> data >> std::ws;  
      oge::SmartPtr< oge::core::Node > node( oge::db::OgeDB::readFile( data, false ) );
      if( node.valid() )
      {
        gModels[id] = node;
        gRoot->addChild( node.get() );
      }
    }

    std::cout << std::endl << "End reading config: ";
  }
  else
  {
    std::cerr << "Error ErrorNo: Config file not found / invalid. " << std::endl;
  }
}


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
// Load cube map. 
//
///////////////////////////////////////////////////////////////////////////////

void loadCubeMap()
{
    glEnable( GL_TEXTURE_CUBE_MAP_EXT );

    glGenTextures( 1, &gSampleObjects[ 0 ] );
    
    glBindTexture( GL_TEXTURE_CUBE_MAP_EXT, gSampleObjects[ 0 ] );    
    
    static GLenum faceTarget[ 6 ] =
    {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT, 
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT, 
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT, 
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT, 
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT, 
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT
    };

    char* faceFile[6] = 
    { 
      "../data/brightday2_posx.bmp", 
      "../data/brightday2_negx.bmp", 
      "../data/brightday2_posy.bmp", 
      "../data/brightday2_negy.bmp", 
      "../data/brightday2_posz.bmp", 
      "../data/brightday2_negz.bmp"
    };
    
    for( unsigned int i=0; i < 6; ++i )
    {
      IMAGE image;
      image.Load( faceFile[ i ] );  
      image.ExpandPalette();		 

      glTexImage2D(	faceTarget[i], 0, GL_RGBA8, image.width, image.height,
						        0, image.format, GL_UNSIGNED_BYTE, image.data );      
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    glDisable( GL_TEXTURE_CUBE_MAP_EXT );
}


///////////////////////////////////////////////////////////////////////////////
//
// Load sphere map. 
//
///////////////////////////////////////////////////////////////////////////////

void loadSphereMap()
{ 
  glEnable( GL_TEXTURE_2D );

  glGenTextures( 1, &gSampleObjects[ 2 ] );

	glBindTexture( GL_TEXTURE_2D, gSampleObjects[2] );

	IMAGE image;
	image.Load( "../data/SphereMap.bmp" );  
	image.ExpandPalette();

	glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height,
							  0, image.format, GL_UNSIGNED_BYTE, image.data );
    
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	
  glDisable( GL_TEXTURE_2D );
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
  ShUtil::load_PNG( normalmap, gPerPixelNormal );
  GLuint ntex;
  glGenTextures( 1,  &gSampleObjects[ 1 ] );
  glBindTexture(GL_TEXTURE_2D, gSampleObjects[ 1 ] );
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                    normalmap.width(), normalmap.height(),
                    GL_RGB,
                    GL_FLOAT, normalmap.data());

}


///////////////////////////////////////////////////////////////////////////////
//
// Load images for displacement map. 
//
///////////////////////////////////////////////////////////////////////////////

void loadDisplacementMap()
{
  glEnable( GL_TEXTURE_2D );

  glGenTextures( 1, &gSampleObjects[ 3 ] );

  glBindTexture( GL_TEXTURE_2D, gSampleObjects[ 3 ] );

  IMAGE image;
  image.Load( "../data/nveye_displace.bmp" );
  image.ExpandPalette();

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, image.width, 
                image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );    
	
  glDisable( GL_TEXTURE_2D );
}


void loadDistanceMap()
{    
  /* Load in height map and generate distance map */
  glEnable( GL_TEXTURE_3D );
  
  ShImage heightmap;
  ShUtil::load_PNG( heightmap, gPerPixelHeight );

  ShImage3D dmapImg = init_distance_map( heightmap, dmapDepth );
  
  //distmap.memory(dmap_img.memory());
  //distmap.size(dmap_img.width(), dmap_img.height(), dmap_img.depth());

  glGenTextures( 1, &gSampleObjects[ 4 ] );

  glBindTexture( GL_TEXTURE_3D, gSampleObjects[ 4 ] );

  //IMAGE image;
  //image.Load( "../data/nveye_displace.bmp" );
  //image.ExpandPalette();

  glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT );    

  glTexImage3D( GL_TEXTURE_3D, 0, GL_LUMINANCE16, dmapImg.width(), dmapImg.height(), dmapImg.depth(), 0, GL_LUMINANCE, GL_FLOAT, dmapImg.data() );
  glDisable( GL_TEXTURE_3D );
}


void loadDistanceBaseMap()
{
  glEnable( GL_TEXTURE_2D );
  ShImage baseImage;
  ShUtil::load_PNG( baseImage, gPerPixelBase );

  glGenTextures( 1, &gSampleObjects[ 5 ] );
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[ 5 ] );

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, baseImage.width(), baseImage.height(), 0, GL_RGB, GL_FLOAT, baseImage.data() );
  gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, baseImage.width(), baseImage.height(), GL_RGB, GL_FLOAT, baseImage.data() );
  glDisable( GL_TEXTURE_2D );
}

void loadEnvMap()
{
  glEnable( GL_TEXTURE_2D );
  char* faceFile[6] = 
  { 
    "../data/posz.bmp", 
    "../data/posx.bmp", 
    "../data/negz.bmp",
    "../data/negx.bmp", 
    "../data/posy.bmp", 
    "../data/negy.bmp"
  };
  
  
  for( unsigned int i=0; i < 6; ++i )
  {
    IMAGE image;
    image.Load( faceFile[ i ] );  
    image.ExpandPalette();		 
    
    glGenTextures( 1, &gEnvMapObjects[i] );
    glBindTexture( GL_TEXTURE_2D, gEnvMapObjects[ i ] );
    glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height,
					        0, image.format, GL_UNSIGNED_BYTE, image.data );
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );    
  }

  glDisable( GL_TEXTURE_2D );
}

///////////////////////////////////////////////////////////////////////////////
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
// Read and load phong per vertex shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setPhongLightingShader()
{
  char *vs,*fs;	
	
	vs = textFileRead( "../shaders/PhongLighting.vert" );
	fs = textFileRead( "../shaders/PhongLighting.frag" );

  setShader( vs, fs );	
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load phong per pixel shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setPhongShadingShader()
{
  char *vs,*fs;	
	
	vs = textFileRead( "../shaders/PhongShading.vert" );
	fs = textFileRead( "../shaders/PhongShading.frag" );

  setShader( vs, fs );	
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load blinn-phong per pixel shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setBlinnPhongShadingShader()
{
  char *vs,*fs;	
	
	vs = textFileRead( "../shaders/BlinnPhongShading.vert" );
	fs = textFileRead( "../shaders/BlinnPhongShading.frag" );

  setShader( vs, fs );	
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load Schlick per pixel shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setSchlickShadingShader()
{
  char *vs,*fs;	
	
	vs = textFileRead( "../shaders/SchlickShading.vert" );
	fs = textFileRead( "../shaders/SchlickShading.frag" );

  setShader( vs, fs );	
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load Schlick per pixel shader. 
//
///////////////////////////////////////////////////////////////////////////////

void loadCubeMapReflectionShader()
{
  char *vs, *fs;  

  vs = textFileRead( "../shaders/CubeMapsReflection.vert" );
  fs = textFileRead( "../shaders/CubeMapsReflection.frag" );

  setShader( vs, fs );

  GLint locD1 = glGetUniformLocation( gProgram, "uLightPos" );	
	GLint locD2 = glGetUniformLocation( gProgram, "uMixRatio" );
	
	
  glUniform3fv( locD1, 1, gLightPosition );
	glUniform1f ( locD2, 0.2 );

  glActiveTexture( GL_TEXTURE0 );
  glBindTexture( GL_TEXTURE_CUBE_MAP_EXT, gSampleObjects[0] );

  GLint locS = glGetUniformLocation( gProgram, gSampleNames[0].c_str() ); 
  
  glUniform1i ( locS, 0 );      
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load sphere map reflection shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setSphereMapReflectionShader()
{
  char *vs, *fs;  

  vs = textFileRead( "../shaders/SphereMapReflection.vert" );
  fs = textFileRead( "../shaders/SphereMapReflection.frag" );

  setShader( vs, fs );  

  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[2] );

  GLint locS = glGetUniformLocation( gProgram, gSampleNames[2].c_str() ); 
  
  glUniform1i ( locS, 0 );    
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load refraction shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setRefractionShader()
{
  char  *vs, *fs;  

  vs = textFileRead( "../shaders/CubeMapsRefraction.vert" );
  fs = textFileRead( "../shaders/CubeMapsRefraction.frag" );

  setShader( vs, fs );

  GLint locD1 = glGetUniformLocation( gProgram, "uEta" );	
  GLint locD2 = glGetUniformLocation( gProgram, "uFresnelPower" );	
  GLint locD3 = glGetUniformLocation( gProgram, "uEyePos" );	

  
  glUniform1f( locD1, gEta );    
  glUniform1f( locD2, gFresnel );    
  glUniform3fv( locD3, 1, gEyePosition );

  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[0] );

  GLint locS = glGetUniformLocation( gProgram, gSampleNames[0].c_str() ); 

  glUniform1i ( locS, 0 );    
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load refraction with dispersion shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setRefractionWithDispersionShader()
{
  char *vs, *fs;  
  
  vs = textFileRead( "../shaders/CubeMapRefractionWithDispersion.vert" );
  fs = textFileRead( "../shaders/CubeMapRefractionWithDispersion.frag" );

  setShader( vs, fs );
  
  GLint locD1 = glGetUniformLocation( gProgram, "uEtaR" );
  GLint locD2 = glGetUniformLocation( gProgram, "uEtaG" );
  GLint locD3 = glGetUniformLocation( gProgram, "uEtaB" );
  GLint locD4 = glGetUniformLocation( gProgram, "uFresnelPower" );	  	
  
	glUniform1f( locD1, gEtaR );
	glUniform1f( locD2, gEtaG );  
  glUniform1f( locD3, gEtaB );  
  glUniform1f( locD4, gFresnel );  

  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[0] );

  GLint locS = glGetUniformLocation( gProgram, gSampleNames[0].c_str() ); 

  glUniform1i ( locS, 0 );    
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load bump map shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setBumpMapShader()
{
  char* vs, *fs ;

  vs  = textFileRead( "../shaders/BumpMap.vert" );
  fs  = textFileRead( "../shaders/BumpMap.frag" );

  setShader( vs, fs );

  GLint locD1    = glGetUniformLocation( gProgram, "uLightPos" );	  
  
  glUniform3fv( locD1, 1, gLightPosition );

  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[1] );

  GLint locS = glGetUniformLocation( gProgram, gSampleNames[1].c_str() ); 

  glUniform1i ( locS, 0 );    
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load bump map with reflection shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setBumpMapEnvMapShader()
{
  char* vs, *fs;  

  vs = textFileRead( "../shaders/BumpMapEnvMap.vert" );
  fs = textFileRead( "../shaders/BumpMapEnvMap.frag" );
  
  setShader( vs, fs );
  
  GLint locD1   = glGetUniformLocation( gProgram, "uLightPos " );	 

  glUniform3fv( locD1, 1, gLightPosition );  
  
  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_CUBE_MAP, gSampleObjects[0] );

  GLint locS1 = glGetUniformLocation( gProgram, gSampleNames[0].c_str() ); 

  glUniform1i ( locS1, 0 );     

  glActiveTexture( GL_TEXTURE1 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[1] );

  GLint locS2 = glGetUniformLocation( gProgram, gSampleNames[1].c_str() ); 

  glUniform1i ( locS2, 1 );     

  // Back to texture unit 0. 
  glActiveTexture( GL_TEXTURE0 ); 
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load projecth shadows shader. 
//
///////////////////////////////////////////////////////////////////////////////

void setProjectionShadowsShader()
{
  char *vs, *fs;
  GLfloat n[] = { 0.0, 1.0, 0.0 };

  vs = textFileRead( "../shaders/ProjectionShadows.vert" );
  fs = textFileRead( "../shaders/ProjectionShadows.frag" );

  setShader( vs, fs );  

  GLint loc1  = glGetUniformLocation( gProgram, "uLightPos" );
  GLint loc2  = glGetUniformLocation( gProgram, "n" );
  GLint loc3  = glGetUniformLocation( gProgram, "d" );

  glUniform4fv( loc1, 1, gLightPosition );
  glUniform3fv( loc2, 1, n );
  glUniform1f ( loc3, 5.0 );   
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load displacement shader.
//
///////////////////////////////////////////////////////////////////////////////

void setDisplacementShader()
{
  char *vs, *fs;
  
  vs = textFileRead( "../shaders/Displacement.vert" );
  fs = textFileRead( "../shaders/Displacement.frag" );

  setShader( vs, fs );

  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[3] );

  GLint locS1 = glGetUniformLocation( gProgram, "uDisplacementMap" );
  GLint locD1 = glGetUniformLocation( gProgram, "test" );
  
  if( locS1 != -1 )
  {
    glUniform1i( locS1, 0 );
  }
  else
  {
    std::cerr << "Location not found error: " << std::endl;
    //std::exit( 0 );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// Read and load per pixel displacement shader. 
//
///////////////////////////////////////////////////////////////////////////////

void drawBox()
{
  glPushMatrix();

  glBegin( GL_TRIANGLES );    

  glNormal3f( 1.0, 0.0, 0.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 0.0, 1.0 );    
  glVertex3f( 2.5, -2.5, 0.2 );
  
  glNormal3f( 1.0, 0.0, 0.0 );
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 0.0, 0.0 );  
  glVertex3f( 2.5, -2.5,-0.0 );
  
  glNormal3f( 1.0, 0.0, 0.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 1.0, 0.0 );  
  glVertex3f( 2.5, 2.5,  -0.0 );  

  glNormal3f( 1.0, 0.0, 0.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 1.0, 0.0 );  
  glVertex3f( 2.5, 2.5,  -0.0 );  

  glNormal3f( 1.0, 0.0, 0.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 1.0, 1.0 );  
  glVertex3f( 2.5, 2.5, 0.2 );  

  glNormal3f( 1.0, 0.0, 0.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 0.0, 1.0 );    
  glVertex3f( 2.5, -2.5, 0.2 );

  glEnd();
  glPopMatrix(); 
}

void drawSquare()
{
  glPushMatrix();

  glBegin( GL_TRIANGLES );    

  glNormal3f( 0.0, 0.0, 1.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 0.0, 0.0, 1.0 );    
  glVertex3f( -2.5, -2.5, 0.0 );
  
  glNormal3f( 0.0, 0.0, 1.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 0.0, 1.0 );  
  glVertex3f( 2.5, -2.5, 0.0 );
  
  glNormal3f( 0.0, 0.0, 1.0 );  
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 1.0, 1.0 );  
  glVertex3f( 2.5, 2.5, 0.0 );  

  glNormal3f( 0.0, 0.0, 1.0 );    
  glMultiTexCoord3f( GL_TEXTURE0, 1.0, 1.0, 1.0 );  
  glVertex3f( 2.5, 2.5, 0.0 );  

  glNormal3f( 0.0, 0.0, 1.0 );    
  glMultiTexCoord3f( GL_TEXTURE0, 0.0, 1.0, 1.0 );  
  glVertex3f( -2.5, 2.5, 0.0 );  

  glNormal3f( 0.0, 0.0, 1.0 );    
  glMultiTexCoord3f( GL_TEXTURE0, 0.0, 0.0, 1.0 );    
  glVertex3f( -2.5, -2.5, 0.0 );

  glEnd();
  glPopMatrix(); 
}

void setPerPixelDisplacementShader()
{
  char* vs, *fs;    

  vs = textFileRead( "../shaders/PerPixelDisplacement.vert" );
  fs = textFileRead( "../shaders/PerPixelDisplacement.frag" );
  
  setShader( vs, fs );
  
  GLint locD1 = glGetUniformLocation( gProgram, "uLightPos" );	 
  GLint locD2 = glGetUniformLocation( gProgram, "uBumpDepth" );	 

  glUniform3fv( locD1, 1, gLightPosition );  
  glUniform1f( locD2, gBumpDepth );  
  
  glActiveTexture( GL_TEXTURE0 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[1] );

  GLint locS1 = glGetUniformLocation( gProgram, gSampleNames[1].c_str() ); 

  glUniform1i ( locS1, 0 );     
  
  glActiveTexture( GL_TEXTURE1 );    
  glBindTexture( GL_TEXTURE_3D, gSampleObjects[4] );

  GLint locS2 = glGetUniformLocation( gProgram, "uDistanceMap" );

  glUniform1i ( locS2, 1 );     

  glActiveTexture( GL_TEXTURE2 );    
  glBindTexture( GL_TEXTURE_2D, gSampleObjects[5] );

  GLint locS3 = glGetUniformLocation( gProgram, "uBaseMap" );

  glUniform1i ( locS3, 2 );     

  // Back to texture unit 0. 
  glActiveTexture( GL_TEXTURE0 ); 
}


///////////////////////////////////////////////////////////////////////////////
//
// Draw light in space. 
//
///////////////////////////////////////////////////////////////////////////////

void drawLight()
{
  glPushMatrix();
    glTranslatef( gLightPosition[0], gLightPosition[1], gLightPosition[2] );
    glutSolidSphere( 1.0, 20.0, 20.0 );
  glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
//
// Draw plane.
//
///////////////////////////////////////////////////////////////////////////////

void drawPlane()
{
  SmartPtr< Vec3Array >  vertices   ( new Vec3Array() );
  SmartPtr< Vec3iArray > indices    ( new Vec3iArray() );
  SmartPtr< Vec3Array >  normals    ( new Vec3Array() );
  SmartPtr< Vec3Array >  texCoords  ( new Vec3Array() );
  SmartPtr< Vec3Array >  tangetT    ( new Vec3Array() );
  SmartPtr< Vec3Array >  tangetB    ( new Vec3Array() );  

  vertices->push_back( Vec3f( -5.0, -5.0, 0.0 ) );
  vertices->push_back( Vec3f(  5.0, -5.0, 0.0 ) );
  vertices->push_back( Vec3f(  5.0,  5.0, 0.0 ) );
  vertices->push_back( Vec3f( -5.0,  5.0, 0.0 ) );  

  normals->push_back( Vec3f( 0.0, 0.0, 1.0 ) );
  normals->push_back( Vec3f( 0.0, 0.0, 1.0 ) );
  normals->push_back( Vec3f( 0.0, 0.0, 1.0 ) );
  normals->push_back( Vec3f( 0.0, 0.0, 1.0 ) );

  texCoords->push_back(  Vec3f( 0.0, 0.0, 0.0 ) );
  texCoords->push_back(  Vec3f( 1.0, 0.0, 0.0 ) );
  texCoords->push_back(  Vec3f( 1.0, 1.0, 0.0 ) );
  texCoords->push_back(  Vec3f( 0.0, 1.0, 0.0 ) );

  tangetT->push_back( Vec3f( 1.0, 0.0, 0.0 ) );
  tangetT->push_back( Vec3f( 1.0, 0.0, 0.0 ) );
  tangetT->push_back( Vec3f( 1.0, 0.0, 0.0 ) );
  tangetT->push_back( Vec3f( 1.0, 0.0, 0.0 ) );

  indices->push_back( Vec3i( 0, 1, 2 ) );
  indices->push_back( Vec3i( 2, 3, 0 ) );

  SmartPtr< Vec3Array > t( new Vec3Array() );
  SmartPtr< Vec3Array > b( new Vec3Array() );
  SmartPtr< Vec3Array > n( new Vec3Array() );

  findTBN( vertices.get(), texCoords.get(), n.get(), b.get(), t.get() );

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, vertices->getDataPointer() );

  glEnableClientState( GL_NORMAL_ARRAY );
  glNormalPointer( GL_FLOAT, 0, normals->getDataPointer() );

  glEnableClientState( GL_TEXTURE_COORD_ARRAY );
  glTexCoordPointer( 3, GL_FLOAT, 0, texCoords->getDataPointer() );

  GLint locT  = glGetAttribLocation( gProgram, "tangent" );
  glBindAttribLocation( gProgram, locT, "tangent" );  
  glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, t->getDataPointer() );  

  GLint locB  = glGetAttribLocation( gProgram, "binormal" );
  glBindAttribLocation( gProgram, locB, "binormal" );  
  glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, b->getDataPointer() );  

  //glVertexAttribPointer( 10, 3, GL_FLOAT, false, sizeof( TORUS_VERTEX ), &gTorus.vertices[0].tTangent );

  glDrawElements( GL_TRIANGLES, ( GLsizei )( 6 ), GL_UNSIGNED_INT, indices->getDataPointer() );

  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_NORMAL_ARRAY );
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

///////////////////////////////////////////////////////////////////////////////
//
// Draw floor. 
//
///////////////////////////////////////////////////////////////////////////////

void drawFloor()
{
  glPushMatrix(); 
  glBegin( GL_TRIANGLES );
  
  glNormal3f(   0.0, 1.0,   0.0 );
  glVertex3f( -8.0, 0.0,  8.0 );
  glNormal3f(   0.0, 1.0,   0.0 );
  glVertex3f(  8.0, 0.0,  8.0 );
  glNormal3f(   0.0, 1.0,   0.0 );
  glVertex3f(  8.0, 0.0, -8.0 );

  glNormal3f(   0.0,  1.0,   0.0 );
  glVertex3f(  8.0,  0.0, -8.0 );
  glNormal3f(   0.0,  1.0,   0.0 );
  glVertex3f( -8.0,  0.0, -8.0 );
  glNormal3f(   0.0,  1.0,   0.0 );
  glVertex3f( -8.0,  0.0,  8.0 );

  glEnd();
  glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
//
// Draw obj file. 
//
///////////////////////////////////////////////////////////////////////////////


void drawObj()
{
  glPushMatrix();
  oge::SmartPtr< oge::core::Node > node;

  if( gModels.find( gCurrentObjectId ) != gModels.end() )
  {
      node = gModels.find( gCurrentObjectId )->second;
  }
  else
  {
    return;
  }
  
  if( !node.valid() ) return;

  oge::SmartPtr< oge::core::Geode > geode = dynamic_cast< oge::core::Geode* > ( node.get() );
  if( geode.valid() )
  { 
    oge::SmartPtr< oge::core::Geometry > geom = dynamic_cast< oge::core::Geometry* > ( geode->getDrawable( 0 ) );    
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
    
      GLint locT  = glGetAttribLocation( gProgram, "tangent" );
      glBindAttribLocation( gProgram, locT, "tangent" );  
      glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, t->getDataPointer() );  
      GLint locB  = glGetAttribLocation( gProgram, "binormal" );
      glBindAttribLocation( gProgram, locB, "binormal" );  
      glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, b->getDataPointer() );  
    }
  }    

  node->accept( *( gNodeVisitor.get() ) );	
  glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
//
// Draw torus. 
//
///////////////////////////////////////////////////////////////////////////////

void drawTorus()
{
  glPushMatrix();  
  glVertexPointer( 3, GL_FLOAT, sizeof( TORUS_VERTEX ), &gTorus.vertices[0].position );
	glEnableClientState( GL_VERTEX_ARRAY );

	glNormalPointer( GL_FLOAT, sizeof( TORUS_VERTEX ), &gTorus.vertices[0].normal );
	glEnableClientState( GL_NORMAL_ARRAY );

	glTexCoordPointer( 2, GL_FLOAT, sizeof( TORUS_VERTEX ), &gTorus.vertices[0].s );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );  


  GLint loc  = glGetAttribLocation( gProgram, "tangent" );
  glBindAttribLocation( gProgram, loc, "tangent" );
  glVertexAttribPointer( 10, 3, GL_FLOAT, false, sizeof( TORUS_VERTEX ), &gTorus.vertices[0].tTangent );

  glDrawElements( GL_TRIANGLES, gTorus.numIndices, GL_UNSIGNED_INT, gTorus.indices );   
  glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
//
// Draw sky box. 
//
///////////////////////////////////////////////////////////////////////////////

void drawSkyBox()
{
  const int size = 50.0;
  glPushMatrix();
  //glLoadIdentity();
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, gEnvMapObjects[0] );
  glBegin( GL_TRIANGLES );

    // +Z face.             
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f(  0.0,  0.0, -1.0 );    
    glVertex3f( -size, -size,  size );
    glTexCoord3f( 1.0, 0.0, 0.0 );
    glNormal3f(  0.0,  0.0, -1.0 );
    glVertex3f(  size, -size,  size );
    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f(  0.0,  0.0, -1.0 );
    glVertex3f(  size,  size,  size );

    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f(  0.0,  0.0, -1.0 );
    glVertex3f(  size,  size,  size );
    glTexCoord3f( 0.0, 1.0, 0.0 );
    glNormal3f(  0.0,  0.0, -1.0 );
    glVertex3f( -size,  size,  size );
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f(  0.0,  0.0, -1.0 );
    glVertex3f( -size, -size,  size );
  glEnd();
  glDisable( GL_TEXTURE_2D );

    // +X face.     
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, gEnvMapObjects[1] );
  glBegin( GL_TRIANGLES );
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f( -1.0,  0.0,  0.0 );
    glVertex3f(  size, -size,  size );
    glTexCoord3f( 1.0, 0.0, 0.0 );
    glNormal3f( -1.0,  0.0,  0.0 );
    glVertex3f(  size, -size, -size );
    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f( -1.0,  0.0,  0.0 );
    glVertex3f(  size,  size, -size );

    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f( -1.0,  0.0,  0.0 );
    glVertex3f(  size,  size, -size );
    glTexCoord3f( 0.0, 1.0, 0.0 );
    glNormal3f( -1.0,  0.0,  0.0 );
    glVertex3f(  size,  size,  size );
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f( -1.0,  0.0,  0.0 );
    glVertex3f(  size, -size,  size );
  glEnd();    
  glDisable( GL_TEXTURE_2D );
    
    // -Z face.
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, gEnvMapObjects[2] );
  glBegin( GL_TRIANGLES );
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f(  0.0,  0.0,  1.0 );
    glVertex3f(  size, -size, -size );
    glTexCoord3f( 1.0, 0.0, 0.0 );
    glNormal3f(  0.0,  0.0,  1.0 );
    glVertex3f( -size, -size, -size );
    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f(  0.0,  0.0,  1.0 );
    glVertex3f( -size,  size, -size );

    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f(  0.0,  0.0,  1.0 );
    glVertex3f( -size, size, -size );
    glTexCoord3f( 0.0, 1.0, 0.0 );
    glNormal3f(  0.0,  0.0,  1.0 );
    glVertex3f(  size, size, -size );
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f(  0.0,  0.0,  1.0 );
    glVertex3f(  size,  -size, -size );
  glEnd();
  glDisable( GL_TEXTURE_2D );

    // -X face.
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, gEnvMapObjects[3] );
  glBegin( GL_TRIANGLES );  
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f(  1.0,  0.0,  0.0 );
    glVertex3f( -size, -size, -size );
    glTexCoord3f( 1.0, 0.0, 0.0 );
    glNormal3f(  1.0,  0.0,  0.0 );
    glVertex3f( -size, -size,  size );
    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f(  1.0,  0.0,  0.0 );
    glVertex3f( -size,  size,  size );

    glTexCoord3f( 1.0, 1.0, 0.0 );
    glNormal3f(  1.0,  0.0,  0.0 );
    glVertex3f( -size,  size,  size );
    glTexCoord3f( 0.0, 1.0, 0.0 );
    glNormal3f(  1.0,  0.0,  0.0 );
    glVertex3f( -size,  size, -size );
    glTexCoord3f( 0.0, 0.0, 0.0 );
    glNormal3f(  1.0,  0.0,  0.0 );
    glVertex3f( -size, -size, -size );
  glEnd();  
  glDisable( GL_TEXTURE_2D );

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

  if( gCurrentObject >= 0 && gCurrentObject <= 3 && gCurrentShader != PER_PIXEL_DISPLACEMENT )
  {
    glUseProgram( 0 );
    drawSkyBox();

    glUseProgram( gProgram );
    drawObj();
  }

  if( gCurrentShader == PER_PIXEL_DISPLACEMENT )
  {
    drawSquare();
    drawBox();
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// Set current shader. 
// 
///////////////////////////////////////////////////////////////////////////////

void setCurrentShader()
{  
  switch( gCurrentShader )
  { 
    case 0: { setPhongLightingShader(); break; }
    case 1: { setPhongShadingShader(); break;   }
    case 2: { setBlinnPhongShadingShader(); break; }
    case 3: { setSchlickShadingShader(); break; }
    case 4: { loadCubeMapReflectionShader(); break; }
    case 5: { setSphereMapReflectionShader(); break; }
    case 6: { setRefractionShader(); break; }
    case 7: { setRefractionWithDispersionShader(); break; }    
    case 8: { setBumpMapShader(); break; }
    case 9: { setBumpMapEnvMapShader(); break; }
    case 10:{ setDisplacementShader(); break; }
    case 11:{ setPerPixelDisplacementShader(); break; }
    case 12:{ setProjectionShadowsShader(); break; }
  };
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

  glClearStencil( 0x0 );
  glEnable( GL_STENCIL_TEST );

  glEnable( GL_BLEND );
  glEnable( GL_ALPHA );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

	glClearDepth( 1.0 );
	glClearColor( 0.4, 0.4, 0.4, 1.0 );			
  
	glLightfv( GL_LIGHT0, GL_AMBIENT,  gLightAmbient );	
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  gLightDiffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, gLightSpecular );		    

	// Lets read this from a text file. 
  readConfig( "../data/oge.config" );

  // Initialize glew and create vertex and fragment shaders. 
  glewInit();        

  setCurrentShader();
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT display function. 
// 
///////////////////////////////////////////////////////////////////////////////

void display()
{		
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );      

  setCurrentMaterial();  
  
  glMatrixMode( GL_MODELVIEW );   
  glLoadIdentity(); 
  gluLookAt( gEyePosition[0], gEyePosition[1], gEyePosition[2], 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f );   

  
  glPushMatrix(); 

    //glTranslatef( 0.0, 0.0, gPosition );        
    //glMultMatrixf( gGmtlNavigationMatrix.mData );      
    //glTranslatef( 0.0, 0.0, -gPosition );
    //glTranslatef( 0.0, 0.0, gPosition );
  
    glPushMatrix();      

      glLoadIdentity();
      glLightfv( GL_LIGHT0, GL_POSITION, gLightPosition );

    glPopMatrix();

    if( gCurrentShader != PROJECTION_SHADOWS )
    {      
      glEnable( GL_DEPTH_TEST );            
      glDisable( GL_STENCIL_TEST );
      //drawLight();
      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);          
      setCurrentObject();
    }
    else 
    {     
      glEnable( GL_DEPTH_TEST );            
      glDisable( GL_CULL_FACE );            
      
      glDisable( GL_STENCIL_TEST );
      glDisable( GL_POLYGON_OFFSET_FILL );
      setPhongLightingShader();      
      drawLight();
      setCurrentObject();
      
      glEnable( GL_DEPTH_TEST );
      glEnable( GL_STENCIL_TEST );
      glClear( GL_STENCIL_BUFFER_BIT );
      glStencilFunc( GL_ALWAYS, 0x1, 0x1 );
      glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );
      glPushMatrix();
       glTranslatef( 0.0, -5.0, 0.0 );
       drawFloor();
      glPopMatrix();

      glDisable( GL_DEPTH_TEST );       
      glStencilFunc( GL_EQUAL, 0x1, 0x1 );
      
      glEnable( GL_POLYGON_OFFSET_FILL );
      glPolygonOffset( -1.0, -1.0 );
      setProjectionShadowsShader();      
      glPushMatrix();                 
       setCurrentObject();
      glPopMatrix();
    } 
  glPopMatrix();

	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT reshape function. 
// 
///////////////////////////////////////////////////////////////////////////////

void reshapeFunc( int w, int h )
{
  gWinTopRightCorner    = h;
  gWinBottomRightCorner = w;
  
  gTrackBallDiameter    = ( h > w ) ? h : w;

  glViewport( 0, 0, (GLsizei ) w, (GLsizei ) h );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 40.0, ( GLfloat ) w / ( GLfloat ) h, 0.1, 10000.0 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT mouse function. 
// 
///////////////////////////////////////////////////////////////////////////////

void mouseFunc( int button, int state, int x, int y )
{
  if( ( x < gWinBottomLeftCorner || x >  gWinBottomRightCorner ) || 
      ( y < gWinTopLeftCorner    || y >  gWinTopRightCorner    )  )
  {
      return;  
  }

  double x1 = ( 2.0f * x - gTrackBallDiameter ) / gTrackBallDiameter;
  double y1 = ( gTrackBallDiameter - 2.0f * y ) / gTrackBallDiameter;
  double z1 = sqrt( 1.0f - ( x1 * x1  - y1 * y1 ) );

  if( z1 >= 1.0f )
  {
    z1 = 1.0f;
  }

  gLastPosition.set( x1, y1, z1 );
  gmtl::normalize( gLastPosition );

  if( state == GLUT_DOWN )
  {
    switch( button )
    {
      case GLUT_LEFT_BUTTON: 
      {
        gUseMouseLeftButton = true;
        break;
      }
      case GLUT_RIGHT_BUTTON:
      {
        gUseMouseRightButton = true;
        break;
      }
    }
  }
  else if( state == GLUT_UP )
  {
    switch( button )
    {
      case GLUT_LEFT_BUTTON: 
      {
        gUseMouseLeftButton = false;
        break;
      }
      case GLUT_RIGHT_BUTTON:
      {
        gUseMouseRightButton = false;
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT mouse motion function. 
// 
///////////////////////////////////////////////////////////////////////////////

void mouseMotion( int x, int y )
{
  float dx, dy, dz, gAngle;
  float axis[3];

  if( ( x < gWinBottomLeftCorner || x >  gWinBottomRightCorner ) || 
      ( y < gWinTopLeftCorner    || y >  gWinTopRightCorner    )  )
  {
      return;  
  }

  double x1 = ( 2.0f * x - gTrackBallDiameter ) / gTrackBallDiameter;
  double y1 = ( gTrackBallDiameter - 2.0f * y ) / gTrackBallDiameter;
  double z1 = sqrt( 1.0f - ( x1 * x1  - y1 * y1 ) );

  if( z1 >= 1.0f )
  {
    z1 = 1.0f;
  }

  gCurrentPosition.set( x1, y1, z1 );
  gmtl::normalize( gCurrentPosition );

  dx = gCurrentPosition[0] - gLastPosition[0];
  dy = gCurrentPosition[1] - gLastPosition[1];
  dz = gCurrentPosition[2] - gLastPosition[2];

  if( dx || dy || dz )
  {
    axis[0] = gLastPosition[1] * gCurrentPosition[2] - gLastPosition[2] * gCurrentPosition[1];
    axis[1] = gLastPosition[2] * gCurrentPosition[0] - gLastPosition[0] * gCurrentPosition[2];
    axis[2] = gLastPosition[0] * gCurrentPosition[1] - gLastPosition[1] * gCurrentPosition[0];    

    gAngle = gmtl::length( gmtl::Vec3f( axis[0], axis[1], axis[2] ) ) * ( ( 180 * 7.0f ) / 22.0f );

    if( gUseMouseLeftButton )
    {       
      glMatrixMode( GL_MODELVIEW );                  
      glLoadIdentity();      
      glRotatef( gAngle, axis[0], axis[1], axis[2] );                  
      glGetFloatv( GL_MODELVIEW_MATRIX, gNavigationMatrix );

      gmtl::Matrix44f temp;
      temp.set( gNavigationMatrix );
      gmtl::preMult( gGmtlNavigationMatrix, temp );

      gLastPosition = gCurrentPosition;

      glutPostRedisplay();
    }
    if( gUseMouseRightButton )
    { 
      // Aply translation here. 
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT Keyboard function. 
// 
///////////////////////////////////////////////////////////////////////////////

void keyboradFunc( unsigned  char key, int mouseX, int mouseY )
{
  static float rot = 0.0f;

  switch( key )
  {    
    case '2':
    {
      gPosition = gPosition - 0.2;
      break;
    }
    case '8':
    {      
      gPosition = gPosition + 0.2;
      break;      
    }
    case 'a':
    {      
      rot = rot - 2.0;
      float rad = rot * ( 3.14159265 / 180.0f );
      gEyePosition[0] = 10.0 * sin( rad );    
      gEyePosition[2] = 10.0 * cos( rad ); 
      
      setRefractionShader();
      break;
    }
    case 'd':
    {
      rot = rot + 2.0;
      float rad = rot * ( 3.14159265 / 180.0f );
      gEyePosition[0] = 10.0 * sin( rad );    
      gEyePosition[2] = 10.0 * cos( rad );      
      break;
    }
  };

  glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//
// GLUT idle function. 
// 
///////////////////////////////////////////////////////////////////////////////

void idle()
{
  gAngle = gAngle + 1.0;

  if( gAngle >= 360.0 )
  {
    gAngle = 0.0;
  }

  //gLightPosition[0] =  0.0 * sin( gmtl::Math::deg2Rad( gAngle ) );
  //gLightPosition[2] =  5.0 * cos( gmtl::Math::deg2Rad( gAngle ) );

  glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//
// Draw callback. 
//
///////////////////////////////////////////////////////////////////////////////

void drawCallback( int control )
{
  if( control < gModels.size() )
  {
    switch( gCurrentObject )
    {
      case 0: gCurrentObjectId = "plane"; break;
      case 1: gCurrentObjectId = "sphere"; break;      
      case 2: gCurrentObjectId = "bunny"; break;
    };
  }

  setCurrentObject();

  glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//
// Control callback. 
//
///////////////////////////////////////////////////////////////////////////////

void controlCallback( int control )
{ 
  setCurrentShader();

  glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//
// Refract callback. 
//
///////////////////////////////////////////////////////////////////////////////

void refractCallback( int control )
{
  if( gCurrentShader == REFRACTION ) 
  {
     setRefractionShader(); 
  }
  else if( gCurrentShader == REFRACTION_WITH_DISPERSION )
  {
    setRefractionWithDispersionShader();
  }

  glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//
// Refract RGB callback. 
//
///////////////////////////////////////////////////////////////////////////////

void refractRGBCallback( int control )
{
  if( gCurrentShader == REFRACTION_WITH_DISPERSION )
  {
    setRefractionWithDispersionShader();
  }

  glutPostRedisplay();
}

void displaceCallback( int control )
{
  if( gCurrentShader == PER_PIXEL_DISPLACEMENT )
  {
    setPerPixelDisplacementShader();
    glutPostRedisplay();
  }
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
  gCurrentWindow = glutCreateWindow( "Author: Aashish Chaudhary - Demo Software" );  
	init();  	

  if( argc > 1 )
  {
    gPerPixelBase   = argv[1];
    gPerPixelNormal = argv[2];
    gPerPixelHeight = argv[3];
  }

  // Load textures and bind them. 
  loadCubeMap();    
  //loadBumpMap();
  //loadSphereMap();	
  //loadDisplacementMap();
  loadDistanceMap();
  loadDistanceBaseMap();
  loadEnvMap();

	glutDisplayFunc ( display );
  glutMouseFunc   ( mouseFunc );
  glutMotionFunc  ( mouseMotion );	
  glutKeyboardFunc( keyboradFunc ); 
  glutReshapeFunc ( reshapeFunc );
  glutIdleFunc    ( idle );  

  // GLUI code.   

  GLUI *glui = GLUI_Master.create_glui( "Project1: Controller", 800, 0, 0  );  

  new GLUI_StaticText( glui, "Controller" );
  new GLUI_Separator( glui );
  
  GLUI_Panel *obj_panel = new GLUI_Panel( glui, "Object Type" );
  
  radioObj = new GLUI_RadioGroup( obj_panel, &gCurrentObject, 1, drawCallback );
  new GLUI_RadioButton( radioObj, "Plane" );
  new GLUI_RadioButton( radioObj, "Sphere" );  
  new GLUI_RadioButton( radioObj, "Bunny" );   

  GLUI_Panel *shader_panel = new GLUI_Panel( glui, "gCurrentShader Type" );
  radioShader = new GLUI_RadioGroup( shader_panel, &gCurrentShader, 2, controlCallback );
  new GLUI_RadioButton( radioShader, "Phong Lighting" );
  new GLUI_RadioButton( radioShader, "Phong Shading" );
  new GLUI_RadioButton( radioShader, "Blinn-Phong Shading" );   
  new GLUI_RadioButton( radioShader, "Schlick Shading" );   
  new GLUI_RadioButton( radioShader, "Cube Map Reflection" );   
  new GLUI_RadioButton( radioShader, "Sphere Map Reflection" );   
  new GLUI_RadioButton( radioShader, "Cube Map Refraction" );   
  new GLUI_RadioButton( radioShader, "Cube Map Refraction w Dispersion" );     
  new GLUI_RadioButton( radioShader, "Bump Map" );   
  new GLUI_RadioButton( radioShader, "Bump Map Env Map" );     
  new GLUI_RadioButton( radioShader, "Displacement" );     
  new GLUI_RadioButton( radioShader, "PerPixelDisplacement" );     

  GLUI_Panel *mat_panel = new GLUI_Panel( glui, "Material" );
  spinner1  = new GLUI_Spinner( mat_panel, "Ambient  R:", &gMatAmbient[0], 2, controlCallback );
  spinner2  = new GLUI_Spinner( mat_panel, "Ambient  G:", &gMatAmbient[1], 2, controlCallback );
  spinner3  = new GLUI_Spinner( mat_panel, "Ambient  B:", &gMatAmbient[2], 2, controlCallback );

  spinner1->set_w( 5.0 );

  spinner4  = new GLUI_Spinner( mat_panel, "Diffuse    R:", &gMatDiffuse[0], 2, controlCallback );
  spinner5  = new GLUI_Spinner( mat_panel, "Diffuse    G:", &gMatDiffuse[1], 2, controlCallback );
  spinner6  = new GLUI_Spinner( mat_panel, "Diffuse    B:", &gMatDiffuse[2], 2, controlCallback );  

  spinner7  = new GLUI_Spinner( mat_panel, "Specular R:", &gMatSpecular[0], 2, controlCallback );
  spinner8  = new GLUI_Spinner( mat_panel, "Specular G:", &gMatSpecular[1], 2, controlCallback );
  spinner9  = new GLUI_Spinner( mat_panel, "Specular B:", &gMatSpecular[2], 2, controlCallback );
  
  spinner10 = new GLUI_Spinner( mat_panel, "Material N:", &gMatShininess, 2, controlCallback );

  GLUI_Panel *light_panel = new GLUI_Panel( glui, "Light" );
  spinner11  = new GLUI_Spinner( light_panel, "Ambient  R:", &gLightAmbient[0], 2, controlCallback );
  spinner12  = new GLUI_Spinner( light_panel, "Ambient  G:", &gLightAmbient[1], 2, controlCallback );
  spinner13  = new GLUI_Spinner( light_panel, "Ambient  B:", &gLightAmbient[2], 2, controlCallback );

  spinner14  = new GLUI_Spinner( light_panel, "Diffuse    R:", &gLightDiffuse[0], 2, controlCallback );
  spinner15  = new GLUI_Spinner( light_panel, "Diffuse    G:", &gLightDiffuse[1], 2, controlCallback );
  spinner16  = new GLUI_Spinner( light_panel, "Diffuse    B:", &gLightDiffuse[2], 2, controlCallback );

  spinner17  = new GLUI_Spinner( light_panel, "Specular R:", &gLightSpecular[0], 2, controlCallback );
  spinner18  = new GLUI_Spinner( light_panel, "Specular G:", &gLightSpecular[1], 2, controlCallback );
  spinner19  = new GLUI_Spinner( light_panel, "Specular B:", &gLightSpecular[2], 2, controlCallback );  

  glui->add_column( true );

  GLUI_Panel *refrac_panel = new GLUI_Panel( glui, "Refraction" );

  spinner20  = new GLUI_Spinner( refrac_panel, "Eta :   ", &gEta,     1,  refractCallback );
  spinner20  = new GLUI_Spinner( refrac_panel, "Fresnel:", &gFresnel, 2,  refractCallback );

  spinner21  = new GLUI_Spinner( refrac_panel, "Eta R:  ", &gEtaR,    2,  refractRGBCallback );
  spinner22  = new GLUI_Spinner( refrac_panel, "Eta G:  ", &gEtaG,    2,  refractRGBCallback );
  spinner23  = new GLUI_Spinner( refrac_panel, "Eta B:  ", &gEtaB,    2,  refractRGBCallback );     


  GLUI_Panel *displace_panel = new GLUI_Panel( glui, "PerPixelDisplacement" );
  spinner24  = new GLUI_Spinner( displace_panel, "Bump Depth:", &gBumpDepth, 2, displaceCallback );       

  glui->set_main_gfx_window( gCurrentWindow );

  
  GLUI_Master.set_glutIdleFunc( idle );
	glutMainLoop();	
	
	return EXIT_SUCCESS;
}
