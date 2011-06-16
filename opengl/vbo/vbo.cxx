
// GL includes.
#include "OpenGL.h"

// Library includes.
#include"OpenGLSLHelper.h"

#include <iostream>

// GLSlang objects.
GLhandleARB gPhongShader;
GLuint oneBuffer;

GLfloat positions [] =
{
  -10.0, -10.0, -100.0, 1.0,
   10.0, -10.0, -100.0, 1.0,
   10.0, 10.0, -100.0, 1.0,
  -10.0, 10.0, -100.0, 1.0
};


// Intentionaly creating varying normals.
GLfloat normals [] =
{
  1.0, 1.0, 0.0, 1.0,
  1.0, 1.0, 0.0, 1.0,
  1.0, 1.0, 0.0, 1.0,
  1.0, 1.0, 0.0, 1.0
};


void Resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);

  gluPerspective(45, width/height, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}


bool InitializeApp()
{
   glClearColor(0, 0, 0, 1);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);

   // Load shaders and object.
   // Load shaders.
   if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/opengl/vbo/per_pixel_phong_shader_vs.glsl",
                        "/home/aashish/tools/mywork/src.git/opengl/vbo/per_pixel_phong_shader_ps.glsl", gPhongShader))
     {
      return false;
     }

   // glBindAttribLocation requires call before glLinkProgram. Since in our code this is not
   // entirely possible we are getting attribute location and using the locations to glVertexAttribPointer.
   GLuint positionsLoc = glGetAttribLocation(gPhongShader, "positions");
   GLuint normalsLoc   = glGetAttribLocation(gPhongShader, "normals");

   glGenBuffers(1, &oneBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, oneBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
   glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), normals);
   glVertexAttribPointer(positionsLoc, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);
   glEnableVertexAttribArray(positionsLoc);
   glVertexAttribPointer(normalsLoc, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(positions));
   glEnableVertexAttribArray(normalsLoc);

   // Swith back to normal operations.
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   return true;
}

// Render scene.
void RenderScene()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glUseProgram(gPhongShader);
  glBindBuffer(GL_ARRAY_BUFFER, oneBuffer);
  glDrawArrays(GL_QUADS, 0, 4);

  glPopMatrix();

  glutSwapBuffers();
  glutPostRedisplay();
}


// Main.
int main(int arg, char **argc)
{
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(0, 0);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInit(&arg, argc);

   glutCreateWindow("OpenGL VBO");
   glutDisplayFunc(RenderScene);
   glutReshapeFunc(Resize);


   if(InitializeApp() == true)
      glutMainLoop();
   else
      std::cerr << "Error in InitializeApp()!\n\n";

   return 1;
}
