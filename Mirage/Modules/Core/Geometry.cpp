
#include "Core/Geometry.h"
#include "Core/PrimitiveSet.h"

#include "GL/glew.h"
#include "GL/gl.h"

#include <map>
#include <vector>

using namespace Mirage::Core;

Geometry::Geometry( ) :
  _fastPath       ( true ),
  _glDrawMethod   ( VERTEX_ARRAYS ), 
  _vertices       ( 0x00 ),
  _normals        ( 0x00 ), 
  _textureCoords  ( 0x00 ),   
  _colors         ( 0x00 ),   
  _tangents       ( 0x00 ),      
  _binormals      ( 0x00 ),   
  _vertexIndices  ( 0x00 ), 
  _normalIndices  ( 0x00 ),
  _textureIndices ( 0x00 ),
  _attrBinding    ( BIND_PER_VERTEX ), 
	_primitiveSets  ( 0x00 )
{
}


Geometry::Geometry( const Geometry& geom ) :
  _fastPath       ( geom._fastPath ), 
  _vertices       ( geom._vertices ),
  _normals        ( geom._normals ), 
  _textureCoords  ( geom._textureCoords ),   
  _colors         ( geom._colors ),   
  _tangents       ( geom._tangents ),      
  _binormals      ( geom._binormals ),   
  _vertexIndices  ( 0x00 ), 
  _normalIndices  ( 0x00 ),
  _textureIndices ( 0x00 ),
  _attrBinding    ( BIND_PER_VERTEX ), 
	_primitiveSets  ( 0x00 )
{
}


bool Geometry::hasFastPath() 
{
  if( this->attributeBinding() == BIND_PER_PRIMITIVE || ( this->glDrawMethod() == INDIVIDUAL  ) )
  {
    _fastPath = false;
  }
  
  return _fastPath;
}


void Geometry::useFastPath( const bool& val )
{
  _fastPath = val;
}


Geometry::PrimitiveSets& Geometry::primitiveSets() 
{
  return _primitiveSets;
}


Vec3Array* Geometry::vertexArray()
{	
	return _vertices.get();
}


void Geometry::vertexArray( Vec3Array* vArray )
{
	_vertices = vArray;
}


Vec3Array* Geometry::normalArray()
{
	return _normals.get();
}


void Geometry::normalArray(  Vec3Array* nArray )
{
	_normals = nArray;
}


Vec3Array* Geometry::textureCoordArray()
{
	return _textureCoords.get();
}


void Geometry::textureCoordArray( Vec3Array* textureCoordArray )
{
	_textureCoords = textureCoordArray;
}


Vec4Array* Geometry::colorArray()
{
	return _colors.get();
}


void Geometry::colorArray( Vec4Array* colorArray )
{
	_colors = colorArray;
}


Vec3Array* Geometry::tangentArray() 
{
  return _tangents.get();
}


void Geometry::tangentArray( Vec3Array* tangentArray )
{
  _tangents = tangentArray;
}


Vec3Array* Geometry::binormalArray() 
{
  return _binormals.get();
}


void Geometry::binormalArray( Vec3Array* binormalArray )
{
  _binormals = binormalArray;
}


Geometry::AttributeBinding Geometry::attributeBinding()
{
	return _attrBinding;
}


void Geometry::attributeBinding( const Geometry::AttributeBinding& attrBinding )
{
	_attrBinding = attrBinding;
}


Vec3iArray* Geometry::vertexIndices()
{
	return _vertexIndices.get();
}


void Geometry::vertexIndices( Vec3iArray* viArray )
{
	_vertexIndices = viArray;
}


Vec3iArray* Geometry::normalIndices()
{
	return _normalIndices.get();
}


void Geometry::normalIndices( Vec3iArray* niArray )
{
	_normalIndices = niArray;
}


Vec3iArray* Geometry::textureCoordIndices()
{
  return _textureIndices.get();
}


void Geometry::textureCoordIndices( Vec3iArray* niArray )
{
  _textureIndices = niArray;
}


const OpenGLDrawMethod&  Geometry::glDrawMethod() const 
{
  return _glDrawMethod;
}


void Geometry::glDrawMethod( const Mirage::Core::OpenGLDrawMethod& method )
{
  _glDrawMethod = method;
}



