#include"GL/gl.h"
#include "GL/glut.h"

#include <iostream>

void Resize(int width, int height)
{
}

bool InitializeApp()
{
   glClearColor(0, 0, 0, 1);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);

   // Load shaders and object.

   return true;
}

void RenderScene()
{
   glutSwapBuffers();
   glutPostRedisplay();
}

int main(int arg, char **argc)
{
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInit(&arg, argc);

   glutCreateWindow("OpenGL VBO");

   glutDisplayFunc(RenderScene);

   if(InitializeApp() == true)
      glutMainLoop();
   else
      std::cerr << "Error in InitializeApp()!\n\n";

   return 1;
}
