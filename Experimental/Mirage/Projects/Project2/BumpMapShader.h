
#ifndef __PROJECT2_BUMPMAP_SHADER_H__
#define __PROJECT2_BUMPMAP_SHADER_H__

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER

#include "GL/glew.h"
#include "GL/gl.h"

#include "Shader.h"

#include <string >

namespace Msg
{
  namespace MsgCore
  {
    class Node;
  }
}

namespace Project2 
{  
  /////////////////////////////////////////////////////////////////////////////
  //
  // Class that implement Phong Shading. 
  // @Note: Requires vertex and fragment shaders. 
  //
  ///////////////////////////////////////////////////////////////////////////// 

  class BumpMapShader : public Shader
  {
    public: 

      /////////////////////////////////////////////////////////////////////////
      //
      // Constructor. 
      // 
      /////////////////////////////////////////////////////////////////////////

      BumpMapShader();


      /////////////////////////////////////////////////////////////////////////
      //
      // Destructor.  
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual ~BumpMapShader();


      /////////////////////////////////////////////////////////////////////////
      //
      // Calls setShader( const std::string& vert, const std::string& frag ).
      // @Note: Passing default shaders as agruments. 
      // 
      /////////////////////////////////////////////////////////////////////////

      void          apply( Msg::MsgCore::Node* node );


      /////////////////////////////////////////////////////////////////////////
      //
      // Compile and load shaders. 
      // 
      /////////////////////////////////////////////////////////////////////////

      void          setShader( const std::string& vert, const std::string& frag );


    protected: 
      
      GLint         _program;  
  };  
}

#endif // __PROJECT2_BUMPMAP_SHADER_H__
