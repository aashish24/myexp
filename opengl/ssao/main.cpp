
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
GLhandleARB g_hBlurShader;
GLhandleARB g_vBlurShader;

// Shader variables we will bind to.
GLuint g_lightPos;
GLuint g_offset;
GLuint g_decal;
GLuint g_normals;
GLuint g_depth;
GLuint g_random;
GLuint g_lightColor;
GLuint g_aos;
GLuint g_colors;

GLuint g_ssaoOffset;
GLuint g_ssaoDecal;
GLuint g_ssaoNormals;
GLuint g_ssaoDepth;
GLuint g_ssaoRandom;

GLuint g_hBlur;
GLuint g_vBlur;

GLuint g_randomSampler;

// FBO data.
OpenGLFBO g_sceneFbo;
OpenGLFBO g_ssaoFbo;
OpenGLFBO g_hBlurFbo;
OpenGLFBO g_vBlurFbo;

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

  glGenTextures(1, &g_randomSampler);
  glBindTexture(GL_TEXTURE_2D, g_randomSampler);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
               0, GL_RGB, GL_UNSIGNED_BYTE, image);

   delete[] image;

  // Load shaders.
  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/setRenderTargetsVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/setRenderTargetsPs.glsl",
                      g_setRTShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/clearRenderTargetsVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/clearRenderTargetsPs.glsl",
                      g_clearRTShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/ssaoVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/ssaoPs.glsl",
                      g_ssaoShader))
   return false;


  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/hBlurVs.glsl",
                      "/home/aashish/tools/mywork/src.git/opengl/ssao/hBlurPs.glsl",
                      g_hBlurShader))
  return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/vBlurVs.glsl",
                       "/home/aashish/tools/mywork/src.git/opengl/ssao/vBlurPs.glsl",
                       g_vBlurShader))
    return false;

  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/ssao/renderingVs.glsl",
                       "/home/aashish/tools/mywork/src.git/opengl/ssao/renderingPs.glsl",
                        g_renderShader))
    return false;

  // Bind our shader variables.
  g_offset      = glGetUniformLocationARB(g_renderShader, "offset");
  g_lightPos    = glGetUniformLocationARB(g_renderShader, "lightPos");
  g_lightColor  = glGetUniformLocationARB(g_renderShader, "lightColor");
  g_aos         = glGetUniformLocationARB(g_renderShader, "aos");
  g_colors      = glGetUniformLocationARB(g_renderShader, "colors");

  g_ssaoOffset  = glGetUniformLocationARB(g_ssaoShader, "offset");
  g_ssaoNormals = glGetUniformLocationARB(g_ssaoShader, "normals");
  g_ssaoDepth   = glGetUniformLocationARB(g_ssaoShader, "depths");
  g_ssaoRandom  = glGetUniformLocationARB(g_ssaoShader, "randoms");

  g_hBlur       = glGetUniformLocationARB(g_hBlurShader, "blurh");
  g_vBlur       = glGetUniformLocationARB(g_vBlurShader, "blurv");

  // Create frame buffer objects.
  if(g_sceneFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  // Create frame buffer objects.
  if(g_ssaoFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  // Create frame buffer objects.
  if(g_hBlurFbo.Create(WIDTH, HEIGHT) == false)
    return false;

  if(g_vBlurFbo.Create(WIDTH, HEIGHT) == false)
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
   glDeleteObjectARB(g_hBlurShader);
   glDeleteObjectARB(g_vBlurShader);


   g_sceneFbo.Release();
   g_ssaoFbo.Release();
   g_hBlurFbo.Release();
   g_vBlurFbo.Release();

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
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_sceneFbo.GetFBO());

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
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_ssaoFbo.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glUseProgramObjectARB(g_ssaoShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFbo.GetColorDest1());
   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, g_randomSampler);
   glActiveTexture(GL_TEXTURE2_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFbo.GetColorDest2());
   glActiveTexture(GL_TEXTURE3_ARB);
   glBindTexture(GL_TEXTURE_2D, g_randomSampler);

   glUniform1iARB(g_ssaoNormals, 0);
   glUniform1iARB(g_ssaoRandom, 1);
   glUniform1iARB(g_ssaoDepth, 2);
   glUniform2fARB(g_ssaoOffset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);
   RenderScreenQuad();

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_hBlurFbo.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUseProgramObjectARB(g_hBlurShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_ssaoFbo.GetColorDest0());
   glUniform1iARB(g_hBlur, 0);
   RenderScreenQuad();


   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_vBlurFbo.GetFBO());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUseProgramObjectARB(g_vBlurShader);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_hBlurFbo.GetColorDest0());
   glUniform1iARB(g_vBlur, 0);
   RenderScreenQuad();


   glUseProgramObjectARB(g_renderShader);
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glUniform2fARB(g_offset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);
   glUniform3fARB(g_lightPos, 0.0f, 20.0f, 15.0f);
   glUniform4fARB(g_lightColor, 0.4f, 0.4f, 0.4f, 1.0f);
   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_vBlurFbo.GetColorDest0());
   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFbo.GetColorDest0());
   glUniform1iARB(g_aos, 0);
   glUniform1iARB(g_colors, 1);
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
