
#include "PhongShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

namespace Project2
{
  PhongShader::PhongShader() : 
    _program( 0x00 )
  {
  }


  PhongShader::~PhongShader()
  {
  }


  void PhongShader::apply( Msg::MsgCore::Node* node )
  {
    this->setShader( "./Data/Shaders/PhongShader.vert", "./Data/Shaders/PhongShader.frag" );
  }


  void PhongShader::setShader( const std::string &vert, const std::string &frag )
  {
    ShadersUtil* shUtil = new ShadersUtil();
    shUtil->setAndLoadShaders( vert, frag );
    delete shUtil;
  }

  Shader* createPhongShader()
  {
    return new PhongShader();
  }

  static bool val = ShaderFactory::instance()->registerCreator( "PhongShader", createPhongShader );
}