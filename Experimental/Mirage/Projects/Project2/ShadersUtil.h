
#ifndef __PROJECT2_SHADERS_UTIL_H__
#define __PROJECT2_SHADERS_UTIL_H__

#include "Gl/glew.h"
#include "GL/gl.h"

#include <string>

namespace Project2
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Utility class to parse, compile and load shaders for a ASCII file.  
  //
  /////////////////////////////////////////////////////////////////////////////

  class ShadersUtil 
  {
    public: 
      
      /////////////////////////////////////////////////////////////////////////
      //
      // Constructor. 
      //
      /////////////////////////////////////////////////////////////////////////

      ShadersUtil();


      /////////////////////////////////////////////////////////////////////////
      //
      // Destructor. 
      //
      /////////////////////////////////////////////////////////////////////////
      
      virtual ~ShadersUtil();


      /////////////////////////////////////////////////////////////////////////
      //
      // Set and load shaders. 
      //
      /////////////////////////////////////////////////////////////////////////

      GLint setAndLoadShaders( const std::string& vert, const std::string& frag );    
  };
}

#endif // __SHADERS_UTIL_H__