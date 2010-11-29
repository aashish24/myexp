
#ifndef __MSG_CORE_GLSL_PROGRAM_H__
#define __MSG_CORE_GLSL_PROGRAM_H__

#include "Export.h"

#include "MsgCore/Object.h"

namespace Msg
{
  namespace MsgCore
  {
    class GLSLShader;

    class MSG_EXPORT GLSLProgram : public MsgCore::Object
    {
      public: 
        
        // Constructor. 
        GLSLProgram();           
        
        // Initialize context specific data. 
        void      contextInit();

        // Return OpenGL object. 
        int       glObject() const;

        // Attach vertex or fragment shader. 
        void      attach( GLSLShader* shader ); 

        // Link shaders. 
        void      link(); 

      
      protected:

        // Destructor. 
        ~GLSLProgram();


      private: 

        int   _glObject;
    };
  }
}

#endif // __MSG_CORE_GLSL_PROGRAM_H__
