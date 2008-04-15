
#ifndef __PROJECT2_SHADER_H__
#define __PROJECT2_SHADER_H__

namespace Msg
{
  namespace MsgCore
  {
    class Node; 
  }
}

namespace Project2
{
  class Shader 
  {
    public: 

      /////////////////////////////////////////////////////////////////////////
      //
      // Shader interface. 
      // 
      /////////////////////////////////////////////////////////////////////////

      virtual GLint program() const = 0;

      virtual void apply( Msg::MsgCore::Node* node ) = 0;     

      virtual void draw() = 0;
  };
}

#endif // __PROJECT2_SHADER_H__
