
#ifndef __MSG_CORE_GLSL_PROGRAM_H__
#define __MSG_CORE_GLSL_PROGRAM_H__

#include "Export.h"

#include "MirageCore/Object.h"

namespace Mirage
{
  namespace MirageCore
  {
    class GLSLShader;

    class MSG_EXPORT GLSLProgram : public MirageCore::Object
    {
      public: 
        
        GLSLProgram();         

        void  contextInit();

        int   glObject() const;

        void  attach( GLSLShader* shader ); 

        void  link(); 

      
      protected:

        ~GLSLProgram();


      private: 

        int   _glObject;
    };
  }
}

#endif // __MSG_CORE_GLSL_PROGRAM_H__
