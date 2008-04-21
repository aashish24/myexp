
#ifndef __PROJECT2_PHONG_SHADER_H__
#define __PROJECT2_PHONG_SHADER_H__

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

  class PhongShader : public Shader
  {
    public: 

      /////////////////////////////////////////////////////////////////////////
      //
      // Constructor. 
      // 
      /////////////////////////////////////////////////////////////////////////

      PhongShader();

      std::string   id() const;

      virtual void  init();

      virtual bool  dirty() const;

      virtual void  dirty( bool flag );

      GLint         program() const;


      /////////////////////////////////////////////////////////////////////////
      //
      // 
      // 
      /////////////////////////////////////////////////////////////////////////

      virtual void  parseArguments( std::vector< std::string >& arguments );

     
      /////////////////////////////////////////////////////////////////////////
      //
      // 
      // 
      /////////////////////////////////////////////////////////////////////////

      virtual void  activate( Msg::MsgCore::Node* node );


      virtual void  deActivate( Msg::MsgCore::Node* node );


      /////////////////////////////////////////////////////////////////////////
      //
      // Compile and load shaders. 
      // 
      /////////////////////////////////////////////////////////////////////////

      void          setShader( const std::string& vert, const std::string& frag );


    protected: 

      /////////////////////////////////////////////////////////////////////////
      //
      // Destructor.  
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual ~PhongShader();


    protected: 

      bool          _dirty;
      
      GLint         _program;  
  };  
}

#endif // __PROJECT2_PHONG_SHADER_H__
