/*
   OpenGL Header
   Game Graphics Programming
   Created by Allen Sherrod
*/


#ifndef _GL_HEADER_H_
#define _GL_HEADER_H_


#ifdef _WIN32
   // Windows.
   #include<gl/glee.h>
   #include<gl/glut.h>
   #pragma comment(lib, "glee.lib")
#else
#ifdef _MAC_OSX
   // Mac.
   #include<glut/glut.h>
   #include<stdlib.h>
#else
   // Linux.
   #include<GL/GLee.h>
   #include<GL/glut.h>
   #include<stdlib.h>
#endif
#endif

#endif
