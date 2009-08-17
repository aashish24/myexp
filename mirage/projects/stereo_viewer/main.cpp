
///////////////////////////////////////////////////////////////////////////////
//
// Created By: Aashish Chaudhary
// Authors: Aashish Chaudhary, Dirk Reiners
//
///////////////////////////////////////////////////////////////////////////////


#ifdef _WIN32
  #include <GL/glew.h>
#else
  #ifdef __APPLE__
    #include <GL/glew.h>
  #else
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
  #endif
#endif

#ifdef _MSC_VER
  #include <windows.h>
  #define strcasecmp _strcmpi

#define strcasecmp _strcmpi
#endif 

#include "GL/gl.h"
#include "GL/glut.h"

#include "BmpImage.h"
#include "TgaImage.h"

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

// Options
typedef enum { 
    MONO = 1, 
    ACTIVE, 
    LEFT_RIGHT, 
    INTERLEAVED, 
    SHARP, 
    WOBBLE 
} StereoModeE;

StereoModeE displayMode;

bool canActive = false;
bool canInterleave = false;

bool useMipmaps = false;


std::vector< std::string > images; 

// Data structure that represents each image. 
struct ImageElem
{
  int         _width;
  int         _height;
  std::string _fileName;
  GLuint      _glId;
  float       _aspect; // width/height
};


// Data structure that represents each stereo pair. 
struct StereoImagePair
{
  ImageElem _left, _right;
};

typedef std::vector< StereoImagePair > StereoImagePairs;
StereoImagePairs stereoImagePairs;



// Global for counting the index for the stereo pair index. 
unsigned int imageIndex = 0;

// Window size
int windowWidth  = 1280; 
int windowHeight = 1000; 
int windowX = -1; 
int windowY = -1; 

float wobble_delta = 100;

bool flipOnLoad = false;

// FBO/Interleave data

GLuint il_texleft, il_texright;
GLuint il_fbo, il_depthbuffer;

GLuint il_vshader, il_fshader, il_sharp_fshader;
GLuint il_program = 0, il_sharp_program;

extern const GLchar *vshader_source, *fshader_source, *sharp_fshader_source;

// work data

int mousex, mousey; // Mouse click position
int mousebut;       // Mouse button state
float baseviewx, baseviewy; // Viewer position when mouse was pressed

float viewx = 0.f, viewy = 0.f, viewz = 1.1f; // Viewer Position

int wobble_last = 0;
bool wobble_left = true;

// Helper functions

GLuint loadTexture( std::string fileName, ImageElem& imageElem )
{
    int extind = fileName.rfind('.');
    std::string ext(&(fileName.c_str()[extind+1]));

    BmpImage* bmpimage = 0;
    TgaImage *tgaimage = 0;
    
    int width, height;
    void *pixels;
    
    if(ext == "BMP" || ext == "bmp")
    {   
      try
      {  
        bmpimage = new BmpImage( fileName );    
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

      if( ! bmpimage->getBitmap()  )
      {
        throw " ERROR 7626153710: Image contains invalid or no data. ";
      }
      
      width = bmpimage->getWidth();
      height = bmpimage->getHeight();
      pixels = bmpimage->getBitmap();
    }
    else if (ext == "TGA" || ext == "tga")
    {
      tgaimage = new TgaImage(fileName);
      
      width = tgaimage->getWidth();
      height = tgaimage->getHeight();
      pixels = tgaimage->getPixels();
      
    }

    GLuint index;
    glGenTextures( 1,  &index );
    glBindTexture( GL_TEXTURE_2D, index );
    if(useMipmaps)
    {
      gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, width, height,
                         GL_RGB, GL_UNSIGNED_BYTE, pixels ); 
    }
    else
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, pixels); 
                   
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    imageElem._fileName = fileName;
    imageElem._width    = width;
    imageElem._height   = height;
    
    imageElem._aspect   = imageElem._width / (float) imageElem._height;
    
    imageElem._glId     = index;

    if(bmpimage)
      delete bmpimage;
      
     if(tgaimage)
      delete tgaimage;

    return index;
}


