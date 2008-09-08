
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
      if( !geom->tangentArray() )
      {
        try
        {
          Msg::MsgUtil::GeometryFuncs::generateTBNs( geom.get() );
        }
        catch( ... )
        {
          // @Todo: How to disable this attribute. We need to find a way.           
          std::cerr << " ERROR 3892253893: Unknown error. " << std::endl;
          
          assert( false ); 
          return;
        }
      }

      if( geom->tangentArray() && geom->binormalArray() && geom->normalArray() )
      {
        glEnableVertexAttribArray( _locT );    
        glVertexAttribPointer( _locT, 3, GL_DOUBLE, false, 0, geom->tangentArray()->getDataPointer() );        
        
        glEnableVertexAttribArray( _locB );    
        glVertexAttribPointer( _locB, 3, GL_DOUBLE, false, 0, geom->binormalArray()->getDataPointer() );  
        
        glEnableVertexAttribArray( _locN );    
        glVertexAttribPointer( _locN, 3, GL_DOUBLE, false, 0, geom->normalArray()->getDataPointer() );  

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
        std::cerr << " ERROR 2395475227: Missing tangent, binormal or normal array. " << std::endl;
        return;
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
      std::cerr << " ERROR 1120598588: " << e.what() << std::endl;
      return;
    }
    catch( ... )
    {
      std::cerr << " ERROR 3490106803: Unknown error. " << std::endl;
      return;
    }

    if( ! image.data  )
    {
      throw " ERROR 7626153710: Image contains invalid or no data. ";
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
      std::cerr << " ERROR 9940214690: " << e.what() << std::endl;
      throw;
    }
    catch( ... )
    {
      std::cerr << " ERROR: 3137731113: Unknown error. " << std::endl;
      throw;
    }

    if( !image.data )
    {
      std::cerr << " ERROR 1478987840: Missing of invalid image data. " << std::endl;
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
      std::cerr << " ERROR 1042252865: Unknown error. " << std::endl;
      std::cerr << " Failed to create shader.  " << std::endl;
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
      std::cerr << " ERROR 1042252865: Unknown error. " << std::endl;
      std::cerr << " Failed to create shader. " << std::endl;
    }
  }  
  

  static Shader* createBumpMapShader()
  {
    return new BumpMapShader();
  }


  static bool val = ShaderFactory::instance()->registerCreator( "BumpMapShader", createBumpMapShader );
}
