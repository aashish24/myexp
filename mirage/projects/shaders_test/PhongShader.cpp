
#include "PhongShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

#include "MsgCore/Node.h"

namespace Project2
{
  PhongShader::PhongShader() 
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


  void PhongShader::contextInit()
  {
    this->compileAndLink();
    this->dirty( false );
  }
  

  void PhongShader::parseArguments( std::vector< std::string >& arguments )
  {      
    for( size_t i = 0; i < arguments.size(); ++i )
    {
      if( arguments[i] == "--shader_file" )
      {
        this->setShaderFiles( ( arguments[i+1] + std::string( ".vert" ) ), ( arguments[i+1] + std::string( ".frag" ) ) );  
      }      
    }
  }

  
  void PhongShader::reset()
  {
    this->compileAndLink();
  }


  void PhongShader::activate( Msg::MsgCore::Node* node )
  {
    if( this->dirty() )
    {
      this->contextInit();
    }

    glUseProgram( this->program() );
  }


  void PhongShader::deActivate( Msg::MsgCore::Node* node )
  {
  }


  void PhongShader::setShaderFiles( const std::string &vert, const std::string &frag )
  {    
    // Save the file names for the future references. 
    this->vertexShaderFile( vert );
    this->fragmentShaderFile( frag );
  }


  void PhongShader::compileAndLink()
  {
    try
    {
      ShadersUtil* shUtil = new ShadersUtil();
      this->program( shUtil->compileAndLinkFiles( this->vertexShaderFile(), this->fragmentShaderFile() ) );
      delete shUtil;
    }
    catch( ... )
    {
      std::cerr << "Error 1063529326: Unknown error: " << std::endl;
      std::cerr << " Failed to create shader: " << std::endl;
    }
  }


  Shader* createPhongShader()
  {
    return new PhongShader();
  }

  static bool val = ShaderFactory::instance()->registerCreator( "PhongShader", createPhongShader );
}