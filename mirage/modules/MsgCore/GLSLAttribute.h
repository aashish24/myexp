
#ifndef __MSG_CORE_GLSL_ATTRIBUTE_H__
#define __MSG_CORE_GLSL_ATTRIBUTE_H__

#include "MsgCore/StateAttribute.h"

#include "MsgCore/GLSLProgram.h"
#include "MsgCore/Uniform.h"
#include "MsgCore/GLSLShader.h"

#include <map>
#include <vector>

namespace Msg
{
  namespace MsgCore
  {
    ///////////////////////////////////////////////////////////////////////////
    //
    // GLSLShader Attribute that could be used as an attribute in any SteteSet. 
    //
    ///////////////////////////////////////////////////////////////////////////

    class GLSLAttribute : public StateAttribute
    {
      public: 

        GLSLAttribute();

        virtual void init();

        virtual void conextInit();

		    virtual void activate( Node* node );

        virtual void deActivate( Node* node );

        virtual void addShader( GLSLShader* shader );

        virtual void addUniform( Uniform* uniform );
      
      protected:

        virtual ~GLSLAttribute();

        void		     set();


      private:

        SmartPtr< GLSLProgram >                             _glslProgram;

        std::map< IShader::Type, SmartPtr< GLSLShader > >   _shaders;

        std::vector< SmartPtr< Uniform > >                  _uniforms;
    };
  }
}

#endif // __MSG_CORE_GLSL_ATTRIBUTE_H__
