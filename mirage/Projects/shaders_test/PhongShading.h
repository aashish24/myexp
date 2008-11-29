
#ifndef __PHONG_SHADING_H__
#define __PHONG_SHADING_H__

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER

#include "GL/glew.h"
#include "GL/gl.h"

#include <string >

namespace Project 
{
  class PhongShading 
  {
    public: 

      PhongShading();

      virtual ~PhongShading();

      void          setShaders( const std::string& vert, const std::string& frag );

    protected: 
      
      GLint         _program;  
  };  
}

#endif // __PHONG_SHADING_H__
