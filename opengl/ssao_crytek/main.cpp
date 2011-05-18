
#include"OpenGL.h"
#include"objLoader.h"
#include"OpenGLSLHelper.h"
#include"OpenGLFbo.h"
#include "TGA.h"

#include<stdio.h>

// Scene Model.
ObjModel _gModel;

// GLSlang objects.
GLhandleARB _gSetRenderTargetShader;
GLhandleARB _gClearRenderTargetShader;
GLhandleARB _gRenderShader;
GLhandleARB _gSsaoShader;
GLhandleARB _gHorizontalBlurShader;
GLhandleARB _gVerticalBlurShader;

// Shader variables we will bind to.
GLuint _gLightPos;
GLuint _gOffset;
GLuint _gDecal;
GLuint _gNormals;
GLuint _gDepths;
GLuint _gRandom;
GLuint _gLightColor;
GLuint _gAmbientOcclusion;
GLuint _gSceneColors;
GLuint _gSceneDepths;
GLuint _gSceneNormals;

GLuint _gSsaoOffset;
GLuint _gSsaoDecal;
GLuint _gSsaoNormals;
GLuint _gSsaoDepths;
GLuint _gSsaoRandoms;

GLuint _gHorizontalBlurSceneSampler;
GLuint _gHorizontalBlurSceneSamplerDepth;
GLuint _gHorizontalBlurSceneSamplerNormal;

GLuint _gVerticalBlurSceneSampler;
GLuint _gVerticalBlurSceneDepthSampler;
GLuint _gVerticalBlurSceneNormalSampler;

GLuint _gRandomSampler;

// FBO data.
OpenGLFBO _gSceneFbo;
OpenGLFBO _gSsaoFbo;
OpenGLFBO _gHorizontalBlurFbo;
OpenGLFBO _gVerticalBlurFbo;

// Scene rotations.
float _gXRot = 0.0f;
float _gYRot = 340.0f;

#define WIDTH  800
#define HEIGHT 600

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
void Resize(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);

   gluPerspective(45, width/height, 1.0, 1000.0);
   glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
