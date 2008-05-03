
#include "BumpMapShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

#include "Image/Image.h"

#include "MsgCore/Node.h"
#include "MsgCore/Geometry.h"
#include "MsgCore/Group.h"
#include "MsgCore/Geode.h"
#include "MsgCore/SmartPtr.h"

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
  

  void BumpMapShader::calculateTBN( Msg::MsgCore::Geometry* geom )
  { 
    if( geom )
    {
      Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > t( new Msg::MsgCore::Vec3Array() );
      Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > b( new Msg::MsgCore::Vec3Array() );
      Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > n( new Msg::MsgCore::Vec3Array() );
      this->doCalculateTBN( geom, t.get(), b.get(), n.get() );

      geom->setTangetTBNArray( t.get() );
      geom->setBinormalTBNArray( b.get() );
      geom->setNormalTBNArray( n.get() );     
    }
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
      if( !geom->getTangentTBNArray() )
      {
        calculateTBN( geom.get() );       
      }

      glEnableVertexAttribArray( _locT );    
      glVertexAttribPointer( _locT, 3, GL_DOUBLE, false, 0, geom->getTangentTBNArray()->getDataPointer() );        
      
      glEnableVertexAttribArray( _locB );    
      glVertexAttribPointer( _locB, 3, GL_DOUBLE, false, 0, geom->getBinormalTBNArray()->getDataPointer() );  
      
      glEnableVertexAttribArray( _locN );    
      glVertexAttribPointer( _locN, 3, GL_DOUBLE, false, 0, geom->getNormalTBNArray()->getDataPointer() );  

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

  
  void BumpMapShader::doCalculateTBN( Msg::MsgCore::Geometry* geom, Msg::MsgCore::Vec3Array* tangent, 
                                    Msg::MsgCore::Vec3Array* binormal, Msg::MsgCore::Vec3Array* normal )
  {
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > vertices = geom->getVertexArray();
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3iArray > indices = geom->getVertexIndices();

    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > texcoords = geom->getTexCoordArray();

    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > normals = geom->getNormalArray();

    if( !vertices.valid() || !texcoords.valid() || !normals.valid() ) 
    {
      return;
    }

    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > tan1 = new Msg::MsgCore::Vec3Array( vertices->size() );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > tan2 = new Msg::MsgCore::Vec3Array( vertices->size() );
    
    // For this algorithm see "Mathematics for 3D Game Programming & Computer Graphics", 
    // Section 6.8.3.
    // @Precondition: 
    // Geometry has indices which defines how many faces / triangles are 
    // there in the geometry. 
    for( size_t i = 0; i < ( indices->size()  ); ++i )
    {
      long i1 = indices->at( i )[0];
      long i2 = indices->at( i )[1];
      long i3 = indices->at( i )[2];

      double x1 = vertices->at( i2 )[0] - vertices->at( i1 )[0];
      double x2 = vertices->at( i3 )[0] - vertices->at( i1 )[0];
      
      double y1 = vertices->at( i2 )[1] - vertices->at( i1  )[1];
      double y2 = vertices->at( i3 )[1] - vertices->at( i1 )[1];      
      
      double z1 = vertices->at( i2 )[2] - vertices->at( i1 )[2];
      double z2 = vertices->at( i3 )[2] - vertices->at( i1 )[2];
      
      double s1 = texcoords->at( i2 )[0] - texcoords->at( i1 )[0];
      double s2 = texcoords->at( i3 )[0] - texcoords->at( i1 )[0];
      
      double t1 = texcoords->at( i2 )[1] - texcoords->at( i1 )[1];
      double t2 = texcoords->at( i3 )[1] - texcoords->at( i1 )[1];          

      double denom = 1.0f / ( s1 * t2 - s2 * t1 );
      
      //if ( denom > -0.001 || denom < 0.001 ) 
      if( false )
      {        
        Vec3d T, B;

        T = Vec3d( 1.0f, 0.0f, 0.0f );
        B = Vec3d( 0.0f, 1.0f, 0.0f );

        tan1->at( i1 ) = tan1->at( i1 ) + T;
        tan1->at( i2 ) = tan1->at( i2 ) + T;
        tan1->at( i3 ) = tan1->at( i3 ) + T;
        
        tan2->at( i1 ) = tan2->at( i1 ) + B;
        tan2->at( i2 ) = tan2->at( i2 ) + B;
        tan2->at( i3 ) = tan2->at( i3 ) + B;
       
      }
      else
      {
        Vec3d T, B;
      
        T = Vec3d( ( t2 * x1 - t1 * x2 ) * denom, ( t2 * y1 - t1 * y2 ) * denom, ( t2 * z1 - t1 * z2 ) * denom );
        B = Vec3d( ( s1 * x2 - s2 * x1 ) * denom, ( s1 * y2 - s2 * y1 ) * denom, ( s1 * z2 - s2 * z1 ) * denom ); 

        tan1->at( i1 ) = tan1->at( i1 ) + T;
        tan1->at( i2 ) = tan1->at( i2 ) + T;
        tan1->at( i3 ) = tan1->at( i3 ) + T;

        tan2->at( i1 ) = tan2->at( i1 ) + B;
        tan2->at( i2 ) = tan2->at( i2 ) + B;
        tan2->at( i3 ) = tan2->at( i3 ) + B;       
      }
    }   

    Msg::MsgCore::Vec3Array* tw = new Msg::MsgCore::Vec3Array(); 

    for( size_t i = 0; i < ( vertices->size() ); ++i )
    {
      Vec3d& n = normals->at( i );
      Vec3d& t = tan1->at( i );
      Vec3d& b = tan2->at( i );

      // @Todo: I am not sure why we need to normalize t here. 
      // Need to figure out the algorithm. 
      
      n.normalize();
      t.normalize(); 
      b.normalize();

      Vec3d tan3v = ( ( t - n * n.dot( t ) ) );            

      tan3v.normalize();      
      
      double f = ( ( ( n.cross( t ) ).dot( b ) ) < 0.0f ? -1.0f : 1.0f ); 

      tw->push_back( Vec3d( f, 0.0, 0.0 ) );

      tangent->push_back( tan3v );
    }      

    for( size_t j = 0; j < ( vertices->size() ); ++j )
    {
      Vec3d& n = normals->at( j );
      Vec3d& t = tangent->at( j );
      
      // @Todo: I am not sure why we need to normalize t here. 
      // Need to figure out the algorithm. 

      n.normalize();
      t.normalize();

      Vec3d bin3v = n.cross( t ) * tw->at( j )[0];
      bin3v.normalize();
      binormal->push_back( bin3v );
    }

    for( size_t j = 0; j < ( vertices->size() ); ++j )
    {      
      Vec3d norV = normals->at( j );
      norV.normalize();
      normal->push_back( norV );     
    }
  }


  static Shader* createBumpMapShader()
  {
    return new BumpMapShader();
  }


  static bool val = ShaderFactory::instance()->registerCreator( "BumpMapShader", createBumpMapShader );
}