void loadStereoImagesAsTextures( std::vector< std::string >& fileNames )
{
  if( fileNames.empty() )
  {
    std::cerr << " ERROR: No input file. " << std::endl;
    std::exit( 0 );
    return;
  }

  // Assuming we are going to get two images per stereo pair.   
  if( fileNames.size() < 2 != 0 )
  {
    std::cerr << " ERROR: Required two images per pair. " << std::endl;
    std::exit( 0 );
  }

  if( fileNames.size() %2 != 0 )
  {
    std::cerr << " WARNING: Odd count of file names as arguments. " << std::endl;
    std::cerr << " Ignoring last file. " << std::endl;
  }

  size_t j = 0;
  for( size_t i=0; i < fileNames.size() / 2; ++i )
  {
    try
    {
      StereoImagePair sp;
      
      loadTexture( fileNames[j]  , sp._left );
      loadTexture( fileNames[j+1], sp._right );

      stereoImagePairs.push_back( sp );

      j += 2;
    }
    catch( std::exception& e )
    {
      std::cerr << " ERROR: " << e.what() << std::endl;
      std::exit( 0 );
    }
    catch( std::string s )
    {
      std::cerr << s << std::endl;
      std::exit( 0 );
    }
    catch( ... )
    {
      std::cerr << " ERROR: Unknown error. " << std::endl;
      std::exit( 0 );
    }

    //_gStereoTextures.push_back( std::pair< GLint, GLint >( index1, index2 ) );
  }
}


void drawQuad(ImageElem &img) 
{  
  glBegin( GL_QUADS );
    glTexCoord2f( 0.0f, 0.0f ); 
    glVertex2f  ( -img._aspect, -1.f );
    glTexCoord2f( 1.0f, 0.0f ); 
    glVertex2f  (  img._aspect, -1.f );
    glTexCoord2f( 1.0f, 1.0f ); 
    glVertex2f  (  img._aspect,  1.f );
    glTexCoord2f( 0.0f, 1.0f ); 
    glVertex2f  ( -img._aspect,  1.f );
  glEnd();
}


void drawImage(ImageElem &img) 
{
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( viewx, viewy, viewz, viewx, viewy, 0.0, 0.0, 1.0, 0.0 );
 
  glEnable( GL_TEXTURE_2D ); 
  glBindTexture( GL_TEXTURE_2D, img._glId );
  drawQuad(img);
  glDisable( GL_TEXTURE_2D );
}


void drawInterleaved(GLuint program)
{  
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, il_fbo);

  // Draw left eye

  glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  drawImage(stereoImagePairs[imageIndex]._left);

  // Draw right eye
  glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  drawImage(stereoImagePairs[imageIndex]._right);

  // Draw interleaved image
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

  glUseProgram(program); 

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,windowWidth-1,0,windowHeight-1,-5,5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE1);   
  glBindTexture(GL_TEXTURE_2D, il_texright);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, il_texleft);

  glBegin(GL_QUADS);
  glTexCoord2f     (0,0);
  glMultiTexCoord2f(GL_TEXTURE1, 0,             0 );               
  glVertex3f       (0,              0,              0);
  glTexCoord2f     (1,0);
  glMultiTexCoord2f(GL_TEXTURE1, windowWidth/2, 0 );               
  glVertex3f       (windowWidth-1, 0,               0);
  glTexCoord2f     (1,1);
  glMultiTexCoord2f(GL_TEXTURE1, windowWidth/2, windowHeight/2 );  
  glVertex3f       (windowWidth-1,  windowHeight-1, 0);
  glTexCoord2f     (0,1);
  glMultiTexCoord2f(GL_TEXTURE1, 0,             windowHeight/2  ); 
  glVertex3f       (0,              windowHeight-1, 0);
  glEnd();

  glUseProgram(0); 

  glActiveTexture(GL_TEXTURE1);   
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void display()
{ 
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  switch(displayMode)
  {
  case ACTIVE:  
  
      glDrawBuffer( GL_BACK_LEFT );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      drawImage(stereoImagePairs[imageIndex]._left);
      glDrawBuffer( GL_BACK_RIGHT );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      drawImage(stereoImagePairs[imageIndex]._right);
      break;

  case MONO:
  
      glDrawBuffer( GL_BACK );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      drawImage(stereoImagePairs[imageIndex]._left);
      break;

  case LEFT_RIGHT:
  
      glDrawBuffer( GL_BACK );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glViewport( 0, 0, windowWidth/2, windowHeight );
      drawImage(stereoImagePairs[imageIndex]._left);
      glViewport( windowWidth/2, 0, windowWidth/2, windowHeight );
      drawImage(stereoImagePairs[imageIndex]._right);
      break;

  case INTERLEAVED:
  
      drawInterleaved(il_program);
      
      break;

  case SHARP:
  
      drawInterleaved(il_sharp_program);
      
      break;

  case WOBBLE:
  
      glDrawBuffer( GL_BACK );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      if(wobble_left)
      {
        drawImage(stereoImagePairs[imageIndex]._left);
      }
      else
      {
        drawImage(stereoImagePairs[imageIndex]._right);
      }
      
      int now = (int)(glutGet(GLUT_ELAPSED_TIME) / wobble_delta);
      
      if(now != wobble_last)
      {
        wobble_left = ! wobble_left;
        wobble_last = now;
      }
      
      break;
  }
  
  glutSwapBuffers();
}


