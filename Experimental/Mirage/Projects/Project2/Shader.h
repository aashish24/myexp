
#ifndef __PROJECT2_SHADER_H__
#define __PROJECT2_SHADER_H__

#include "MsgCore/StateAttribute.h"

#include <vector>

namespace Msg
{
  namespace MsgCore
  {
    class Node; 
  }
}

namespace Project2
{
  class Shader : public Msg::MsgCore::StateAttribute
  {
    public: 

      /////////////////////////////////////////////////////////////////////////
      //
      // Shader interface. 
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual int program() const = 0;

      virtual void parseArguments( std::vector< std::string >& arguments ) = 0;
  };
}

#endif // __PROJECT2_SHADER_H__
