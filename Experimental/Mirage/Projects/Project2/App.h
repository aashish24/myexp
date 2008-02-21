
#ifndef __APP_H__
#define __APP_H__

#include "PhongShading.h"

#include "Msg/MsgCore/Node.h"
#include "Msg/MsgCore/Group.h"

namespace Project
{
  class App
  {
    public: 

      typedef Msg::MsgCore::SmartPtr< Msg::MsgCore::Group >   GroupPtr;

      App();      
      virtual ~App();

      virtual void  init(); 
      virtual void  display();

      virtual void  update();

    private: 

      GroupPtr          _root;

      PhongShading*    _phongShader;
  };
}

#endif // __APP_H__
