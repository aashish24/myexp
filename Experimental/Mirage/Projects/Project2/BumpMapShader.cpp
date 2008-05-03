
#include "BumpMapShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

#include "Image/Image.h"

#include "MsgCore/Node.h"
#include "MsgCore/Geometry.h"
#include "MsgCore/Group.h"
#include "MsgCore/Geode.h"
#include "MsgCore/SmartPtr.h"

#include "MsgUtil/GeometryFuncs.h" 

#include "GL/gl.h"

#include "sh/sh.hpp"
#include "shutil/shutil.hpp"
#include "sh/ShImage.hpp"

namespace Project2
{
  BumpMapShader::BumpMapShader() :   
    _useDecalMap( false ),     
    _locT( -1 ), 
    _locB( -1 ), 
    _locN( -1 ),
    _locNormalMap( -1 ), 
    _locDecalMap( -1 ), 
    _locUseDecalMap( -1 ), 
    _normalMapTexIndex( -1 ), 
    _decalMapTexIndex( -1 )
  {
  }


  BumpMapShader::~BumpMapShader()
  {
  }


  std::string BumpMapShader::id() const 
  {
    return std::string( "BumpMapShader" );
  }


  void BumpMapShader::init()
  {
  }


  void BumpMapShader::contextInit()
  {
    compileAndLink();
      
    _locT  = glGetAttribLocation( _program, "tangent" );
    _locB  = glGetAttribLocation( _program, "binormal" );
    _locN  = glGetAttribLocation( _program, "normal" );
        
    _locNormalMap = glGetUniformLocation( _program, "normalMap" ); 
    _locDecalMap  = glGetUniformLocation( _program, "decalMap" ); 

    _locUseDecalMap  = glGetUniformLocation( _program, "useDecalMap" ); 
  }

 
  void BumpMapShader::reset()
  {   
    // Assuming that we are loading shaders from the file only. 
    compileAndLink();
  }
  
  
  void  BumpMapShader::parseArguments( std::vector< std::string >& arguments )
  {      
    for( size_t i = 0; i < arguments.size(); ++i )
    {
      if( arguments[i] == "--shader_file" )
      {
        this->setShaderFiles( ( arguments[i+1] + std::string( ".vert" ) ), ( arguments[i+1] + std::string( ".frag" ) ) );  
      }
      if( arguments[i] == "--normal_map" )
      {
        this->loadBumpMap( arguments[i+1] );
      }
      if( arguments[i] == "--decal_map" )
      {
        this->loadDecalMap( arguments[i+1] );
      }
    }
  }


