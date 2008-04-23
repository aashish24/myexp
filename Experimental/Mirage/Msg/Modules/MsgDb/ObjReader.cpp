
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
  // Lets dereference all the indices except the vertex indices so that we can use
  // the fast path. 

	const int LINE_SIZE = 4096;
	
  char line[LINE_SIZE];
	
  float x =0.0, y=0.0, z=0.0, w=0.0;
	
  std::vector< int >			normalIndices;

  try
  {
	  /*SmartPtr< Geode >       geode	    = new Geode();
	  SmartPtr< Geometry >    geom      = new Geometry();

	  SmartPtr< Vec3Array >   vertices	= new Vec3Array();	
	  SmartPtr< Vec3iArray >  vIndices	= new Vec3iArray();	
	  
    SmartPtr< Vec3Array >   normals	  = new Vec3Array();	
	  SmartPtr< Vec3iArray >  nIndices	= new Vec3iArray();	

    SmartPtr< Vec3Array >   texcoords = new Vec3Array();	
    SmartPtr< Vec3iArray >  tIndices	= new Vec3iArray();	*/
  	
    // Its not efficinet to use int as default. 
    // @Todo: check the rrange of the data and then set the type. 
    //SmartPtr< DrawElementUInt > drawUInt( new DrawElementUInt( DrawElementUInt::TRIANGLES ) );

    SmartPtr< Model > model( new Model() );
  
	  while( !fin.eof() )
	  {
		  fin.getline( line, LINE_SIZE );
  		
		  if( strncmp( line, "v ", 2 ) == 0 )
		  {
			  // Read all the vertices here. 
			  unsigned int fieldsRead = sscanf_s( line+2,"%f %f %f %f", &x, &y, &z, &w );
        if ( fieldsRead==1 ) model->mVertices->push_back( Smtl::Vec3f( x,0.0f,0.0f ) );
			  else if ( fieldsRead==2 ) model->mVertices->push_back( Smtl::Vec3f( x,y,0.0f ) );
			  else if ( fieldsRead==3 ) model->mVertices->push_back( Smtl::Vec3f( x,y,z ) );
			  else if ( fieldsRead>=4 ) model->mVertices->push_back( Smtl::Vec3f( x/w,y/w,z/w ) );
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
            
            // Assuming that we have same value for three different indices and also 
            // that we have same number of values for each of them.           
            //drawUInt->push_back( vi - 1 );					
				  }
				  else if( sscanf_s( ptr, "%d//%d", &vi, &ni ) == 2 )
				  {
					  vectorIndex.push_back( vi - 1  );
					  normalIndex.push_back( ni -1 );
  					
            // Assuming that we have same value for three different indices and also 
            // that we have same number of values for each of them. 
            //drawUInt->push_back( vi - 1 );					
				  }
				  else if( sscanf_s( ptr, "%d/%d", &vi, &ti ) == 2 )
				  {
					  vectorIndex.push_back( vi - 1  );
            
            // Assuming that we have same value for three different indices and also 
            // that we have same number of values for each of them. 
            //drawUInt->push_back( vi - 1 );						
				  }
				  else if( sscanf_s( ptr, "%d", &vi ) == 1)
				  {
					  vectorIndex.push_back( vi - 1 );
  					
            // Assuming that we have same value for three different indices and also 
            // that we have same number of values for each of them. 
            //drawUInt->push_back( vi - 1 );					
				  }

				  while( *ptr != ' ' && *ptr != 0 ) ++ptr;
			  }

        model->mVertexIndices->push_back( Vec3i( vectorIndex[0], vectorIndex[1], vectorIndex[2] ) );
  			
			  if( !normalIndex.empty() )
			  {
          model->mNormalIndices->push_back( Vec3i( normalIndex[0], normalIndex[1], normalIndex[2] ) );
			  }

        if( !textureIndex.empty() )
        {
          model->mTexCoordIndices->push_back( Vec3i( textureIndex[0], textureIndex[1], textureIndex[2] ) );
        }
		  }

		  if( strncmp( line, "vn ", 3 ) == 0 )
		  {
			  unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
        if( fieldsRead == 1 ) model->mNormals->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 1 ) model->mNormals->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 2 ) model->mNormals->push_back( Smtl::Vec3f( x, y, 0.0 ) );
			  else if( fieldsRead == 3 ) model->mNormals->push_back( Smtl::Vec3f( x, y, z ) );
		  }

      if( strncmp( line, "vt ", 3 ) == 0 )
		  {
			  unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
        if( fieldsRead == 1 )       model->mTexCoords->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 1 )  model->mTexCoords->push_back( Smtl::Vec3f( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 2 )  model->mTexCoords->push_back( Smtl::Vec3f( x, y, 0.0 ) );
			  else if( fieldsRead == 3 )  model->mTexCoords->push_back( Smtl::Vec3f( x, y, z ) );
		  }
	  }      

    return this->convertDataIntoNode( model.get() );
	  //geom->setVertexArray( vertices.get() );
  	//
   // geom->setVertexIndices( vIndices.get() );

	  //if( !normals->empty() && !ignoreNormals )
	  //{
		 // geom->setNormalArray( normals.get() );
	  //}
	  //else if( !ignoreNormals )
	  //{
		 // geom->generateNormals( Geometry::BIND_PER_VERTEX );
	  //}

	  //if( !nIndices->empty() )
	  //{
		 // geom->setNormalIndices( nIndices.get() );
	  //}

   // if( !texcoords->empty() )
   // {
   //   geom->setTexCoordArray( texcoords.get() );
   // }

   // if( !tIndices->empty() )
   // {
   //   geom->setTextureIndices( tIndices.get() );
   // }
   // 
   // // For fast method. 
	  //geom->addPrimitiveSet( drawUInt.get() );
   // 
	  //geode->addDrawable( geom.get() );

	  //return geode.release();
  }
  catch( std::bad_alloc& e )
  {
    std::cerr << "Out of Memory error";
    throw;
  }
  catch( ... ) 
  {
    std::cerr <<  "Unknown error: "; 
    throw;
  }
}

