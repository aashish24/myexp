
#include "OsgTools/Geom/OsgQuad.h"

#include "osg/Geode"
#include "osg/Geometry"

OsgTools::Geom::OsgQuad::OsgQuad() : 
  osg::MatrixTransform(), 
  mFixedSize      ( true ), 
  mFixedAspect    ( true ),    
  mColor          ( 0.8, 0.8, 0.85, 1.0 )
{
}


OsgTools::Geom::OsgQuad::OsgQuad( const long double& width, const long double& height, const osg::Vec3f& pos ) :
  osg::MatrixTransform(), 
  mFixedSize      ( true ), 
  mFixedAspect    ( true ),    
  mColor          ( 0.8, 0.8, 1.0, 1.0 )  
{           
   buildQuad( width, height, pos );
}


OsgTools::Geom::OsgQuad::~OsgQuad()
{
}

void OsgTools::Geom::OsgQuad::buildQuad( const unsigned long& width, const unsigned long& height, const osg::Vec3f& pos )
{
  osg::ref_ptr< osg::Geode > geode( new osg::Geode() );

  // A plane needs three points. 

  osg::Vec3 v1 = pos; 
  osg::Vec3 v2 = pos + osg::Vec3( width, 0.0, 0.0 );
  osg::Vec3 v3 = v2 + osg::Vec3( 0.0, 0.0, height );
  osg::Vec3 v4 = pos + osg::Vec3( 0.0, 0.0, height );

  // create the geometry for the wall.
  osg::ref_ptr< osg::Geometry > geom( new osg::Geometry );
  
  osg::ref_ptr< osg::Vec3Array > vertices( new osg::Vec3Array( 4 ) );
  ( *vertices )[ 0 ].set( v1 );
  ( *vertices )[ 1 ].set( v2 );
  ( *vertices )[ 2 ].set( v3 );
  ( *vertices )[ 3 ].set( v4 );          

  osg::ref_ptr< osg::Vec2Array > texCoords( new osg::Vec2Array( 4 ) );
  ( *texCoords )[ 0 ].set( 0.0, 0.0 );
  ( *texCoords )[ 1 ].set( 0.0, 1.0 );
  ( *texCoords )[ 2 ].set( 1.0, 1.0 );
  ( *texCoords )[ 3 ].set( 0.0, 1.0 );
  
  osg::ref_ptr< osg::Vec4Array > color( new osg::Vec4Array( 1 ) );
  ( *color )[ 0 ].set( mColor[ 0 ], mColor[ 1 ], mColor[ 2 ], mColor[ 3 ] );
  
  //// @Todo: Find normal for this quad. 
  //osg::ref_ptr< osg::Vec3Array > normal( new osg::Vec3Array( 1 ) );
  //( *normal )[ 0 ].set( 0.0, -1.0, 0.0 );

  geom->setVertexArray( vertices.get() );       
  geom->setTexCoordArray( 0, texCoords.get() );

  //geom->setNormalArray( normal.get() );          
  //geom->setNormalBinding( osg::Geometry::BIND_OVERALL );

  geom->setColorArray( color.get() );
  geom->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE );            

  geom->addPrimitiveSet( new osg::DrawArrays( GL_QUADS, 0, 4 ) );
  geode->addDrawable( geom.get() );

  this->addChild( geode.get() );
}


void OsgTools::Geom::OsgQuad::addTexture( osg::Texture2D* texture )
{
  mTextures.push_back( texture );
}


void OsgTools::Geom::OsgQuad::setTexture( osg::Texture2D* texture )
{ 
  this->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );  
}


void OsgTools::Geom::OsgQuad::useTexture( const unsigned int &index )
{
  this->getOrCreateStateSet()->setTextureAttributeAndModes( 0, mTextures[ index ].get(), osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );  
}