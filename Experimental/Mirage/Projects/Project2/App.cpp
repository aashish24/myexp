
#include "App.h"

namespace Project
{
  App::App() :
    _phongShader( 0x00 )
  {
  }


  App::~App()
  {
  }


  void App::init()
  {
    // Read config file here. 

    // Set OpenGL states. 
    glEnable( GL_DEPTH_TEST);
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // Initialize scene graph now. 
    _root = new Msg::MsgCore::Group();

    // Initialize shaders now. 
    _phongShader = new PhongShading();
    _phongShader->setShaders( "./Data/Shaders/Phong.vert", "./Data/Shaders/Phong.frag" );
  }


  void App::display()
  {
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
  }


  void App::update()
  {
  }
}