Node* ObjReader::readFile( std::istream& fin, const std::string &fileName, const bool& ignoreNormals )
{
	return readFile( fin, fileName.c_str() );
}


Node* ObjReader::convertDataIntoNode( ObjReader::Model* model )
{
  // If NULL. 
  if( !model )
  {
    return 0x00;
  }

  try
  {
    // Create geode which will hold this geometry. 
    SmartPtr< Geode > geode = new Geode();

    // Node that actually holds the data. 
	  SmartPtr< Geometry > geom = new Geometry();

    // Place holders for vertex data. 
    SmartPtr< Vec3Array > normalArray( new Vec3Array( model->mVertices->size() ) );
    SmartPtr< Vec3Array > texCoordArray( new Vec3Array( model->mVertices->size() ) );
    SmartPtr< Vec3Array > colorArray( new Vec3Array( model->mVertices->size() ) );

    // Vertices are Vertex Indices are must in an obj. 
    if( model->mVertices->empty() || model->mVertexIndices->empty() )
    {
      return 0x00;
    }    

    // Set vertices and vertex index array. 
    geom->setVertexArray( model->mVertices.get() );
    geom->setVertexIndices( model->mVertexIndices.get() );

    for( size_t i=0; i < model->mVertexIndices->size(); ++i )
    {
      SmartPtr< DrawElementUInt > drawUInt( new DrawElementUInt( DrawElementUInt::TRIANGLES ) );
      drawUInt->push_back( model->mVertexIndices->at( i )[0] );
      drawUInt->push_back( model->mVertexIndices->at( i )[1] );
      drawUInt->push_back( model->mVertexIndices->at( i )[2] );
      geom->addPrimitiveSet( drawUInt.get() );

      // Find the index for the vectices. 
      int v1 = model->mVertexIndices->at( i )[0];
      int v2 = model->mVertexIndices->at( i )[1];
      int v3 = model->mVertexIndices->at( i )[2];

      // Now for these vertices set their normals. 
      if( model->mNormals.valid() && model->mNormalIndices.valid() )
      {
        normalArray->at(v1) = model->mNormals->at( model->mNormalIndices->at(i)[0] );
        normalArray->at(v2) = model->mNormals->at( model->mNormalIndices->at(i)[1] );
        normalArray->at(v3) = model->mNormals->at( model->mNormalIndices->at(i)[2] );        
      }
      else
      {
        normalArray  = 0x00;
      }

      // Now for these vertices set their texture coordinates. 
      if( model->mTexCoords.valid() && model->mTexCoordIndices.valid() )
      { 
        texCoordArray->at(v1) = model->mTexCoords->at( model->mTexCoordIndices->at(i)[0] );
        texCoordArray->at(v2) = model->mTexCoords->at( model->mTexCoordIndices->at(i)[1] );
        texCoordArray->at(v3) = model->mTexCoords->at( model->mTexCoordIndices->at(i)[2] );          
      }
      else
      {
        texCoordArray = 0x00;
      }

      // Now for these vertces set their colors. 
      if( model->mColors.valid() && model->mColorIndices.valid() )
      { 
        // @Todo: Implement this. 
      }
      else
      {
        colorArray = 0x00;
      }
    } // End for(... )    

    // Set normal array. 
    if( normalArray.valid() )
    {
      geom->setNormalArray( normalArray.get() );
    }

    // Set texture coordinate array. 
    if( texCoordArray.valid() )
    {
      geom->setTexCoordArray( texCoordArray.get() );
    }

    // Set normal index array. 
    if( !model->mNormalIndices->empty() )
    {
      geom->setNormalIndices( model->mNormalIndices.get() );
    }

    // Set texture coordinate index array. 
    if( !model->mTexCoordIndices->empty() )
    {
      geom->setTextureIndices( model->mTexCoordIndices.get() );
    }

    // Set color index array. 
    if( !model->mColorIndices->empty() )
    {
      // @Todo: Implement. 
      //geom->setColorArray( model->mColorIndices );
    }

    // Add geometry to this geode. 
    geode->addDrawable( geom.get() );

    // Return this newly created geode. 
    return geode.release();
  }
  catch( std::bad_alloc e )
  {
    std::cerr << "Error 4444963920: Out of memory error. " << std::endl;
    throw;
  }
  catch( ... )
  {
    std::cerr << "Error 3329170664: Unknown error. " << std::endl;
    throw;
  }
}