void reshape( int w, int h )
{
  glViewport( 0, 0, (GLsizei ) w, (GLsizei ) h );

  glMatrixMode( GL_PROJECTION );    
  glLoadIdentity();
  
  float aspect = w / (float) h;
  
  if(displayMode == LEFT_RIGHT)
  {
    aspect /= 2;
  }
  
  gluPerspective( 90.0f, aspect, 0.001f, 10000.0f ); 
  //glOrtho( -aspect, aspect, -1.f, 1.f, 0.1f, 10000.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  windowWidth = w;
  windowHeight = h;

  if(il_program != 0)
  {
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glBindTexture(GL_TEXTURE_2D, il_texleft);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, il_texright);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  }
  glutPostRedisplay();
}


void mouseButton(int but, int state, int x, int y)
{
  //cout << "mouseButton: button " << but << " state " << state << " at " << x << "," << y << endl;

  if(but == 0)   // Left button?
  {    
    if(state == 0)   // pressed?
    {
      mousex = x;
      mousey = y;
      mousebut |=   1 << but;

      baseviewx = viewx;
      baseviewy = viewy;
    }
    else
    {
      mousebut &= ~(1 << but);
    }
  }
  
  if(but == 3)  // Mouse wheel forward
  {
    if (state == 0)
    {
      viewz *= 0.9;
      //std::cout << "Viewz now " << viewz << std::endl;
    }
  }
  
  if(but == 4)  // Mouse wheel forward
  {
    if (state == 0)
    {
      viewz *= 1.1;
      //std::cout << "Viewz now " << viewz << std::endl;
    }
  }

  // Force a redraw
  glutPostRedisplay();    
}


void mouseMotion(int x, int y)
{
    //cout << "mouseMotion: at " << x << "," << y << "\r";
    //cout.flush();

    if(mousebut & 1)  // Left button pressed?
    {
      int mdx = x - mousex;
      int mdy = y - mousey;
      
      float dx = mdx / (float)windowWidth  * 2.f * viewz;
      float dy = mdy / (float)windowHeight * 2.f * viewz;
      
      viewx = baseviewx - dx;
      viewy = baseviewy + dy;
      
      //cout << "mouseMotion: mdx="<<mdx<<" mdy="<< mdy<<endl;
      //cout << "mouseMotion: dx="<<dx<<" dy="<<dy<<endl;
      //cout << "mouseMotion: viewx="<<viewx<<" viewy="<<viewy<<endl;
    }
    
    // Force a redraw
    glutPostRedisplay();    
}

void idle()
{
  if(displayMode == WOBBLE)
  {
    glutPostRedisplay();
  }
}


void printShaderInfoLog(GLuint obj)
{
  GLint infologLength = 0;
  GLsizei charsWritten  = 0;
  char *infoLog;

  glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 0)
  {
    infoLog = (char *)malloc(infologLength);
    glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
    std::cout << infoLog << endl;
    free(infoLog);
  }
}


void printProgramInfoLog(GLuint obj)
{
  GLint infologLength = 0;
  GLsizei charsWritten  = 0;
  char *infoLog;

  glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

  if (infologLength > 0)
  {
    infoLog = (char *)malloc(infologLength);
    glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
    std::cout << infoLog << endl;
    free(infoLog);
  }
}


