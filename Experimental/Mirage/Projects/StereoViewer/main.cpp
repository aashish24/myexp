

#ifdef _MSC_VER
#include <windows.h>
#endif 

//#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glut.h"

#include "BmpImage.h"

#include <iostream>
#include <vector>

typedef std::vector< std::pair< GLuint, GLuint > >  StereoTextures;
StereoTextures _gStereoTextures;

typedef std::vector< std::pair< int, int > > StereoImageDimensions;
StereoImageDimensions _gStereoImageDimensions;

// Quad size. 
float _gWidth = 1.0f; 
float _gHeight = 1.0f;

// Global for counting the index for the stereo image. 
unsigned int _gStereoPairIndex = 0;

GLuint loadTexture( std::string fileName )
{
  // Load normal map.    
    //IMAGE image;
    BmpImage* image;

    try
    {  
      BmpImage* loader = new BmpImage( fileName );    
      //iimage.Load( const_cast< char* >( fileName.c_str() ) );
      //image.ExpandPalette();
      image  = loader;
    }
    catch( std::exception& e )
    {
      std::cerr << " ERROR 1120598588: " << e.what() << std::endl;
      throw;
    }
    catch( ... )
    {
      std::cerr << " ERROR 3490106803: Unknown error. " << std::endl;
      throw;
    }

    if( ! image->getBitmap()  )
    {
      throw " ERROR 7626153710: Image contains invalid or no data. ";
    }

    GLuint index;
    glGenTextures( 1,  &index );
    glBindTexture( GL_TEXTURE_2D, index );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8,
                       image->getWidth(), image->getHeight(),
                       GL_RGB,
                       GL_UNSIGNED_BYTE, image->getBitmap() ); 


   _gStereoImageDimensions.push_back( std::pair< int, int >( image->getWidth(), image->getHeight() ) );
 
    return index;
}


void loadTextures( std::vector< std::string >& fileNames )
{
  // Assuming we are going to get two images per stereo pair. 
  
  for( size_t i=0; i < fileNames.size() / 2; i=i+2 )
  {
    GLint index1 = loadTexture( fileNames[i] );
    GLint index2 = loadTexture( fileNames[i+1] );

    _gStereoTextures.push_back( std::pair< GLint, GLint >( index1, index2 ) );
  }
}


void drawQuad() 
{  
  glBegin( GL_QUADS );
    glTexCoord2f( 0.0f, 0.0f ); 
    glVertex2f( 0.0, 0.0 );
    glTexCoord2f( 1.0f, 0.0f ); 
    glVertex2f(  _gWidth, 0.0f );
    glTexCoord2f( 1.0f, 1.0f ); 
    glVertex2f(  _gWidth,  _gHeight );
    glTexCoord2f( 0.0f, 1.0f ); 
    glVertex2f( 0.0f,  _gHeight );
  glEnd();
}


void drawLeft()
{
  glDrawBuffer( GL_BACK_LEFT );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
 
  glEnable( GL_TEXTURE_2D ); 
  glPushMatrix(); 
    //std::cout << "index is: " << _gStereoTextures[_gStereoPairIndex].first << std::endl;
    glBindTexture( GL_TEXTURE_2D, _gStereoTextures[_gStereoPairIndex].first );
    drawQuad();
  glPopMatrix();
  glDisable( GL_TEXTURE_2D );
}


void drawRight()
{
  glDrawBuffer( GL_BACK_RIGHT );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
 
  glEnable( GL_TEXTURE_2D ); 
  glPushMatrix();
     //std::cout << "index is: " << _gStereoTextures[_gStereoPairIndex].second << std::endl;
     glBindTexture( GL_TEXTURE_2D, _gStereoTextures[_gStereoPairIndex].second );
    drawQuad();
  glPopMatrix();
  glDisable( GL_TEXTURE_2D );
}


void display()
{ 
  glDrawBuffer( GL_BACK );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  drawLeft(); 
  drawRight();
  glutSwapBuffers();
}


void reshape( int w, int h )
{
  glViewport( 0, 0, (GLsizei ) w, (GLsizei ) h );

  glMatrixMode( GL_PROJECTION );    
  glLoadIdentity();
  //gluPerspective( 40.0f, ( GLfloat ) w / ( GLfloat ) h, 0.1f, 10000.0f );
  glOrtho( 0.0f, _gWidth, 0.0f, _gHeight, 0.1f, 10000.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}


void idle()
{
}


void init()
{
  // Set OpenGL states. 
  glEnable( GL_DEPTH_TEST);
  glEnable( GL_TEXTURE_2D );
  
  //glEnable( GL_LIGHTING );
  //glEnable( GL_LIGHT0 );

  //glShadeModel( GL_SMOOTH );
}


void parseArguments( int& argc, char** argv )
{
  std::vector< std::string > images; 

  for( int i=1; i < argc; ++i )
  {
    images.push_back( argv[i] );
  }


  // Now load these textures. 
  loadTextures( images );  
}


void initScene()
{
  if( _gStereoPairIndex >= _gStereoTextures.size() )
  {
    throw "ERROR: Stereo pair index has higher value than number of pairs";    
  }
	
  if( ( _gStereoImageDimensions[_gStereoPairIndex].first != _gStereoImageDimensions[_gStereoPairIndex + 1].first ) ||
      ( _gStereoImageDimensions[_gStereoPairIndex].second != _gStereoImageDimensions[_gStereoPairIndex + 1].second ) )
  {
    throw "ERROR: Stereo pair images does not have the same dimensions: ";	
  }  

  
  _gHeight = (  _gStereoImageDimensions[_gStereoPairIndex].first /  _gStereoImageDimensions[_gStereoPairIndex].second ) * _gHeight; 
}



int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO );
  glutInitWindowSize( 1280, 1024 );
  glutCreateWindow( "Stereo Viewer" ); 

  // Initialization. 
  init();

  // Parse command line arguments. 
  parseArguments( argc, argv );

  // 
  initScene(); 

  // Set display function. 
  glutDisplayFunc( display );

  // Reshape function.
  glutReshapeFunc( reshape );

  // Idle function. 
  glutIdleFunc( idle );

  // Run the loop. 
  glutMainLoop();
}
