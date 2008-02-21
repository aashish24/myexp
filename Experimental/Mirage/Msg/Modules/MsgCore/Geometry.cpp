
#include "MsgCore/Geometry.h"
#include "MsgCore/PrimitiveSet.h"

#include <map>
#include <vector>

using namespace Msg::MsgCore;

Geometry::Geometry() :
	mAttrBinding( Geometry::BIND_PER_VERTEX )
{
}

Geometry::Geometry( const Geometry& geom ) :
	mAttrBinding( Geometry::BIND_PER_VERTEX )
{
}

Vec3Array* Geometry::getVertexArray()
{	
	return mVertices.get();
}

void Geometry::setVertexArray( Vec3Array* vArray )
{
	mVertices = vArray;
}

Vec3Array* Geometry::getNormalArray()
{
	return mNormals.get();
}

void Geometry::setNormalArray(  Vec3Array* nArray )
{
	mNormals = nArray;
}

Vec3Array* Geometry::getTexCoordArray()
{
	return mTexCoords.get();
}

void Geometry::setTexCoordArray( Vec3Array* texCoordArray )
{
	mTexCoords = texCoordArray;
}
				
Vec4Array* Geometry::getColorArray()
{
	return mColors.get();
}

void Geometry::setColorArray( Vec4Array* colorArray )
{
	mColors = colorArray;
}

Geometry::AttributeBinding Geometry::getAttrBinding()
{
	return mAttrBinding;
}

void Geometry::setAttrBinding( const Geometry::AttributeBinding& attrBinding )
{
	mAttrBinding = attrBinding;
}

Vec3iArray* Geometry::getVertexIndices()
{
	return mVertexIndices.get();
}

void Geometry::setVertexIndices( Vec3iArray* viArray )
{
	mVertexIndices = viArray;
}

Vec3iArray* Geometry::getNormalIndices()
{
	return mNormalIndices.get();
}

void Geometry::setNormalIndices( Vec3iArray* niArray )
{
	mNormalIndices = niArray;
}

Vec3iArray* Geometry::getTextureIndices()
{
  return mTextureIndices.get();
}

void Geometry::setTextureIndices( Vec3iArray* niArray )
{
  mTextureIndices = niArray;
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

	for( size_t i=0; i < mVertexIndices->size(); ++i )
	{
		Vec3f vec1 = mVertices->at( mVertexIndices->at(i)[1] ) - mVertices->at( mVertexIndices->at(i)[0] );
		Vec3f vec2 = mVertices->at( mVertexIndices->at(i)[2] ) - mVertices->at( mVertexIndices->at(i)[0] );
		Vec3f normal = vec1.cross( vec2 );		
		normal.normalize();
		normals->push_back( normal );
		nIndices->push_back( Vec3i( i, 0, 0 ) );
	}	

	if( attrBinding == Geometry::BIND_PER_PRIMITIVE )
	{
		mNormals = normals.get();
		mNormalIndices = nIndices.get();
	}
	else if( attrBinding == Geometry::BIND_PER_VERTEX )
	{
		typedef std::map< int, std::vector< int > >  MapVertexIDToPrimitiveID;

		MapVertexIDToPrimitiveID mapVertexIDToPrimitiveID;
		std::vector< int > PrimitiveIDs;

		// Point each VertextID to a vector of PrimitiveIDs. 
		for( size_t i=0; i < mVertexIndices->size(); ++i )
		{
			mapVertexIDToPrimitiveID[ mVertexIndices->at(i)[0] ] = PrimitiveIDs;
			mapVertexIDToPrimitiveID[ mVertexIndices->at(i)[1] ] = PrimitiveIDs;
			mapVertexIDToPrimitiveID[ mVertexIndices->at(i)[2] ] = PrimitiveIDs;
		}

		// Now fill the this map. 
		for( size_t i=0; i < mVertexIndices->size(); ++i )
		{
			mapVertexIDToPrimitiveID[ mVertexIndices->at(i)[0] ].push_back( i );
			mapVertexIDToPrimitiveID[ mVertexIndices->at(i)[1] ].push_back( i );
			mapVertexIDToPrimitiveID[ mVertexIndices->at(i)[2] ].push_back( i );
		}
		
		// Now calculate per vertex normals. 
		SmartPtr< Vec3Array >  perVertexNormals = new Vec3Array();		

		MapVertexIDToPrimitiveID::iterator itr = mapVertexIDToPrimitiveID.begin();		
		for( itr; itr != mapVertexIDToPrimitiveID.end(); ++itr )
		{
			Vec3f vertextNormal;
			for( size_t i = 0; i < itr->second.size(); ++i )
			{				
				vertextNormal = vertextNormal + normals->at( ( itr->second.at( i ) ) );
			}
			vertextNormal.normalize();
			perVertexNormals->push_back( vertextNormal );
		}		

		mNormals = perVertexNormals.get();
	}

	std::cout << "Finished creating normals with binding " << bindingType << std::endl;
}


