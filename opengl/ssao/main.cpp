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
#include<stdio.h>


// Scene Model.
ObjModel g_stageModel;
ObjModel g_boxModel;
ObjModel g_torusA;
ObjModel g_torusB;

// GLSlang objects.
GLhandleARB g_setRTShader;
GLhandleARB g_clearRTShader;
GLhandleARB g_directionalLightDeferredShader;

// Shader variables we will bind to.
GLuint g_glslLightPos;
GLuint g_glslOffset;
GLuint g_glslDecal;
GLuint g_glslNormals;
GLuint g_glslDepth;
GLuint g_glslLightColor;

// FBO data.
OpenGLFBO g_sceneFBO;

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

   // Load shaders.
   if(!CreateGLSLShader("../SetRenderTargetsVS.glsl", "../SetRenderTargetsPS.glsl", g_setRTShader))
      return false;

   if(!CreateGLSLShader("../ClearRenderTargetsVS.glsl", "../ClearRenderTargetsPS.glsl", g_clearRTShader))
      return false;

   if(!CreateGLSLShader("../DirectionalLightVS.glsl", "../DirectionalLightPS.glsl", g_directionalLightDeferredShader))
      return false;

   // Bind our shader variables.
   g_glslOffset = glGetUniformLocationARB(g_directionalLightDeferredShader, "offset");
   g_glslLightPos = glGetUniformLocationARB(g_directionalLightDeferredShader, "lightPos");
   g_glslLightColor = glGetUniformLocationARB(g_directionalLightDeferredShader, "lightColor");
   g_glslDecal = glGetUniformLocationARB(g_directionalLightDeferredShader, "colors");
   g_glslNormals = glGetUniformLocationARB(g_directionalLightDeferredShader, "normals");
   g_glslDepth = glGetUniformLocationARB(g_directionalLightDeferredShader, "depths");


   // Create frame buffer objects.
   if(g_sceneFBO.Create(WIDTH, HEIGHT) == false)
      return false;


   // Load the model from the file then its generated color data.
   if(g_stageModel.LoadOBJ("../Box.obj") == false)
      return false;

   if(g_boxModel.LoadOBJ("../Cube.obj") == false)
      return false;

   if(g_torusA.LoadOBJ("../TorusA.obj") == false)
      return false;

   if(g_torusB.LoadOBJ("../TorusB.obj") == false)
      return false;

   return true;
}


void ShutdownApp()
{
   glDeleteObjectARB(g_setRTShader);
   glDeleteObjectARB(g_clearRTShader);
   glDeleteObjectARB(g_directionalLightDeferredShader);

   g_sceneFBO.Release();

   g_stageModel.Release();
   g_boxModel.Release();
   g_torusA.Release();
   g_torusB.Release();
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

   glTranslatef(0, 0, -15);
   glRotatef(-g_yRot, 1.0f, 0.0f, 0.0f);
   glRotatef(-g_xRot, 0.0f, 1.0f, 0.0f);

   // Draw the objects.
   glColor3f(1.0f, 1.0f, 1.0f); DrawModel(g_stageModel);
   glColor3f(1.0f, 0.0f, 0.0f); DrawModel(g_boxModel);
   glColor3f(0.0f, 1.0f, 0.0f); DrawModel(g_torusA);
   glColor3f(0.0f, 0.0f, 1.0f); DrawModel(g_torusB);
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
   gluPerspective(45, (float)WIDTH/(float)HEIGHT, 1.0, 1000.0);

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
   RenderScenePass();

   // Draw to the back buffer using deferred shading.
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glActiveTexture(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFBO.GetColorDest0());

   glActiveTexture(GL_TEXTURE1_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFBO.GetColorDest1());

   glActiveTexture(GL_TEXTURE2_ARB);
   glBindTexture(GL_TEXTURE_2D, g_sceneFBO.GetColorDest2());

   glUseProgramObjectARB(g_directionalLightDeferredShader);
   glUniform1iARB(g_glslDecal, 0);
   glUniform1iARB(g_glslNormals, 1);
   glUniform1iARB(g_glslDepth, 2);
   glUniform3fARB(g_glslLightPos, 0.0f, 20.0f, 15.0f);
   glUniform4fARB(g_glslLightColor, 0.4f, 0.4f, 0.0f, 1.0f);
   glUniform2fARB(g_glslOffset, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);

   RenderScreenQuad();

   glActiveTexture(GL_TEXTURE0_ARB);

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
