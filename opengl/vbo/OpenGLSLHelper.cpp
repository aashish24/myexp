/*
   OpenGL GLSL Header
   Game Graphics Programming
   Created by Allen Sherrod
*/


#include"OpenGL.h"
#include"OpenGLSLHelper.h"
#include<stdio.h>


char* LoadText(char *file)
{
   FILE *fp = fopen(file, "r");

   if(fp == NULL)
      return NULL;

   fseek(fp, 0, SEEK_END);
   int size = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   if(size == 0)
      return NULL;

   char *source = new char[size + 1];

   fread(source, 1, size, fp);

   // Trim exceess characters that might exist.  Some text
   // editors do not save text after the last character in
   // the text file, which can force errors.  Replace final }
   // with a string delim.
   while(size-- >= 1)
      {
         if(source[size - 1] == '}')
            {
               source[size] = '\0';
               break;
            }
      }

   return source;
}


bool LoadShader(char *file, GLenum type, GLhandleARB context)
{
   // GLSL shader.
   GLhandleARB shader;

   // Load shader's source text.
   char *code = LoadText(file);

   if(code == NULL)
      return false;

   // Create the shader from a text file.
   shader = glCreateShaderObjectARB(type);
   glShaderSourceARB(shader, 1, (const char**)&code, NULL);
   glCompileShaderARB(shader);

   GLint result;
   char error[1024];

   // Returns the results of the shader compilation.
   glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB,
                             &result);
   delete[] code;

   // Display shader errors if any.
   if(!result)
      {
       // Get the error message and display it.
       glGetInfoLogARB(shader, sizeof(error), NULL, error);
       printf("Error in %s...\n%s\n", file, error);
       return false;
      }

   // Attach to the effect's context.
   glAttachObjectARB(context, shader);

   glDeleteObjectARB(shader);

   return true;
}


bool CreateGLSLShader(char *vsFile, char *psFile, GLhandleARB &shader)
{
   bool ret = false;

   // Create the shader.
   shader = glCreateProgramObjectARB();

   // Load the vertex shader.
   if(LoadShader(vsFile, GL_VERTEX_SHADER_ARB, shader) == false)
      return false;

   // Load the pixel shader.
   if(LoadShader(psFile, GL_FRAGMENT_SHADER_ARB, shader) == false)
      return false;

   // Link together the vertex and pixel shaders.
   glLinkProgramARB(shader);

   GLint link = 0;
   char error[1024];

   glGetObjectParameterivARB(shader, GL_OBJECT_LINK_STATUS_ARB, &link);

   if(!link)
      {
         // Get the error message and display it.
         glGetInfoLogARB(shader, sizeof(error), NULL, error);
         printf("Error linking shader...\n%s\n", error);
         return false;
      }

   return true;
}
