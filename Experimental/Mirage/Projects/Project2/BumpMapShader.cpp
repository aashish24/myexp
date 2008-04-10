
#include "BumpMapShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

namespace Project2
{
  BumpMapShader::BumpMapShader() : 
    _program( 0x00 )
  {
  }


  BumpMapShader::~BumpMapShader()
  {
  }


  void BumpMapShader::apply( Msg::MsgCore::Node* node )
  {
    this->setShader( "./Data/Shaders/BumpMapShader.vert", "./Data/Shaders/BumpMapShader.frag" );
  }


  void BumpMapShader::setShader( const std::string &vert, const std::string &frag )
  {
    ShadersUtil* shUtil = new ShadersUtil();
    shUtil->setAndLoadShaders( vert, frag );
    delete shUtil;
  }

  Shader* createBumpMapShader()
  {
    return new BumpMapShader();
  }

  static bool val = ShaderFactory::instance()->registerCreator( "PhongShader", createBumpMapShader );
}