void KeyDown(unsigned char key, int x, int y)
{
   switch(key)
      {
         case 27:
            exit(0);
            break;
      }
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
void KeyDownSpecial(int key, int x, int y)
{
   switch(key)
      {
         case GLUT_KEY_LEFT:
            _gXRot -= 0.8f;
            break;

         case GLUT_KEY_RIGHT:
            _gXRot += 0.8f;
            break;

         case GLUT_KEY_DOWN:
            _gYRot -= 0.6f;
            break;

         case GLUT_KEY_UP:
            _gYRot += 0.6f;
            break;
      }

   if(_gXRot < 0)
      _gXRot = 359;
   else if(_gXRot >= 360)
      _gXRot = 0;

   if(_gYRot < 0)
      _gYRot = 359;
   else if(_gYRot >= 360)
      _gYRot = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
bool InitializeApp()
{
  glClearColor(0, 0, 0, 1);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  // Load texture.
  int width = 0, height = 0, comp = 0;
  unsigned char *image;
  image = LoadTGA("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/noise.tga", width, height, comp);

  glGenTextures(1, &_gRandomSampler);
  glBindTexture(GL_TEXTURE_2D, _gRandomSampler);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
               0, GL_RGB, GL_UNSIGNED_BYTE, image);

   delete[] image;

  // Load shaders.
  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/setRenderTargetsVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/setRenderTargetsPs.glsl",
                      _gSetRenderTargetShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/clearRenderTargetsVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/clearRenderTargetsPs.glsl",
                      _gClearRenderTargetShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/ssaoVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/ssaoPs.glsl",
                      _gSsaoShader))
   return false;


  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/hBlurVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/hBlurPs.glsl",
                      _gHorizontalBlurShader))
  return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/vBlurVs.glsl",
                       "/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/vBlurPs.glsl",
                       _gVerticalBlurShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/renderingVs.glsl",
                       "/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/renderingPs.glsl",
                        _gRenderShader))
    return false;

  // Bind our shader variables.
  _gOffset            = glGetUniformLocationARB(_gRenderShader, "offset");
  _gLightPos          = glGetUniformLocationARB(_gRenderShader, "lightPos");
  _gLightColor        = glGetUniformLocationARB(_gRenderShader, "lightColor");
  _gAmbientOcclusion  = glGetUniformLocationARB(_gRenderShader, "aos");
  _gSceneColors       = glGetUniformLocationARB(_gRenderShader, "colors");
  _gSceneDepths       = glGetUniformLocationARB(_gRenderShader, "depths");
  _gSceneNormals      = glGetUniformLocationARB(_gRenderShader, "normals");

  _gSsaoOffset        = glGetUniformLocationARB(_gSsaoShader, "offset");
  _gSsaoNormals       = glGetUniformLocationARB(_gSsaoShader, "normals");
  _gSsaoDepths        = glGetUniformLocationARB(_gSsaoShader, "depths");
  _gSsaoRandoms       = glGetUniformLocationARB(_gSsaoShader, "randoms");

  _gHorizontalBlurSceneSampler       = glGetUniformLocationARB(_gHorizontalBlurShader, "scene");
  _gHorizontalBlurSceneSamplerDepth  = glGetUniformLocationARB(_gHorizontalBlurShader, "depths");
  _gHorizontalBlurSceneSamplerNormal = glGetUniformLocationARB(_gHorizontalBlurShader, "normals");

  _gVerticalBlurSceneSampler       = glGetUniformLocationARB(_gVerticalBlurShader, "scene");
  _gVerticalBlurSceneDepthSampler  = glGetUniformLocationARB(_gVerticalBlurShader, "depths");
  _gVerticalBlurSceneNormalSampler = glGetUniformLocationARB(_gVerticalBlurShader, "normals");

  // Create frame buffer objects.
  if(_gSceneFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  // Create frame buffer objects.
  if(_gSsaoFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  // Create frame buffer objects.
  if(_gHorizontalBlurFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  if(_gVerticalBlurFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  if(_gModel.LoadOBJ("/home/aashish/tools/mywork/src.git/opengl/ssao_crytek/sponza.obj") == false)
    return false;

  return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
void ShutdownApp()
{
   glDeleteObjectARB(_gSetRenderTargetShader);
   glDeleteObjectARB(_gClearRenderTargetShader);
   glDeleteObjectARB(_gRenderShader);
   glDeleteObjectARB(_gSsaoShader);
   glDeleteObjectARB(_gHorizontalBlurShader);
   glDeleteObjectARB(_gVerticalBlurShader);

   _gSceneFbo.Release();
   _gSsaoFbo.Release();
   _gHorizontalBlurFbo.Release();
   _gVerticalBlurFbo.Release();

   _gModel.Release();
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
void DrawModel(ObjModel &model)
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, model.GetVertices());

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, model.GetNormals());

  glDrawArrays(GL_TRIANGLES, 0, model.GetTotalVerts());

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////
void RenderScenePass()
{
   // We can't simply call this to clear so we take another approach.
   // This is done before this function is called.
   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glTranslatef(0, 0, -2.5);
   glRotatef(-_gYRot, 1.0f, 0.0f, 0.0f);
   glRotatef(-_gXRot, 0.0f, 1.0f, 0.0f);


   glColor3f(1.0f, 1.0f, 1.0f); DrawModel(_gModel);
}

///////////////////////////////////////////////////////////////////////////////
//
// Render quad for deferred shading.
//
///////////////////////////////////////////////////////////////////////////////
void RenderScreenQuad()
{
   float fullScreenVerts[]  = { 0.0f, 0.0f, 0.0f, WIDTH, 0.0f, 0.0f,
                                WIDTH, HEIGHT, 0.0f, WIDTH, HEIGHT, 0.0f,
                                0.0f, HEIGHT, 0.0f, 0.0f, 0.0f, 0.0f };

   float fullScreenTexC[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                              1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f };

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   gluOrtho2D(0, WIDTH, 0, HEIGHT);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, fullScreenVerts);

   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glTexCoordPointer(2, GL_FLOAT, 0, fullScreenTexC);

   glDrawArrays(GL_TRIANGLES, 0, 6);

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();

   glViewport(0, 0, WIDTH, HEIGHT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45, (float)WIDTH/(float)HEIGHT, 1.0, 10000.0);

   glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////////////////////////////////////
//
// Render scene.
//
///////////////////////////////////////////////////////////////////////////////
void RenderScene()
{
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _gSceneFbo.GetFBO());

   // Clear each rendering target first before drawing the scene.
   glUseProgram(_gClearRenderTargetShader);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   RenderScreenQuad();

   // Now draw scene once destinations have been cleared.
   glUseProgram(_gSetRenderTargetShader);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   RenderScenePass();

   // For BLUR the code need to do the following.
   // Use same or different FBO.
   // Our Display shader will become SSAO shader.
   // RenderSceneQuad().. using mostly the code below.
   // But using a HBLUR render target shader.
   // Now Again do RenderSceneQuad() this time with VBLUR shader.
   // Now draw the final image.

   // Draw to the back buffer using deferred shading.
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _gSsaoFbo.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glUseProgram(_gSsaoShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest1());
   glUniform1i(_gSsaoNormals, 0);

   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, _gRandomSampler);
   glUniform1i(_gSsaoRandoms, 1);

   glActiveTexture(GL_TEXTURE2_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest2());
   glUniform1i(_gSsaoDepths, 2);

   glActiveTexture(GL_TEXTURE3_ARB);
   glBindTexture(GL_TEXTURE_2D, _gRandomSampler);
   glUniform2fARB(_gSsaoOffset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);

   RenderScreenQuad();

   // Horizontal blur.
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _gHorizontalBlurFbo.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUseProgram(_gHorizontalBlurShader);

   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSsaoFbo.GetColorDest0());

   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest1());

   glActiveTexture(GL_TEXTURE2_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest2());

   glUniform1i(_gHorizontalBlurSceneSampler, 0);
   glUniform1i(_gHorizontalBlurSceneSamplerNormal, 1);
   glUniform1i(_gHorizontalBlurSceneSamplerDepth, 2);

   RenderScreenQuad();

   // Vertical blur.
   glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, _gVerticalBlurFbo.GetFBO() );
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUseProgram( _gVerticalBlurShader );

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, _gHorizontalBlurFbo.GetColorDest0());
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest1());
   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest2());

   glUniform1i( _gVerticalBlurSceneSampler, 0 );
   glUniform1i( _gVerticalBlurSceneNormalSampler, 1 );
   glUniform1i( _gVerticalBlurSceneDepthSampler, 2 );

   RenderScreenQuad();

   // Final stage.
   glUseProgram( _gRenderShader );
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUniform2fARB(_gOffset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);
   glUniform3fARB(_gLightPos, 0.0f, 20.0f, 15.0f);
   glUniform4fARB(_gLightColor, 0.4f, 0.4f, 0.4f, 1.0f);

   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, _gVerticalBlurFbo.GetColorDest0());
   glUniform1i(_gAmbientOcclusion, 0);

   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest0());
   glUniform1i(_gSceneColors, 1);

   glActiveTexture(GL_TEXTURE2_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest1());
   glUniform1i(_gSceneNormals, 2);

   glActiveTexture(GL_TEXTURE3_ARB);
   glBindTexture(GL_TEXTURE_2D, _gSceneFbo.GetColorDest2());
   glUniform1i(_gSceneDepths, 2);

   RenderScreenQuad();

   glutSwapBuffers();
   glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//
// Main.
//
///////////////////////////////////////////////////////////////////////////////
int main(int arg, char **argc)
{
   glutInitWindowSize(WIDTH, HEIGHT);
   glutInitWindowPosition(100, 100);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInit(&arg, argc);

   glutCreateWindow("OpenGL Deferred Shading");

   glutDisplayFunc(RenderScene);
   glutReshapeFunc(Resize);
   glutKeyboardFunc(KeyDown);
   glutSpecialFunc(KeyDownSpecial);

   if(InitializeApp() == true)
      glutMainLoop();
   else
      printf("Error in InitializeApp()!\n\n");

   ShutdownApp();

   return 1;
}