  void BumpMapShader::activate( Msg::MsgCore::Node* node )
  {
    if( dirty() )
    {
      contextInit(); 
      dirty( false );
    }

    glUseProgram( this->program() );
    
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Geometry > geom = dynamic_cast< Msg::MsgCore::Geometry* >( node );
    
    if( geom.valid() )
    {     
      // Only if we dont have tangent array we will do the calculation. 
      //
      // @Note: Here we are assuming that if we dont have tangent array that means 
      // that we are missing binormals as well. 
      if( !geom->getTangentArray() )
      {
        try
        {
          Msg::MsgUtil::GeometryFuncs::generateTBNs( geom.get() );
        }
        catch( ... )
        {
          // @Todo: How to disable this attribute. We need to find a way.           
          std::cerr << "Error 3892253893: Unknown error. " << std::endl;
          
          assert( false );          
        }
      }

      if( geom->getTangentArray() && geom->getBinormalArray() && geom->getNormalArray() )
      {
        glEnableVertexAttribArray( _locT );    
        glVertexAttribPointer( _locT, 3, GL_DOUBLE, false, 0, geom->getTangentArray()->getDataPointer() );        
        
        glEnableVertexAttribArray( _locB );    
        glVertexAttribPointer( _locB, 3, GL_DOUBLE, false, 0, geom->getBinormalArray()->getDataPointer() );  
        
        glEnableVertexAttribArray( _locN );    
        glVertexAttribPointer( _locN, 3, GL_DOUBLE, false, 0, geom->getNormalArray()->getDataPointer() );  

        // Locate uniform for BumpMap sampler.      
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, _normalMapTexIndex );
        glUniform1i ( _locNormalMap, 0 );           
          
        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, _decalMapTexIndex );
        glUniform1i ( _locDecalMap, 1 );           

        // Set the boolean flag in the shader to use decal map. 
        glUniform1i( _locUseDecalMap, _useDecalMap );
      }
      else
      {
        std::cerr << "Error 2395475227: Missing tangent, binormal or normal array. " << std::endl;
      }
    }
  }


  void BumpMapShader::deActivate( Msg::MsgCore::Node* node )
  {
    if( !dirty() )
    {
      // Disabling generic attribute arrays.         
      glDisableVertexAttribArray( _locN );
      glDisableVertexAttribArray( _locB );
      glDisableVertexAttribArray( _locT );    
    }
  }


  void BumpMapShader::loadBumpMap( const std::string& fileName )
  {
    // Load normal map.    
    IMAGE image;
    
    try
    {      
      image.Load( const_cast< char* >( fileName.c_str() ) );
      image.ExpandPalette();    
    }
    catch( std::exception& e )
    {
      std::cerr << "Error " << e.what() << std::endl;
      throw;
    }
    catch( ... )
    {
      std::cerr << "Unknown error: " << std::endl;
      throw;
    }

    if( ! image.data  )
    {
      throw "Image data is NULL: ";
    }

    glActiveTexture( GL_TEXTURE0 );
    glGenTextures( 1,  &_normalMapTexIndex );
    glBindTexture( GL_TEXTURE_2D, _normalMapTexIndex );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8,
                       image.width, image.height,
                       image.format,
                       GL_UNSIGNED_BYTE, image.data ); 

  }


  void BumpMapShader::loadDecalMap( const std::string& fileName ) 
  {
    IMAGE image; 

    try
    {
      image.Load( const_cast< char* >( fileName.c_str() ) );
      image.ExpandPalette();    
    }
    catch( std::exception& e )
    {
      std::cerr << "Error " << e.what() << std::endl;
      throw;
    }
    catch( ... )
    {
      std::cerr << "Unknown error: " << std::endl;
      throw;
    }

    if( !image.data )
    {
      this->_useDecalMap = false;
      return;
    }    

    glActiveTexture( GL_TEXTURE1 );
    glGenTextures( 1, &_decalMapTexIndex );
    glBindTexture( GL_TEXTURE_2D, _decalMapTexIndex );   
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, image.width, image.height, image.format, GL_UNSIGNED_BYTE, image.data );

    // Ok now we can ask shaders to use this decal map. 
    // 
    // @Note: We are still not checking for any OpenGL error here.     
    this->_useDecalMap = true;
  }


  void BumpMapShader::setShaderFiles( const std::string &vert, const std::string &frag )
  { 
    try
    {
      this->vertexShaderFile( vert );
      this->fragmentShaderFile( frag );      
    }
    catch( ... )
    {
      std::cerr << "Error 1042252865: Unknown error: " << std::endl;
      std::cerr << " Failed to create shader: " << std::endl;
    }
  }


  void BumpMapShader::compileAndLink() 
  {
    try
    {
      ShadersUtil* shUtil = new ShadersUtil();    
      this->program( shUtil->compileAndLinkFiles( this->vertexShaderFile(), this->fragmentShaderFile() ) );
      delete shUtil;
    }
    catch( ... )
    {
      std::cerr << "Error 1042252865: Unknown error: " << std::endl;
      std::cerr << " Failed to create shader: " << std::endl;
    }
  }  
  

  static Shader* createBumpMapShader()
  {
    return new BumpMapShader();
  }


  static bool val = ShaderFactory::instance()->registerCreator( "BumpMapShader", createBumpMapShader );
}
