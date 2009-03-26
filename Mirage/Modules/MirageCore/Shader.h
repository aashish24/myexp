
#ifndef __MSG_CORE_SHADER_H__
#define __MSG_CORE_SHADER_H__

#include "Export.h"

#include "Core/IShader.h"
#include "Core/Object.h"


namespace Mirage
{
  namespace Core
  {
    class MSG_EXPORT Shader : public Core::Object, public Core::IShader
    {
      public: 

        ///////////////////////////////////////////////////////////////////////
        //
        // Constructor.
        //
        ///////////////////////////////////////////////////////////////////////

        Shader( Type type ); 


        ///////////////////////////////////////////////////////////////////////
        //
        // Initialize context specific data. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void  contextInit();

        
        ///////////////////////////////////////////////////////////////////////
        //
        // Return OpenGL object associate with this shader. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual int   glObject() const;


        ///////////////////////////////////////////////////////////////////////
        //
        // Set shader source via stream of strings. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void  source( const std::string& source );


        ///////////////////////////////////////////////////////////////////////
        //
        // Set shader source as file. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void  sourceAsFile( const std::string& fileName );

        
        ///////////////////////////////////////////////////////////////////////
        //
        // Compile the shader. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void  compile(); 
        
      
      protected: 

        virtual ~Shader();


      protected: 

        Type          _type;

        int           _glObject;

        std::string   _ss;
    };
  }
}

#endif // __MSG_CORE_SHADER_H__
