#include"OpenGL.h"
#include"OpenGLFbo.h"

OpenGLFBO::OpenGLFBO()
{
   m_fbo = 0;
   m_color0Dest = 0;
   m_color1Dest = 0;
   m_color2Dest = 0;
   m_depthDest = 0;
}


OpenGLFBO::~OpenGLFBO()
{
   Release();
}


bool OpenGLFBO::Create(int width, int height)
{
   glGenFramebuffersEXT(1, &m_fbo);
   glGenRenderbuffersEXT(1, &colorBuffer);
   glGenRenderbuffersEXT(1, &normalBuffer);
   glGenRenderbuffersEXT(1, &positionBuffer);

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

   glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, colorBuffer);
   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB, width, height);
   glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                                GL_RENDERBUFFER_EXT, colorBuffer);

   glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, normalBuffer);
   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB, width, height);
   glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                                GL_RENDERBUFFER_EXT, normalBuffer);

   glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, positionBuffer);
   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB32F_ARB, width, height);
   glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT,
                                GL_RENDERBUFFER_EXT, colorBuffer);

   glGenTextures(1, &m_color0Dest);
   glBindTexture(GL_TEXTURE_2D, m_color0Dest);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
                0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                             GL_TEXTURE_2D, m_color0Dest, 0);

   glGenTextures(1, &m_color1Dest);
   glBindTexture(GL_TEXTURE_2D, m_color1Dest);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F_ARB, width, height,
                0, GL_RGB, GL_FLOAT, NULL);

   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                             GL_TEXTURE_2D, m_color1Dest, 0);

   glGenTextures(1, &m_color2Dest);
   glBindTexture(GL_TEXTURE_2D, m_color2Dest);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, width, height,
                0, GL_RGB, GL_FLOAT, NULL);

   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT,
                             GL_TEXTURE_2D, m_color2Dest, 0);

   GLenum destBuffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT,
                            GL_COLOR_ATTACHMENT2_EXT };

   glDrawBuffers(3, destBuffers);

   glGenTextures(1, &m_depthDest);
   glBindTexture(GL_TEXTURE_2D, m_depthDest);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
                0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
                             GL_TEXTURE_2D, m_depthDest, 0);

   if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
      return false;

   return true;
}


void OpenGLFBO::Release()
{
   if(m_fbo) glDeleteFramebuffersEXT(1, &m_fbo);
   if(colorBuffer) glDeleteRenderbuffersEXT(1, &colorBuffer);
   if(normalBuffer) glDeleteRenderbuffersEXT(1, &normalBuffer);
   if(positionBuffer) glDeleteRenderbuffersEXT(1, &positionBuffer);
   if(m_color0Dest) glDeleteTextures(1, &m_color0Dest);
   if(m_color1Dest) glDeleteTextures(1, &m_color1Dest);
   if(m_color2Dest) glDeleteTextures(1, &m_color2Dest);
   if(m_depthDest) glDeleteTextures(1, &m_depthDest);
}
