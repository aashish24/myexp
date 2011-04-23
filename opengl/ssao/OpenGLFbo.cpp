#include"OpenGL.h"
#include"OpenGLFbo.h"

//-----------------------------------------------------------------------------
OpenGLFBO::OpenGLFBO()
{
   m_fbo = 0;
   m_color0Dest = 0;
   m_color1Dest = 0;
   m_color2Dest = 0;
   m_depthDest = 0;
}

//-----------------------------------------------------------------------------
OpenGLFBO::~OpenGLFBO()
{
   Release();
}

//-----------------------------------------------------------------------------
bool OpenGLFBO::Create(int width, int height)
{
  // Generate frame buffer.
  glGenFramebuffers(1, &m_fbo);

  // And associates render buffers.
  glGenRenderbuffers(1, &m_colorBuffer);
  glGenRenderbuffers(1, &m_normalBuffer);
  glGenRenderbuffers(1, &m_positionBuffer);

  // Bind frame buffer.
  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

  // Bind render buffers and specify storage.
  glBindRenderbuffer    (GL_RENDERBUFFER, m_colorBuffer);
  glRenderbufferStorage (GL_RENDERBUFFER, GL_RGB, width, height);

  glBindRenderbuffer    (GL_RENDERBUFFER, m_normalBuffer);
  glRenderbufferStorage (GL_RENDERBUFFER, GL_RGB16F, width, height);

  glBindRenderbuffer    (GL_RENDERBUFFER, m_positionBuffer);
  glRenderbufferStorage (GL_RENDERBUFFER, GL_RGB32F, width, height);

  // Attach render buffers to frame buffer.
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                            GL_RENDERBUFFER, m_colorBuffer);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
                            GL_RENDERBUFFER, m_normalBuffer);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
                            GL_RENDERBUFFER, m_colorBuffer);

  // Write to textures.
  glGenTextures   (1, &m_color0Dest);
  glBindTexture   (GL_TEXTURE_2D, m_color0Dest);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB8, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D, m_color0Dest, 0);

  glGenTextures   (1, &m_color1Dest);
  glBindTexture   (GL_TEXTURE_2D, m_color1Dest);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB16F, width, height,
                   0, GL_RGB, GL_FLOAT, NULL);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
                         GL_TEXTURE_2D, m_color1Dest, 0);

  glGenTextures   (1, &m_color2Dest);
  glBindTexture   (GL_TEXTURE_2D, m_color2Dest);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB32F, width, height,
                   0, GL_RGB, GL_FLOAT, NULL);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
                         GL_TEXTURE_2D, m_color2Dest, 0);

  GLenum destBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                          GL_COLOR_ATTACHMENT2 };

  glDrawBuffers(3, destBuffers);

  glGenTextures(1, &m_depthDest);
  glBindTexture(GL_TEXTURE_2D, m_depthDest);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
              0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                         GL_TEXTURE_2D, m_depthDest, 0);

  if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return false;

  return true;
}

//-----------------------------------------------------------------------------
void OpenGLFBO::Release()
{
   if(m_fbo)            glDeleteFramebuffersEXT(1, &m_fbo);
   if(m_colorBuffer)    glDeleteRenderbuffersEXT(1, &m_colorBuffer);
   if(m_normalBuffer)   glDeleteRenderbuffersEXT(1, &m_normalBuffer);
   if(m_positionBuffer) glDeleteRenderbuffersEXT(1, &m_positionBuffer);
   if(m_color0Dest)     glDeleteTextures(1, &m_color0Dest);
   if(m_color1Dest)     glDeleteTextures(1, &m_color1Dest);
   if(m_color2Dest)     glDeleteTextures(1, &m_color2Dest);
   if(m_depthDest)      glDeleteTextures(1, &m_depthDest);
}
