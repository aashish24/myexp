
#ifndef __MSG_CORE_GLSL_ATTRIBUTE_H__
#define __MSG_CORE_GLSL_ATTRIBUTE_H__

#include "Export.h"

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

    class MSG_EXPORT GLSLAttribute : public StateAttribute
    {
      public: 

        typedef std::map< IShader::Type, SmartPtr< GLSLShader > > Shaders;
        typedef Shaders::iterator                                 Iterator;
        typedef Shaders::const_iterator                           ConstIterator;

        GLSLAttribute();

        virtual std::string id() const;

        virtual void init();

        virtual void contextInit();

		    virtual void activate( Node* node );

        virtual void deActivate( Node* node );

        virtual void addShader( GLSLShader* shader );

        virtual void addUniform( Uniform* uniform );

      
      protected:

        virtual ~GLSLAttribute();

        void		     set();


      private:

        SmartPtr< GLSLProgram >                             _glslProgram;

        Shaders                                             _shaders;

        std::vector< SmartPtr< Uniform > >                  _uniforms;
    };
  }
}

#endif // __MSG_CORE_GLSL_ATTRIBUTE_H__
