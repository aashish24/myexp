
#ifndef __PROJECT2_BUMPMAP_SHADER_H__
#define __PROJECT2_BUMPMAP_SHADER_H__

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER

#include "GL/glew.h"
#include "GL/gl.h"

#include "MsgCore/Array.h"

#include "Shader.h"

#include <string >

namespace Msg
{
  namespace MsgCore
  {
    class Node;
    class Geometry;
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
      
      std::string   id() const;

      virtual void  init();

      virtual bool  dirty() const;

      virtual void  dirty( bool flag );

      GLint         program() const;

      void          calculateTBN( Msg::MsgCore::Geometry* geom );

      virtual void  parseArguments( std::vector< std::string >& arguments );

      virtual void  activate( Msg::MsgCore::Node* node );

      virtual void  deActivate( Msg::MsgCore::Node* node );

      void          loadBumpMap( const std::string& filename );

      void          loadDecalMap( const std::string& filename );

      void          doCalculateTBN( Msg::MsgCore::Geometry* geom, Msg::MsgCore::Vec3Array* tangent,
                                  Msg::MsgCore::Vec3Array* binormal, Msg::MsgCore::Vec3Array* normal );


      /////////////////////////////////////////////////////////////////////////
      //
      // Compile and load shaders. 
      // 
      /////////////////////////////////////////////////////////////////////////

      void          setShader( const std::string& vert, const std::string& frag );


    protected: 

      bool          _dirty;
      
      GLint         _program;  
      GLint         _locT;
      GLint         _locB;
      GLint         _locN;
      GLint         _locNormalMap;
      GLint         _locDecalMap;

      GLuint         _normalMapTexIndex;
      GLuint         _decalMapTexIndex;
  };  
}

#endif // __PROJECT2_BUMPMAP_SHADER_H__
