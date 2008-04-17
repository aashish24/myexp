
#include "BumpMapShader.h"
#include "ShadersUtil.h"
#include "ShaderFactory.h"

#include "Image/Image.h"

#include "MsgCore/Geometry.h"
#include "MsgCore/Group.h"
#include "MsgCore/Geode.h"
#include "MsgCore/SmartPtr.h"

#include "sh/sh.hpp"
#include "shutil/shutil.hpp"
#include "sh/ShImage.hpp"

namespace Project2
{
  BumpMapShader::BumpMapShader() : 
    _program( 0x00 )
  {
  }


  BumpMapShader::~BumpMapShader()
  {
  }


  GLint BumpMapShader::program() const
  {
    return _program;
  }


  void BumpMapShader::apply( Msg::MsgCore::Node* node )
  {    

    this->setShader( "./Data/Shaders/BumpMapShader.vert", "./Data/Shaders/BumpMapShader.frag" );
   
    //glActiveTexture( GL_TEXTURE0 );        
    
    // Load normal map. 
    this->loadBumpMap( "./Data/Textures/NormalMap.bmp" );  

    if( Msg::MsgCore::Group* gr = dynamic_cast< Msg::MsgCore::Group* >( node ) )
    {
      size_t noOfChildren = gr->getChildren().size();

      for( size_t k = 0; k < noOfChildren; ++k )
      {
        Msg::MsgCore::Geode* ge = dynamic_cast< Msg::MsgCore::Geode* >( gr->getChild( k ) );
      
        size_t drawablesCount = ge->getDrawableList().size();

        for( size_t i = 0; i < drawablesCount; ++i )
        {
          Msg::MsgCore::Geometry* geom = dynamic_cast< Msg::MsgCore::Geometry* >( ge->getDrawable( i ) );

          if( geom )
          {
            Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > t( new Msg::MsgCore::Vec3Array() );
            Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > b( new Msg::MsgCore::Vec3Array() );
            Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > n( new Msg::MsgCore::Vec3Array() );
            calculateTBN( geom, t.get(), b.get(), n.get() );

            geom->setTangetTBNArray( t.get() );
            geom->setBinormalTBNArray( b.get() );
            geom->setNormalTBNArray( n.get() );

            //GLint locT  = glGetAttribLocation( _program, "tangent" );

            //// @Todo: Why we need to call this? 
            //glBindAttribLocation( _program, locT, "tangent" );  
            //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, t->getDataPointer() );  

            //GLint locB  = glGetAttribLocation( _program, "binormal" );
            //glBindAttribLocation( _program, locB, "binormal" );  
            //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, b->getDataPointer() );  
          }
        }
      }
    }
  }


  void BumpMapShader::draw()
  {
    //glUseProgram( _program );
    //
    //GLint locT  = glGetAttribLocation( _program, "tangent" );
    //glBindAttribLocation( _program, locT, "tangent" );  
    //       
    //GLint locB  = glGetAttribLocation( _program, "binormal" );
    //glBindAttribLocation( _program, locB, "binormal" );    

    //// Locate uniform for BumpMap sampler. 
    //GLint loc = glGetUniformLocation( _program, "normalMap" ); 
    //glUniform1i ( loc, 0 );  
  }


