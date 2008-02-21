
#ifndef __SHADERS_UTIL_H__
#define __SHADERS_UTIL_H__

#include "Gl/glew.h"
#include "GL/gl.h"

#include <string>

namespace Project
{
  class ShadersUtil 
  {
    public: 

      ShadersUtil();

      virtual ~ShadersUtil();

      GLint setShaders( const std::string& vert, const std::string& frag );    
  };
}

#endif // __SHADERS_UTIL_H__