void init()
{
  // Set OpenGL states. 
  glEnable( GL_DEPTH_TEST);
  glEnable( GL_TEXTURE_2D );  
  glDisable( GL_LIGHTING );  

  // We need word alignment here instead of bye alignment as used earlier which
  // was causing some shear effect on the image when applied over the polygon. 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  if(canInterleave)
  {
    // Setup the FBO
    
    glGenTextures(1, &il_texleft);
    glBindTexture  (GL_TEXTURE_2D, il_texleft);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    glGenTextures(1, &il_texright);
    glBindTexture  (GL_TEXTURE_2D, il_texright);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);


    glGenFramebuffersEXT(1, &il_fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, il_fbo);

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, il_texleft, 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, il_texright, 0);

    glGenRenderbuffersEXT(1, &il_depthbuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, il_depthbuffer);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 1, 1);         	
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, il_depthbuffer);


    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
    {
      canInterleave = false;
      cerr << "Error setting up FBO!" << endl;
    }

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the _framebuffer for now

    
    // Setup the shaders

    il_vshader = glCreateShader(GL_VERTEX_SHADER);
    il_fshader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(il_vshader, 1, &vshader_source, NULL);
    glShaderSource(il_fshader, 1, &fshader_source, NULL);

    glCompileShader(il_vshader);
    glCompileShader(il_fshader);

    il_program = glCreateProgram();
    glAttachShader(il_program,il_fshader);
    glAttachShader(il_program,il_vshader);

    glLinkProgram(il_program);
    glUseProgram(il_program); 
    
    printProgramInfoLog(il_program);   
    printShaderInfoLog(il_vshader);
    printShaderInfoLog(il_fshader);
    
    glUniform1i(glGetUniformLocation(il_program,"right_eye"),1);
    glUniform1i(glGetUniformLocation(il_program,"left_eye"),0);

    // Sharp Autostereo shaders
    il_sharp_fshader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(il_sharp_fshader, 1, &sharp_fshader_source, NULL);

    glCompileShader(il_sharp_fshader);

    il_sharp_program = glCreateProgram();
    glAttachShader(il_sharp_program,il_sharp_fshader);
    glAttachShader(il_sharp_program,il_vshader);

    glLinkProgram(il_sharp_program);
    glUseProgram(il_sharp_program); 
    
    printProgramInfoLog(il_sharp_program);   
    printShaderInfoLog(il_sharp_fshader);
    
    // Set sampler uniforms
    glUniform1i(glGetUniformLocation(il_sharp_program,"right_eye"),1);
    glUniform1i(glGetUniformLocation(il_sharp_program,"left_eye"),0);

    glUseProgram(0); 
  }
}


void parseArguments( int& argc, char* argv[] )
{
  int ind;
  
  // Pick up options
  
  displayMode = MONO;
  
  for(ind = 1; ind < argc; ++ind)
  {
    if(argv[ind][0] != '-')
      break;
      
    if(!strcmp(argv[ind], "-mode"))
    {
      std::cout << "Stereo mode " << argv[ind+1] << std::endl;
      
           if(!strcasecmp(argv[ind+1], "mono"))         displayMode = MONO;
      else if(!strcasecmp(argv[ind+1], "active"))       displayMode = ACTIVE;
      else if(!strcasecmp(argv[ind+1], "left-right"))   displayMode = LEFT_RIGHT;
      else if(!strcasecmp(argv[ind+1], "interleaved"))  displayMode = INTERLEAVED;
      else if(!strcasecmp(argv[ind+1], "sharp"))        displayMode = SHARP;
      else if(!strcasecmp(argv[ind+1], "wobble"))       displayMode = WOBBLE;
      else 
      {
        std::cerr << "Unknown mode, using mono." << std::endl;
        displayMode = MONO;
      }
      ++ind;
    }
    else if(!strncmp(argv[ind], "-geo", 4))
    {
      int n = sscanf(argv[ind + 1], "%dx%d+%d+%d", &windowWidth, &windowHeight,
                                                   &windowX, &windowY);
      if (n < 2)
      {
        std::cerr << "Error scanning window size '" << argv[ind + 1] 
                  << "', ignored." << std::endl;
        windowWidth = 1000;
        windowHeight = 1000;
        windowX = 0;
        windowY = 0;
      }  
      else if (n < 4)
      {
        windowX = 0;
        windowY = 0;
      }  
      else
      {
        std::cout << "Window " << windowWidth << "x" 
                  << windowHeight << "+" << windowX 
                  << "+" << windowY << std::endl;
        
      }    
      ++ind;
    }
    else if(!strncmp(argv[ind], "-mip", 4))
    {
      useMipmaps = true;
    }
    else if(!strncmp(argv[ind], "-flip", 5))
    {
      flipOnLoad = true;
    }
    else
    {
      std::cerr << "Unknown command " << argv[ind] << ", ignored." 
                << std::endl;
    }
  }
  


  for(; ind < argc; ++ind )
  {
    images.push_back( argv[ind] );
  }
}


