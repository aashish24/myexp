
#ifndef __MSG_CORE_I_UNIFORM_H__
#define __MSG_CORE_I_UNIFORM_H__

#include <string>

// Interface for GLSL uniform data type. 
namespace Msg
{
  namespace MsgCore
  {
    struct IUniform
    {
      virtual std::string name() const = 0;

      virtual void name( const std::string& name ) = 0;

      virtual void callGL() const = 0;


      protected: 
      
        virtual ~IUniform()
        {
        }
    };
  }
}

#endif // __MSG_CORE_I_UNIFORM_H__
