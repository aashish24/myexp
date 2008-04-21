
#ifndef __PROJECT2_APP_H__
#define __PROJECT2_APP_H__

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"
#include "MsgCore/NodeVisitor.h"

#include "Smtl/Vector.h"

namespace Project2
{
  // Forward declarations. 
  class Shader;

  /////////////////////////////////////////////////////////////////////////////
  //
  // Application class 
  //
  ///////////////////////////////////////////////////////////////////////////// 

  class App
  {
    public: 

      typedef Msg::MsgCore::SmartPtr< Msg::MsgCore::Group >   GroupPtr;

      /////////////////////////////////////////////////////////////////////////
      //
      // Constructor. 
      // 
      /////////////////////////////////////////////////////////////////////////
      App();      
      

      /////////////////////////////////////////////////////////////////////////
      //
      // Destructor. 
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual ~App();


      /////////////////////////////////////////////////////////////////////////
      //
      // Set arguments. 
      //
      /////////////////////////////////////////////////////////////////////////
      
      virtual void arguments( int& argc, char** argv );   


      /////////////////////////////////////////////////////////////////////////
      //
      // Parse arguments. 
      // 
      /////////////////////////////////////////////////////////////////////////

      virtual void parseArguments(); 


      /////////////////////////////////////////////////////////////////////////
      //
      // Initializing OpenGL and Shaders and loading sample dataset.
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual void  init(); 
      
      
      /////////////////////////////////////////////////////////////////////////
      //
      // Funtion to handle correct aspect based off Window width and height. 
      // 
      /////////////////////////////////////////////////////////////////////////      
      
      virtual void  reshape( int w, int h );

      
      /////////////////////////////////////////////////////////////////////////
      //
      // Initializing OpenGL and Shaders and loading sample dataset.
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual void  display();


      /////////////////////////////////////////////////////////////////////////
      //
      // Initializing OpenGL, Shaders and loading sample dataset.
      // 
      /////////////////////////////////////////////////////////////////////////
      
      virtual void  update();


    private: 

      std::vector< std::string >                          _arguments; 

      Smtl::Vec4f                                         _lightPosition;  

      GroupPtr                                            _root;
      Msg::MsgCore::SmartPtr< Shader >                    _shader;

      Msg::MsgCore::SmartPtr< Msg::MsgCore::NodeVisitor > _nodeVisitor;  
  };
}

#endif // __PROJECT2_APP_H__