void initScene()
{
  //if( imageIndex >= _gStereoTextures.size() )
  if( imageIndex >= stereoImagePairs.size() )
  {
    std::cerr << "ERROR: Stereo pair index has higher value than number of pairs" << std::endl;    
    std::exit( 0 );
  }

  if( ( stereoImagePairs[imageIndex]._left._width != stereoImagePairs[imageIndex]._right._width ) ||
      ( stereoImagePairs[imageIndex]._left._height != stereoImagePairs[imageIndex]._right._height ) )        
  {
    std::cerr << "ERROR: Stereo pair images does not have the same dimensions: " << std::endl;	  
    std::exit( 0 );
  } 
} 


void appExit()
{
  std::cout << "Application exiting. " << std::endl;
  std::exit( 0 );
}


void update()
{
  if( imageIndex < 0 || ( imageIndex > ( stereoImagePairs.size() - 1 ) ) )
  {
    imageIndex = 0;
  }  
  else
  {
    // Do nothing. 
  }

  viewx = viewy = 0;
  viewz = 1.1;
  
  glutPostRedisplay();
}


void flipLeftRight(void)
{
  ImageElem dummy;
  for(int i=0; i < stereoImagePairs.size(); ++i)
  {
    dummy = stereoImagePairs[i]._left;
    stereoImagePairs[i]._left = stereoImagePairs[i]._right;
    stereoImagePairs[i]._right = dummy;
  }
}


void keyboard( unsigned char key, int x, int y )
{
  switch( key )
  {
    case 'e' : 
    case 27 : 
    {
      appExit();
      break;
    }
    case 'p': 
    {
      --imageIndex;
      update();
      break;
    }
    case 'n': 
    {
      ++imageIndex;
      update();
      break;
    }
    case 'k':
    {
      viewz *= 0.9;
      glutPostRedisplay();
      break;
    }
    case 'l':
    {
      viewz *= 1.1;
      glutPostRedisplay();
      break;
    }
    case 'a':
    {
      wobble_delta *= 0.9;
      cout << "wobble_delta now " << wobble_delta << endl;
      break;
    }
    case 's':
    {
      wobble_delta *= 1.1;
      cout << "wobble_delta now " << wobble_delta << endl;
      break;
    }
    case 'f':
    {
      flipLeftRight();
      cout << "Flipped left/right" << endl;
      glutPostRedisplay();
      break;
    }
    
  }; // switch( key ).
}