void Geometry::addPrimitiveSet( PrimitiveSet* primitiveSet )
{
	mPrimitiveSets.push_back( primitiveSet );
}

void Geometry::drawImplementation() const
{
	glBegin( GL_TRIANGLES );
	for( size_t i=0; i < mVertexIndices->size(); ++ i )
	{
		if( mAttrBinding == Geometry::BIND_PER_PRIMITIVE )
		{
			if( mNormals.valid())
			{
				glNormal3f( mNormals->at( mNormalIndices->at(i)[0] )[0],
							mNormals->at( mNormalIndices->at(i)[0] )[1],
							mNormals->at( mNormalIndices->at(i)[0] )[2] );	  
			}

			glVertex3f( mVertices->at( mVertexIndices->at(i)[0] )[0], 	
						mVertices->at( mVertexIndices->at(i)[0] )[1], 
						mVertices->at( mVertexIndices->at(i)[0] )[2] );

			glVertex3f( mVertices->at( mVertexIndices->at(i)[1] )[0], 	
						mVertices->at( mVertexIndices->at(i)[1] )[1], 
						mVertices->at( mVertexIndices->at(i)[1] )[2] );

			glVertex3f( mVertices->at( mVertexIndices->at(i)[2] )[0], 	
						mVertices->at( mVertexIndices->at(i)[2] )[1], 
						mVertices->at( mVertexIndices->at(i)[2] )[2] );
		}
		else if( mAttrBinding == Geometry::BIND_PER_VERTEX )
		{
			
      glNormal3f( mNormals->at( mNormalIndices->at(i)[0] )[0],
						      mNormals->at( mNormalIndices->at(i)[0] )[1],
						      mNormals->at( mNormalIndices->at(i)[0] )[2] );

      glTexCoord3f( mTexCoords->at( mTextureIndices->at(i)[0] )[0],
						        mTexCoords->at( mTextureIndices->at(i)[0] )[1],
						        mTexCoords->at( mTextureIndices->at(i)[0] )[2] );

			glVertex3f( mVertices->at( mVertexIndices->at(i)[0] )[0], 	
						      mVertices->at( mVertexIndices->at(i)[0] )[1], 
						      mVertices->at( mVertexIndices->at(i)[0] )[2] );

			glNormal3f( mNormals->at( mNormalIndices->at(i)[1] )[0],
						      mNormals->at( mNormalIndices->at(i)[1] )[1],
						      mNormals->at( mNormalIndices->at(i)[1] )[2] );

      glTexCoord3f( mTexCoords->at( mTextureIndices->at(i)[1] )[0],
						        mTexCoords->at( mTextureIndices->at(i)[1] )[1],
						        mTexCoords->at( mTextureIndices->at(i)[1] )[2] );

			glVertex3f( mVertices->at( mVertexIndices->at(i)[1] )[0], 	
						      mVertices->at( mVertexIndices->at(i)[1] )[1], 
						      mVertices->at( mVertexIndices->at(i)[1] )[2] );

			glNormal3f( mNormals->at( mNormalIndices->at(i)[2] )[0],
						      mNormals->at( mNormalIndices->at(i)[2] )[1],
						      mNormals->at( mNormalIndices->at(i)[2] )[2] );

      glTexCoord3f( mTexCoords->at( mTextureIndices->at(i)[2] )[0],
						        mTexCoords->at( mTextureIndices->at(i)[2] )[1],
						        mTexCoords->at( mTextureIndices->at(i)[2] )[2] );

			glVertex3f( mVertices->at( mVertexIndices->at(i)[2] )[0], 	
						      mVertices->at( mVertexIndices->at(i)[2] )[1], 
						      mVertices->at( mVertexIndices->at(i)[2] )[2] );
		}
	}
	glEnd();


	/*
	for( size_t i=0; i < mPrimitiveSets.size(); ++i )
	{			
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glVertexPointer( 3, GL_FLOAT, 0, mVertices->getDataPointer() );

		if( mColors.valid() )
		{
			glEnableClientState( GL_COLOR_ARRAY );
			glColorPointer( 4, GL_FLOAT, 0, mColors->getDataPointer() );
		}

		if( mNormals.valid() )
		{
			glEnableClientState( GL_NORMAL_ARRAY );
			glNormalPointer( GL_FLOAT, 0, mNormals->getDataPointer() );
		}	
		
		if( mTexCoords.valid() )
		{
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glTexCoordPointer( 3, GL_FLOAT, 0, mTexCoords->getDataPointer() );
		}

		glEnableClientState( GL_VERTEX_ARRAY );
		mPrimitiveSets[i]->draw();
		glDisableClientState( GL_VERTEX_ARRAY );

		glPopAttrib();	
	}
	*/
}