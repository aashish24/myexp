
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


  void PhongShader::set()
  {
    this->setShader( "./Data/Shaders/PhongShading.vert", "./Data/Shaders/PhongShading.frag" );
  }


  void PhongShader::setShader( const std::string &vert, const std::string &frag )
  {
    ShadersUtil* shUtil = new ShadersUtil();
    shUtil->setAndLoadShaders( vert, frag );
    delete shUtil;
  }

  Shader* create()
  {
    return new PhongShader();
  }

  bool val = ShaderFactory::instance()->registerCreator( "PhongShader", create );
}