void menu(int val)
{
  if(val >= 0x100 && val < 0x200)
  {
    imageIndex = val - 0x100;
    update();
  }
  if(val >= 0x200 && val < 0x300)
  {
    switch(val)
    {
    case 0x200: displayMode = MONO; break;
    case 0x201: displayMode = ACTIVE; break;
    case 0x202: displayMode = LEFT_RIGHT; break;
    case 0x203: displayMode = INTERLEAVED; break;
    case 0x204: displayMode = SHARP; break;
    case 0x205: displayMode = WOBBLE; break;
    }
    reshape(windowWidth, windowHeight);
    glutPostRedisplay();
  }
  
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );

  // Parse command line arguments. 
  parseArguments( argc, argv );

  if(displayMode == ACTIVE)
  {
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO );
    canActive = true;  
  }
  else
  {
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );    
  }
  
  glutInitWindowSize( windowWidth, windowHeight );
  if(windowX >= 0)
    glutInitWindowPosition( windowX, windowY );
  glutCreateWindow( "Stereo Image Viewer" ); 


  // GLEW init for FBOs
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    //Problem: glewInit failed, something is seriously wrong. 
    cout << "GLEW Error: " <<  glewGetErrorString(err) << endl;
  }
  else
  {
    if (glewIsSupported("GL_VERSION_2_0"))
    {
      cout << "Have OpenGL 2" << endl;

      if (GL_EXT_framebuffer_object)
        cout << "Have GL_EXT_framebuffer_object" << endl;
      if (GLEW_ARB_vertex_shader)
        cout << "Have GLEW_ARB_vertex_shader" << endl;
      if (GLEW_ARB_fragment_shader)
        cout << "Have GLEW_ARB_fragment_shader" << endl;

      if(GL_EXT_framebuffer_object && GLEW_ARB_vertex_shader &&
          GLEW_ARB_fragment_shader)
      {
        canInterleave = true;
        cout << "Have extensions for interleaving!" << endl;
      }
    }
  }

  // Initialization. 
  init();
  
  // Now load these textures. 
  loadStereoImagesAsTextures( images );  

  if(flipOnLoad)
  {
    flipLeftRight();
    cout << "Left/right flipped" << endl;
  }

  // Set up menus
  int modemenuid = glutCreateMenu(menu);
  glutAddMenuEntry("Mono", 0x200); 
  if(canActive) 
    glutAddMenuEntry("Active", 0x201); 
  glutAddMenuEntry("Left/Right", 0x202); 
  if(canInterleave) 
  {
    glutAddMenuEntry("Interleaved", 0x203); 
    glutAddMenuEntry("Sharp", 0x204); 
  }
  glutAddMenuEntry("Wobble", 0x205); 
  
  
  int menuid = glutCreateMenu(menu);

  glutAddSubMenu("Modes", modemenuid);
  
  for(int i = 0; i < images.size(); i += 2)
  {
    std::string i1(&images[i  ].c_str()[images[i  ].rfind('/') + 1]);
    std::string i2(&images[i+1].c_str()[images[i+1].rfind('/') + 1]);
    
    std::string e = i1 + "/" + i2;
    
    glutAddMenuEntry(e.c_str(), 0x100 + i / 2); 
  }
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // 
  initScene(); 

  glutDisplayFunc       (display);  
  glutReshapeFunc       (reshape);
  glutIdleFunc          (idle);
  glutKeyboardFunc      (keyboard);
  glutMouseFunc         (mouseButton);
  glutMotionFunc        (mouseMotion);
  glutPassiveMotionFunc (mouseMotion); 

  // Run the loop. 
  glutMainLoop();
}


// GLSLShader Source

const GLchar *vshader_source="\n\
void main()\n\
{\n\
  gl_TexCoord[0]= gl_MultiTexCoord0;\n\
  gl_TexCoord[1]= gl_MultiTexCoord1;\n\
  gl_Position=ftransform();\n\
}";

const GLchar *fshader_source="\n\
uniform sampler2D left_eye,right_eye;\n\
\n\
void main()\n\
{\n\
  vec4 color;\n\
  \n\
  float x =  gl_TexCoord[1].t - floor(gl_TexCoord[1].t);\n\
  \n\
  if ( x < 0.5) color = texture2D(right_eye,gl_TexCoord[0].st).rgba;\n\
  else          color = texture2D(left_eye ,gl_TexCoord[0].st).rgba;\n\
\n\
\n\
  gl_FragColor = color;\n\
}";

const GLchar *sharp_fshader_source="\n\
uniform sampler2D left_eye,right_eye;\n\
\n\
void main()\n\
{\n\
  vec4 l,r,color;\n\
  l = texture2D(left_eye ,gl_TexCoord[0].st).rgba;\n\
  r = texture2D(right_eye,gl_TexCoord[0].st).rgba;\n\
  \n\
  float x =  gl_TexCoord[1].s - floor(gl_TexCoord[1].s);\n\
  \n\
  if ( x < 0.5) color = vec4(l.r, r.g, l.b, 0);\n\
  else          color = vec4(r.r, l.g, r.b, 0);\n\
\n\
\n\
  gl_FragColor = color;\n\
}";

