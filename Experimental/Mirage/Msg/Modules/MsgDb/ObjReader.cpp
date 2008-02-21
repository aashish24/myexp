
#include "MsgDB/ObjReader.h"

#include "MsgCore/Node.h"
#include "MsgCore/Geode.h"
#include "MsgCore/Geometry.h"
#include "MsgCore/Array.h"

#include <fstream>

using namespace Msg::MsgDB;
using namespace Msg::MsgCore;

Node* ObjReader::readFile( std::istream& fin, const char *fileName, const bool& ignoreNormals  )
{
	const int LINE_SIZE = 4096;
	char line[LINE_SIZE];
	float x =0.0, y=0.0, z=0.0, w=0.0;
	std::vector< int >			normalIndices;

	SmartPtr< Geode >       geode	    = new Geode();
	SmartPtr< Geometry >    geom      = new Geometry();
	SmartPtr< Vec3Array >   vertices	= new Vec3Array();	
	SmartPtr< Vec3iArray >  vIndices	= new Vec3iArray();	
	SmartPtr< Vec3Array >   normals	  = new Vec3Array();	
	SmartPtr< Vec3iArray >  nIndices	= new Vec3iArray();	

  SmartPtr< Vec3Array >   texcoords = new Vec3Array();	
  SmartPtr< Vec3iArray >  tIndices	= new Vec3iArray();	
	
	while( !fin.eof() )
	{
		fin.getline( line, LINE_SIZE );
		
		if( strncmp( line, "v ", 2 ) == 0 )
		{
			// Read all the vertices here. 
			unsigned int fieldsRead = sscanf_s( line+2,"%f %f %f %f", &x, &y, &z, &w );
			if ( fieldsRead==1 ) vertices->push_back( Smtl::Vec3f( x,0.0f,0.0f ) );
			else if ( fieldsRead==2 ) vertices->push_back( Smtl::Vec3f( x,y,0.0f ) );
			else if ( fieldsRead==3 ) vertices->push_back( Smtl::Vec3f( x,y,z ) );
			else if ( fieldsRead>=4 ) vertices->push_back( Smtl::Vec3f( x/w,y/w,z/w ) );
		}	

		if( strncmp( line, "f ", 2 ) == 0 )
		{
			char* ptr = line+2;
			unsigned int vi=0, ti=0, ni=0;

			std::vector< unsigned int > vectorIndex;
			std::vector< unsigned int > normalIndex;
      std::vector< unsigned int > textureIndex;

			while( *ptr != 0 )
			{
				while ( *ptr == ' ' ) ++ptr;

				// Read all the indices here. 			
				if( sscanf_s( ptr, "%d/%d/%d", &vi, &ti, &ni ) == 3 ) 
				{
					vectorIndex.push_back ( vi - 1 );
          textureIndex.push_back( ti - 1 );
          normalIndex.push_back ( ni - 1 );
          
					//drawElem->push_back( 0 );
					//drawElem->push_back( 0 );
				}
				else if( sscanf_s( ptr, "%d//%d", &vi, &ni ) == 2 )
				{
					vectorIndex.push_back( vi - 1  );
					normalIndex.push_back( ni -1 );
					//drawElem->push_back( 0 );				
				}
				else if( sscanf_s( ptr, "%d/%d", &vi, &ti ) == 2 )
				{
					vectorIndex.push_back( vi - 1  );
					//drawElem->push_back( fy - 1 );
					//drawElem->push_back( 0 );				
				}
				else if( sscanf_s( ptr, "%d", &vi ) == 1)
				{
					vectorIndex.push_back( vi - 1 );
					//drawElem->push_back( 0 );
					//drawElem->push_back( 0 );
				}

				while( *ptr != ' ' && *ptr != 0 ) ++ptr;
			}

			vIndices->push_back( Vec3i( vectorIndex[0], vectorIndex[1], vectorIndex[2] ) );
			
			if( !normalIndex.empty() )
			{
				nIndices->push_back( Vec3i( normalIndex[0], normalIndex[1], normalIndex[2] ) );
			}

      if( !textureIndex.empty() )
      {
        tIndices->push_back( Vec3i( textureIndex[0], textureIndex[1], textureIndex[2] ) );
      }
		}

		if( strncmp( line, "vn ", 3 ) == 0 )
		{
			unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
			if( fieldsRead == 1 ) normals->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			else if( fieldsRead == 1 ) normals->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			else if( fieldsRead == 2 ) normals->push_back( Smtl::Vec3f( x, y, 0.0 ) );
			else if( fieldsRead == 3 ) normals->push_back( Smtl::Vec3f( x, y, z ) );
		}

    if( strncmp( line, "vt ", 3 ) == 0 )
		{
			unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
			if( fieldsRead == 1 )       texcoords->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			else if( fieldsRead == 1 )  texcoords->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			else if( fieldsRead == 2 )  texcoords->push_back( Smtl::Vec3f( x, y, 0.0 ) );
			else if( fieldsRead == 3 )  texcoords->push_back( Smtl::Vec3f( x, y, z ) );
		}
	}

	geom->setVertexArray( vertices.get() );
	geom->setVertexIndices( vIndices.get() );

	if( !normals->empty() && !ignoreNormals )
	{
		geom->setNormalArray( normals.get() );
	}
	else if( !ignoreNormals )
	{
		geom->generateNormals( Geometry::BIND_PER_VERTEX );
	}

	if( !nIndices->empty() )
	{
		geom->setNormalIndices( nIndices.get() );
	}

  if( !texcoords->empty() )
  {
    geom->setTexCoordArray( texcoords.get() );
  }

  if( !tIndices->empty() )
  {
    geom->setTextureIndices( tIndices.get() );
  }

	//geom->addPrimitiveSet( drawElem.get() );
	geode->addDrawable( geom.get() );

	return geode.release();
}

Node* ObjReader::readFile( std::istream& fin, const std::string &fileName, const bool& ignoreNormals )
{
	return readFile( fin, fileName.c_str() );
}
