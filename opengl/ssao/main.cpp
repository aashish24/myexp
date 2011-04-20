/*
   Deferred Shading - OpenGL
   Game Graphics Programming
   Created by Allen Sherrod

   NOTE: This demo creates an FBO that sets the color to output 0,
         normals to ouptut 1, and depth values to output 2.  Each
         output target has the same number of bits (32).  The depth
         target uses a single 32-bit component to keep precision
         and the shaders use that depth value to re-build the world
         position.
*/


#include"OpenGL.h"
#include"objLoader.h"
#include"OpenGLSLHelper.h"
#include"OpenGLFbo.h"
#include "TGA.h"

#include<stdio.h>


// Scene Model.
ObjModel g_stageModel;
ObjModel g_boxModel;
ObjModel g_torusA;
ObjModel g_torusB;
ObjModel g_model;

// GLSlang objects.
GLhandleARB g_setRTShader;
GLhandleARB g_clearRTShader;
GLhandleARB g_renderShader;
GLhandleARB g_ssaoShader;
GLhandleARB g_setHBlurShader;
GLhandleARB g_setVBlurShader;


// Shader variables we will bind to.
GLuint g_glslLightPos;
GLuint g_glslOffset;
GLuint g_glslDecal;
GLuint g_glslNormals;
GLuint g_glslDepth;
GLuint g_glslRandom;
GLuint g_glslLightColor;
GLuint g_glslAOS;
GLuint g_glslColors;

GLuint g_glslSsaoOffset;
GLuint g_glslSsaoDecal;
GLuint g_glslSsaoNormals;
GLuint g_glslSsaoDepth;
GLuint g_glslSsaoRandom;

GLuint g_glslBlurh;
GLuint g_glslBlurv;


GLuint g_glslRandomTexture;

// FBO data.
OpenGLFBO g_sceneFBO;
OpenGLFBO g_ssaoFBO;
OpenGLFBO g_blurHFBO;
OpenGLFBO g_blurVFBO;

// Scene rotations.
float g_xRot = 0.0f;
float g_yRot = 340.0f;

#define WIDTH  800
#define HEIGHT 600


void Resize(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);

   gluPerspective(45, width/height, 1.0, 1000.0);
   glMatrixMode(GL_MODELVIEW);
}


void KeyDown(unsigned char key, int x, int y)
{
   switch(key)
      {
         case 27:
            exit(0);
            break;
      }
}


void KeyDownSpecial(int key, int x, int y)
{
   switch(key)
      {
         case GLUT_KEY_LEFT:
            g_xRot -= 0.8f;
            break;

         case GLUT_KEY_RIGHT:
            g_xRot += 0.8f;
            break;

         case GLUT_KEY_DOWN:
            g_yRot -= 0.6f;
            break;

         case GLUT_KEY_UP:
            g_yRot += 0.6f;
            break;
      }

   if(g_xRot < 0)
      g_xRot = 359;
   else if(g_xRot >= 360)
      g_xRot = 0;

   if(g_yRot < 0)
      g_yRot = 359;
   else if(g_yRot >= 360)
      g_yRot = 0;
}


bool InitializeApp()
{
  glClearColor(0, 0, 0, 1);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  // Load texture.
  int width = 0, height = 0, comp = 0;
  unsigned char *image;
  image = LoadTGA("/home/aashish/tools/mywork/src.git/opengl/ssao/randoms.tga", width, height, comp);

  glGenTextures(1, &g_glslRandomTexture);
  glBindTexture(GL_TEXTURE_2D, g_glslRandomTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
               0, GL_RGB, GL_UNSIGNED_BYTE, image);

   delete[] image;

  // Load shaders.
  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/SetRenderTargetsVS.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/SetRenderTargetsPS.glsl",
                      g_setRTShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/ClearRenderTargetsVS.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/ClearRenderTargetsPS.glsl",
                      g_clearRTShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/SsaoVS.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/SsaoPS.glsl",
                      g_ssaoShader))
   return false;


  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/SetHBlurVS.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/SetHBlurPS.glsl",
                      g_setHBlurShader))
  return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/SetVBlurVS.glsl",
                       "/home/aashish/tools/mywork/src.git/opengl/ssao/SetVBlurPS.glsl",
                       g_setVBlurShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/DirectionalLightVS.glsl",
                       "/home/aashish/tools/mywork/src.git/opengl/ssao/DirectionalLightPS.glsl",
                        g_renderShader))
    return false;

  // Bind our shader variables.
  g_glslOffset = glGetUniformLocationARB(g_renderShader, "offset");
  g_glslLightPos = glGetUniformLocationARB(g_renderShader, "lightPos");
  g_glslLightColor = glGetUniformLocationARB(g_renderShader, "lightColor");
  g_glslAOS = glGetUniformLocationARB(g_renderShader, "aos");
  g_glslColors = glGetUniformLocationARB(g_renderShader, "colors");

  g_glslSsaoOffset = glGetUniformLocationARB(g_ssaoShader, "offset");
  g_glslSsaoNormals = glGetUniformLocationARB(g_ssaoShader, "normals");
  g_glslSsaoDepth = glGetUniformLocationARB(g_ssaoShader, "depths");
  g_glslSsaoRandom = glGetUniformLocationARB(g_ssaoShader, "randoms");

  g_glslBlurh = glGetUniformLocationARB(g_setHBlurShader, "blurh");

  g_glslBlurv = glGetUniformLocationARB(g_setVBlurShader, "blurv");

  // Create frame buffer objects.
  if(g_sceneFBO.Create(WIDTH, HEIGHT) == false)
    return false;

  // Create frame buffer objects.
  if(g_ssaoFBO.Create(WIDTH, HEIGHT) == false)
    return false;

  // Create frame buffer objects.
  if(g_blurHFBO.Create(WIDTH, HEIGHT) == false)
    return false;

  if(g_blurVFBO.Create(WIDTH, HEIGHT) == false)
    return false;

    if(g_model.LoadOBJ("/home/aashish/tools/mywork/src.git/opengl/ssao/dragon.obj") == false)
      return false;

