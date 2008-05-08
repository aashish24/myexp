
#ifdef _MSC_VER
#include <windows.h>
#endif 

#include "GL/gl.h"
#include "GL/glut.h"

#include "BmpImage.h"

#include <iostream>
#include <vector>
#include <string>

// Data structure that represents each image. 
struct ImageElem
{
  int         _width;
  int         _height;
  std::string _fileName;
};


// Data structure that represents each stereo pair. 
struct StereoImagePair
{
  std::pair< ImageElem, ImageElem > _imageElemPair;
};


// Data structure that represents each OpenGL stereo pair. 
struct GLStereoImagePair : public StereoImagePair 
{
  std::pair< GLuint, GLuint > _textureObjectPair;
};


typedef std::vector< GLStereoImagePair > GLStereoImagePairs;
GLStereoImagePairs _gGLStereoImagePairs;

// Quad size. 
float _gWidth = 1.0f; 
float _gHeight = 1.0f;

// Global for counting the index for the stereo pair index. 
unsigned int _gStereoImagePairIndex = 0;

GLuint loadTexture( std::string fileName, ImageElem& imageElem )
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


    imageElem._fileName = fileName;
    imageElem._width = image->getWidth();
    imageElem._height = image->getHeight();

    delete image;

   //_gStereoImageDimensions.push_back( std::pair< int, int >( image->getWidth(), image->getHeight() ) );
 
    return index;
}


void loadStereoImagesAsTextures( std::vector< std::string >& fileNames )
{
  if( fileNames.empty() )
  {
    std::cerr << "ERROR: No input file. " << std::endl;
    std::exit( 0 );
    return;
  }

  // Assuming we are going to get two images per stereo pair.   
  if( fileNames.size() < 2 != 0 )
  {
    std::cerr << "ERROR: Required two images per pair. " << std::endl;
    std::exit( 0 );
  }

  for( size_t i=0; i < fileNames.size() / 2; i=i+2 )
  {
    ImageElem imageElem1;
    ImageElem imageElem2; 

    try
    {
      GLint index1 = loadTexture( fileNames[i], imageElem1 );
      GLint index2 = loadTexture( fileNames[i+1], imageElem2 );

      GLStereoImagePair sp; 
      sp._imageElemPair = std::pair< ImageElem, ImageElem >( imageElem1, imageElem2 );
      sp._textureObjectPair = std::pair< GLuint, GLuint >( index1, index2 );

      _gGLStereoImagePairs.push_back( sp );
    }
    catch( std::exception& e )
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      std::exit( 0 );
    }
    catch( std::string s )
    {
      std::cerr << s << std::endl;
      std::exit( 0 );
    }
    catch( ... )
    {
      std::cerr << "ERROR: Unknown error. " << std::endl;
      std::exit( 0 );
    }

    //_gStereoTextures.push_back( std::pair< GLint, GLint >( index1, index2 ) );
  }
}


void drawQuad() 
{  
  glBegin( GL_QUADS );
    glTexCoord2f( 0.0f, 0.0f ); 
    glVertex2f( 0.0f, 0.0f );
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
  gluLookAt( 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
 
  glEnable( GL_TEXTURE_2D ); 
  glPushMatrix();     
    //std::cout << "index is: " << _gStereoTextures[_gStereoImagePairIndex].first << std::endl;
    glBindTexture( GL_TEXTURE_2D, _gGLStereoImagePairs[_gStereoImagePairIndex]._textureObjectPair.first );
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
    //std::cout << "index is: " << _gStereoTextures[_gStereoImagePairIndex].second << std::endl;     
    glBindTexture( GL_TEXTURE_2D, _gGLStereoImagePairs[_gStereoImagePairIndex]._textureObjectPair.second );
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
  glDisable( GL_LIGHTING );  
}


void parseArguments( int& argc, char** argv )
{
  std::vector< std::string > images; 

  for( int i=1; i < argc; ++i )
  {
    images.push_back( argv[i] );
  }

  // Now load these textures. 
  loadStereoImagesAsTextures( images );  
}


void initScene()
{
  //if( _gStereoImagePairIndex >= _gStereoTextures.size() )
  if( _gStereoImagePairIndex >= _gGLStereoImagePairs.size() )
  {
    std::cerr << "ERROR: Stereo pair index has higher value than number of pairs" << std::endl;    
    std::exit( 0 );
  }

  if( ( _gGLStereoImagePairs[_gStereoImagePairIndex]._imageElemPair.first._width != _gGLStereoImagePairs[_gStereoImagePairIndex]._imageElemPair.second._width ) ||
      ( _gGLStereoImagePairs[_gStereoImagePairIndex]._imageElemPair.first._height != _gGLStereoImagePairs[_gStereoImagePairIndex]._imageElemPair.second._height ) )        
  {
    std::cerr << "ERROR: Stereo pair images does not have the same dimensions: " << std::endl;	  
    std::exit( 0 );
  }

  _gHeight = (  ( float )_gGLStereoImagePairs[_gStereoImagePairIndex]._imageElemPair.first._height /  
                ( float )_gGLStereoImagePairs[_gStereoImagePairIndex]._imageElemPair.first._width ) * _gHeight; 
} 


void myDisplay() 
{
  glutSwapBuffers();
}


int main( int argc, char** argv )
{
  const int windowWidth  = 1280; 
  const int windowHeight = 1280; 

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO );  
  glutInitWindowSize( windowWidth, windowHeight );
  glutCreateWindow( "Stereo Viewer" ); 

  // Initialization. 
  init();

  // Parse command line arguments. 
  parseArguments( argc, argv );

  // 
  initScene(); 

  // Reshape window size based on the aspect ratio of the image. 
  int newHeight = windowHeight * _gHeight;
  if( newHeight > 0 )
  {
    glutReshapeWindow( windowWidth, newHeight );
  }

  // Set display function. 
  glutDisplayFunc( display );  

  // Reshape function.
  glutReshapeFunc( reshape );

  // Idle function. 
  glutIdleFunc( idle );

  // Run the loop. 
  glutMainLoop();
}