void Geometry::generateNormals( Geometry::AttributeBinding attrBinding )
{
	std::string bindingType("");

	if( attrBinding == Geometry::BIND_PER_PRIMITIVE )
	{
		bindingType = "BIND_PER_PRIMITIVE";
	}
	else if ( attrBinding == Geometry::BIND_PER_VERTEX )
	{
		bindingType = "BIND_PER_VERTEX";
	}

	std::cout << "Creating normals with binding " << bindingType << std::endl;

	SmartPtr< Vec3Array >  normals   = new Vec3Array();
	SmartPtr< Vec3iArray > nIndices  = new Vec3iArray();

	for( size_t i=0; i < _vertexIndices->size(); ++i )
	{
		Math::Vec3d vec1 = _vertices->at( _vertexIndices->at(i)[1] ) - _vertices->at( _vertexIndices->at(i)[0] );
		Math::Vec3d vec2 = _vertices->at( _vertexIndices->at(i)[2] ) - _vertices->at( _vertexIndices->at(i)[0] );
		Math::Vec3d normal = vec1.cross( vec2 );		
		normal.normalize();
		normals->push_back( normal );
		nIndices->push_back( Math::Vec3i( i, 0, 0 ) );
	}	

	if( attrBinding == Geometry::BIND_PER_PRIMITIVE )
	{
		_normals = normals.get();
		_normalIndices = nIndices.get();
	}
	else if( attrBinding == Geometry::BIND_PER_VERTEX )
	{
		typedef std::map< int, std::vector< int > >  MapVertexIDToPrimitiveID;

		MapVertexIDToPrimitiveID mapVertexIDToPrimitiveID;
		std::vector< int > PrimitiveIDs;

		// Point each VertextID to a vector of PrimitiveIDs. 
		for( size_t i=0; i < _vertexIndices->size(); ++i )
		{
			mapVertexIDToPrimitiveID[ _vertexIndices->at(i)[0] ] = PrimitiveIDs;
			mapVertexIDToPrimitiveID[ _vertexIndices->at(i)[1] ] = PrimitiveIDs;
			mapVertexIDToPrimitiveID[ _vertexIndices->at(i)[2] ] = PrimitiveIDs;
		}

		// Now fill the this map. 
		for( size_t i=0; i < _vertexIndices->size(); ++i )
		{
			mapVertexIDToPrimitiveID[ _vertexIndices->at(i)[0] ].push_back( i );
			mapVertexIDToPrimitiveID[ _vertexIndices->at(i)[1] ].push_back( i );
			mapVertexIDToPrimitiveID[ _vertexIndices->at(i)[2] ].push_back( i );
		}
		
		// Now calculate per vertex normals. 
		SmartPtr< Vec3Array >  perVertexNormals = new Vec3Array();		

		MapVertexIDToPrimitiveID::iterator itr = mapVertexIDToPrimitiveID.begin();		
		for( itr; itr != mapVertexIDToPrimitiveID.end(); ++itr )
		{
			Math::Vec3d vertextNormal;
			for( size_t i = 0; i < itr->second.size(); ++i )
			{				
				vertextNormal = vertextNormal + normals->at( ( itr->second.at( i ) ) );
			}
			vertextNormal.normalize();
			perVertexNormals->push_back( vertextNormal );
		}		

		_normals = perVertexNormals.get();
	}

	std::cout << "Finished creating normals with binding " << bindingType << std::endl;
}


void Geometry::addPrimitiveSet( PrimitiveSet* primitiveSet )
{
	_primitiveSets.push_back( primitiveSet );
}