//  // Load the model from the file then its generated color data.
//  if(g_stageModel.LoadOBJ("/home/aashish/tools/mywork/src.git/opengl/ssao/Box.obj") == false)
//    return false;

//  if(g_boxModel.LoadOBJ("/home/aashish/tools/mywork/src.git/opengl/ssao/Cube.obj") == false)
//    return false;

//  if(g_torusA.LoadOBJ("/home/aashish/tools/mywork/src.git/opengl/ssao/TorusA.obj") == false)
//    return false;

//  if(g_torusB.LoadOBJ("/home/aashish/tools/mywork/src.git/opengl/ssao/TorusB.obj") == false)
//    return false;

  return true;
}


void ShutdownApp()
{
   glDeleteObjectARB(g_setRTShader);
   glDeleteObjectARB(g_clearRTShader);
   glDeleteObjectARB(g_renderShader);
   glDeleteObjectARB(g_ssaoShader);
   glDeleteObjectARB(g_setHBlurShader);
   glDeleteObjectARB(g_setVBlurShader);


   g_sceneFBO.Release();
   g_ssaoFBO.Release();
   g_blurHFBO.Release();
   g_blurVFBO.Release();

//   g_stageModel.Release();
//   g_boxModel.Release();
//   g_torusA.Release();
//   g_torusB.Release();
   g_model.Release();
}


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


void RenderScenePass()
{
   // We can't simply call this to clear so we take another approach.
   // This is done before this function is called.
   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glTranslatef(0, 0, -2);
   glRotatef(-g_yRot, 1.0f, 0.0f, 0.0f);
   glRotatef(-g_xRot, 0.0f, 1.0f, 0.0f);

   // Draw the objects.
//   glColor3f(1.0f, 1.0f, 1.0f); DrawModel(g_stageModel);
//   glColor3f(1.0f, 0.0f, 0.0f); DrawModel(g_boxModel);
//   glColor3f(0.0f, 1.0f, 0.0f); DrawModel(g_torusA);
//   glColor3f(0.0f, 0.0f, 1.0f); DrawModel(g_torusB);

   glColor3f(1.0f, 1.0f, 1.0f); DrawModel(g_model);
}


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


void RenderScene()
{
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_sceneFBO.GetFBO());

   // Clear each rendering target first before drawing the scene.
   glUseProgramObjectARB(g_clearRTShader);
   RenderScreenQuad();

   // Now draw scene once destinations have been cleared.
   glUseProgramObjectARB(g_setRTShader);
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
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_ssaoFBO.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glUseProgramObjectARB(g_ssaoShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFBO.GetColorDest1());
   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, g_glslRandomTexture);
   glActiveTexture(GL_TEXTURE2_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFBO.GetColorDest2());
   glActiveTexture(GL_TEXTURE3_ARB);
   glBindTexture(GL_TEXTURE_2D, g_glslRandomTexture);

   glUniform1iARB(g_glslSsaoNormals, 0);
   glUniform1iARB(g_glslSsaoRandom, 1);
   glUniform1iARB(g_glslSsaoDepth, 2);
   glUniform2fARB(g_glslSsaoOffset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);
   RenderScreenQuad();

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_blurHFBO.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUseProgramObjectARB(g_setHBlurShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_ssaoFBO.GetColorDest0());
   glUniform1iARB(g_glslBlurh, 0);
   RenderScreenQuad();


   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_blurVFBO.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUseProgramObjectARB(g_setVBlurShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_blurHFBO.GetColorDest0());
   glUniform1iARB(g_glslBlurv, 0);
   RenderScreenQuad();


   glUseProgramObjectARB(g_renderShader);
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUniform2fARB(g_glslOffset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);
   glUniform3fARB(g_glslLightPos, 0.0f, 20.0f, 15.0f);
   glUniform4fARB(g_glslLightColor, 0.4f, 0.4f, 0.4f, 1.0f);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_blurVFBO.GetColorDest0());
   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFBO.GetColorDest0());
   glUniform1iARB(g_glslAOS, 0);
   glUniform1iARB(g_glslColors, 1);
   RenderScreenQuad();

   glutSwapBuffers();
   glutPostRedisplay();
}


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
