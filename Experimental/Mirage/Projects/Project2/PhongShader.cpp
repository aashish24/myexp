
#include "PhongShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

#include "MsgCore/Node.h"

namespace Project2
{
  PhongShader::PhongShader() : 
    _dirty( true ),
    _program( 0x00 )
  {
  }


  PhongShader::~PhongShader()
  {
  }


  std::string PhongShader::id() const 
  {
    return std::string( "Shader" );
  }


  void PhongShader::init() 
  {
    this->dirty( false );
  }


  bool PhongShader::dirty() const
  {
    return _dirty;
  }

  
  void PhongShader::dirty( bool flag )
  {
    _dirty = flag;
  }


  GLint PhongShader::program() const
  {
    return _program;
  }


  void PhongShader::parseArguments( std::vector< std::string >& arguments )
  {      
    for( size_t i = 0; i < arguments.size(); ++i )
    {
      if( arguments[i] == "--shader_file" )
      {
        this->setShader( ( arguments[i+1] + std::string( ".vert" ) ), ( arguments[i+1] + std::string( ".frag" ) ) );  
      }      
    }
  }

  
  void PhongShader::activate( Msg::MsgCore::Node* node )
  {
    if( this->dirty() )
    {
      this->init();
    }
  }


  void PhongShader::deActivate( Msg::MsgCore::Node* node )
  {
  }


  void PhongShader::setShader( const std::string &vert, const std::string &frag )
  {    
    ShadersUtil* shUtil = new ShadersUtil();
    _program = shUtil->setAndLoadShaders( vert, frag );
    delete shUtil;
  }


  Shader* createPhongShader()
  {
    return new PhongShader();
  }

  static bool val = ShaderFactory::instance()->registerCreator( "PhongShader", createPhongShader );
}