void Geometry::drawImplementation() 
{
  // This is a slow path. 
  // @Todo: Need to revamp the code sometime to make the drawing via different ways.   
  if( !this->hasFastPath() )
  {
	  glBegin( GL_TRIANGLES );
	  for( size_t i=0; i < _vertexIndices->size(); ++ i )
	  {
		  if( _attrBinding == Geometry::BIND_PER_PRIMITIVE )
		  {
			  if( _normals.valid())
			  {
				  glNormal3d( _normals->at( _normalIndices->at(i)[0] )[0],
							        _normals->at( _normalIndices->at(i)[0] )[1],
							        _normals->at( _normalIndices->at(i)[0] )[2] );	  
			  }

			  glVertex3d(   _vertices->at( _vertexIndices->at(i)[0] )[0], 	
						          _vertices->at( _vertexIndices->at(i)[0] )[1], 
						          _vertices->at( _vertexIndices->at(i)[0] )[2] );

			  glVertex3d(   _vertices->at( _vertexIndices->at(i)[1] )[0], 	
						          _vertices->at( _vertexIndices->at(i)[1] )[1], 
						          _vertices->at( _vertexIndices->at(i)[1] )[2] );

			  glVertex3d(   _vertices->at( _vertexIndices->at(i)[2] )[0], 	
						          _vertices->at( _vertexIndices->at(i)[2] )[1], 
						          _vertices->at( _vertexIndices->at(i)[2] )[2] );
		  }
		  else if( _attrBinding == Geometry::BIND_PER_VERTEX )
		  {
  			
        glNormal3d(   _normals->at( _normalIndices->at(i)[0] )[0],
						          _normals->at( _normalIndices->at(i)[0] )[1],
						          _normals->at( _normalIndices->at(i)[0] )[2] );

        glTexCoord3d( _textureCoords->at( _textureIndices->at(i)[0] )[0],
						          _textureCoords->at( _textureIndices->at(i)[0] )[1],
						          _textureCoords->at( _textureIndices->at(i)[0] )[2] );

			  glVertex3d(   _vertices->at( _vertexIndices->at(i)[0] )[0], 	
						          _vertices->at( _vertexIndices->at(i)[0] )[1], 
						          _vertices->at( _vertexIndices->at(i)[0] )[2] );

			  glNormal3d(   _normals->at( _normalIndices->at(i)[1] )[0],
						          _normals->at( _normalIndices->at(i)[1] )[1],
						          _normals->at( _normalIndices->at(i)[1] )[2] );

        glTexCoord3d( _textureCoords->at( _textureIndices->at(i)[1] )[0],
						          _textureCoords->at( _textureIndices->at(i)[1] )[1],
						          _textureCoords->at( _textureIndices->at(i)[1] )[2] );

			  glVertex3d(   _vertices->at( _vertexIndices->at(i)[1] )[0], 	
						          _vertices->at( _vertexIndices->at(i)[1] )[1], 
						          _vertices->at( _vertexIndices->at(i)[1] )[2] );

			  glNormal3d(   _normals->at( _normalIndices->at(i)[2] )[0],
						          _normals->at( _normalIndices->at(i)[2] )[1],
						          _normals->at( _normalIndices->at(i)[2] )[2] );

        glTexCoord3d( _textureCoords->at( _textureIndices->at(i)[2] )[0],
						          _textureCoords->at( _textureIndices->at(i)[2] )[1],
						          _textureCoords->at( _textureIndices->at(i)[2] )[2] );

			  glVertex3d(   _vertices->at( _vertexIndices->at(i)[2] )[0], 	
						          _vertices->at( _vertexIndices->at(i)[2] )[1], 
						          _vertices->at( _vertexIndices->at(i)[2] )[2] );
		  }
	  }
	  glEnd();
  }
  else if( glDrawMethod() == VERTEX_ARRAYS )
  {
    // Set all the vertex arrays and then dereference the vertex array later. 
    glVertexPointer( 3, GL_DOUBLE, 0, _vertices->getDataPointer() );

    if( _colors.valid() )
    {
	    glEnableClientState( GL_COLOR_ARRAY );
	    glColorPointer( 4, GL_DOUBLE, 0, _colors->getDataPointer() );
    }

    if( _normals.valid() )
    {
	    glEnableClientState( GL_NORMAL_ARRAY );
      glNormalPointer( GL_DOUBLE, 0, _normals->getDataPointer() );      
    }	
  	
    if( _textureCoords.valid() )
    {
	    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 3, GL_DOUBLE, 0, _textureCoords->getDataPointer() );
    }		  

    // Now dereference the arrays. 
	  for( size_t i=0; i < _primitiveSets.size(); ++i )
	  {	
		  glEnableClientState( GL_VERTEX_ARRAY );
		  _primitiveSets[i]->draw();
		  glDisableClientState( GL_VERTEX_ARRAY );		   
	  }

    if( _textureCoords.valid() )
    {
      glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    }

    if( _normals.valid() )
    {
      glDisableClientState( GL_NORMAL_ARRAY );
    }

    if( _colors.valid() )
    {
      glDisableClientState( GL_COLOR_ARRAY );
    }
  }
  else
  {
  } // if( !this->hasFastPath() ) 
}