  void BumpMapShader::loadBumpMap( const std::string& fileName )
  {
    // Load normal map. 
   /* ShImage normalMap;
    ShUtil::load_PNG( normalMap, fileName );    
    GLuint texIndex;
    glGenTextures( 1,  &texIndex );
    glBindTexture( GL_TEXTURE_2D, texIndex );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB,
                       normalMap.width(), normalMap.height(),
                       GL_RGB,
                       GL_FLOAT, normalMap.data() );    */

    IMAGE image; 
    image.Load( const_cast< char* >( fileName.c_str() ) );
    image.ExpandPalette();
    GLuint texIndex;
    glGenTextures( 1,  &texIndex );
    glBindTexture( GL_TEXTURE_2D, texIndex );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8,
                       image.width, image.height,
                       image.format,
                       GL_UNSIGNED_BYTE, image.data ); 

  }


  void BumpMapShader::loadDecalMap( const std::string& filename ) 
  {
    
  }


  void BumpMapShader::setShader( const std::string &vert, const std::string &frag )
  {    
    ShadersUtil* shUtil = new ShadersUtil();
    _program = shUtil->setAndLoadShaders( vert, frag );
    delete shUtil;
  }

  
  void BumpMapShader::calculateTBN( Msg::MsgCore::Geometry* geom, Msg::MsgCore::Vec3Array* tangent, 
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

      float x1 = vertices->at( i1 )[0] - vertices->at( i1 )[0];
      float x2 = vertices->at( i3 )[0] - vertices->at( i1 )[0];
      float y1 = vertices->at( i2 )[1] - vertices->at( i1  )[1];
      float y2 = vertices->at( i2 )[1] - vertices->at( i1 )[1];      
      float z1 = vertices->at( i1 )[2] - vertices->at( i1 )[2];
      float z2 = vertices->at( i2 )[2] - vertices->at( i1 )[2];
      
      float s2 = texcoords->at( i2 )[0] - texcoords->at( i1 )[0];
      float s1 = texcoords->at( i1 )[0] - texcoords->at( i1 )[0];

      float t1 = texcoords->at( i2 )[1] - texcoords->at( i1 )[1];
      float t2 = texcoords->at( i1 )[1] - texcoords->at( i1 )[1];          

      float denom = 1.0f / ( s2 * t2 - s2 * t1 );
      
      if ( denom > -0.001 || denom < 0.001 ) 
      {        
        Vec3f T, B;

        T = Vec3f( 1.0f, 0.0f, 0.0f );
        B = Vec3f( 0.0f, 1.0f, 0.0f );

        tan1->at( i1 ) = tan1->at( i1 ) + T;
        tan1->at( i2 ) = tan1->at( i2 ) + T;
        tan1->at( i3 ) = tan1->at( i3 ) + T;
        
        tan2->at( i1 ) = tan2->at( i1 ) + B;
        tan2->at( i2 ) = tan2->at( i2 ) + B;
        tan2->at( i3 ) = tan2->at( i3 ) + B;
       
      }
      else
      {
        Vec3f T, B;
      
        T = Vec3f( ( t2 * x1 - t1 * x2 ) * denom, ( t2 * y1 - t1 * y2 ) * denom, ( t2 * z1 - t1 * z2 ) * denom );
        B = Vec3f( ( s1 * x2 - s2 * x1 ) * denom, ( s1 * y2 - s2 * y1 ) * denom, ( s1 * z2 - s2 * z1 ) * denom ); 

        tan1->at( i1 ) = tan1->at( i1 ) + T;
        tan1->at( i2 ) = tan1->at( i2 ) + T;
        tan1->at( i3 ) = tan1->at( i3 ) + T;

        tan2->at( i1 ) = tan2->at( i1 ) + B;
        tan2->at( i2 ) = tan2->at( i2 ) + B;
        tan2->at( i3 ) = tan2->at( i3 ) + B;       
      }
    }

    // Now average and orthogonalize the vectors. 
    // 1. tangents. 
    // 2. binormals. 
    // 3. normals. 

    //Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > tangentsT = new Msg::MsgCore::Vec3Array();
    //Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > binormalsB = new Msg::MsgCore::Vec3Array();
    //Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > normalsN = new Msg::MsgCore::Vec3Array();

    for( size_t i = 0; i < ( vertices->size() ); ++i )
    {
      Vec3f& n = normals->at( i );
      Vec3f& t = tan1->at( i );
      Vec3f& b = tan2->at( i );

      Vec3f tan3v = ( ( t - n * n.dot( t ) ) );      
      tan3v.normalize();
      tan3v = tan3v * ( ( ( n.cross( t ) ).dot( b ) ) < 0.0f ? -1.0f : 1.0f );
      tangent->push_back( tan3v );
    }      

    for( size_t j = 0; j < ( vertices->size() ); ++j )
    {
      Vec3f& n = normals->at( j );
      Vec3f& t = tan1->at( j );

      Vec3f bin3v = n.cross( t ) * 1.0;
      binormal->push_back( bin3v );
    }

    for( size_t j = 0; j < ( vertices->size() ); ++j )
    {
      Vec3f norV = tangent->at(j).cross( binormal->at(j) );
      norV.normalize();
      normal->push_back( norV );
    }

    //// Now find the inverse. 
    //for( size_t j = 0; j < ( vertices->size() ); ++j )
    //{
    //  float fScale2 = 1.0f / (( tangentsT->at(j)[0] * binormalsB->at(j)[1] * normalsN->at(j)[2] - tangentsT->at(j)[2] * binormalsB->at(j)[1] * normalsN->at(j)[0] ) + 
    //                          ( binormalsB->at(j)[0] * normalsN->at(j)[1] * tangentsT->at(j)[2] - binormalsB->at(j)[2] * normalsN->at(j)[1] * tangentsT->at(j)[0]) + 
    //                          ( normalsN->at(j)[0] * tangentsT->at(j)[1] * binormalsB->at(j)[2] - normalsN->at(j)[2] * tangentsT->at(j)[1] * binormalsB->at(j)[0] ));
    //  
    //  Vec3f T = Vec3f( binormalsB->at(j).cross( normalsN->at(j) )[0] * fScale2, 
    //                   ( -1.0f * normalsN->at(j).cross( tangentsT->at(j) )[0] * fScale2,
    //                   tangentsT->at(j).cross( binormalsB->at(j) )[0] * fScale2 ) );
    //  T.normalize();

    //  tangent->push_back( T );
    //  
    //  
    //  Vec3f B = Vec3f( -1.0f * binormalsB->at(j).cross( normalsN->at(j) )[1] * fScale2, 
    //                   ( normalsN->at(j) ).cross( tangentsT->at(j) )[1] * fScale2,
    //                   ( -1.0f * tangentsT->at(j).cross( binormalsB->at(j) )[1] * fScale2 ) );
    //  B.normalize();
    //  binormal->push_back( B );

    //  Vec3f N = Vec3f( binormalsB->at(j).cross( normalsN->at(j) )[2] * fScale2, 
    //                   ( -1.0f * normalsN->at(j).cross( tangentsT->at(j) )[2] * fScale2,
    //                   tangentsT->at(j).cross( binormalsB->at(j) )[2] * fScale2 ) );

    //  N.normalize();
    //  normal->push_back( N );
    //}
  }


  Shader* createBumpMapShader()
  {
    return new BumpMapShader();
  }


  static bool val = ShaderFactory::instance()->registerCreator( "BumpMapShader", createBumpMapShader );
}
