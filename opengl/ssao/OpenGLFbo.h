

#ifndef _GL_FBO_H_
#define _GL_FBO_H_


class OpenGLFBO
{
   public:
      OpenGLFBO();
      ~OpenGLFBO();

      bool Create(int width, int height);
      void Release();

      GLuint GetFBO() { return m_fbo; }
      GLuint GetColorDest0() { return m_color0Dest; }
      GLuint GetColorDest1() { return m_color1Dest; }
      GLuint GetColorDest2() { return m_color2Dest; }
      GLuint GetDepthDest() { return m_depthDest; }

   private:
      GLuint m_fbo;
      GLuint m_color0Dest;
      GLuint m_color1Dest;
      GLuint m_color2Dest;
      GLuint m_depthDest;

      GLuint colorBuffer;
      GLuint normalBuffer;
      GLuint positionBuffer;
};

#endif
