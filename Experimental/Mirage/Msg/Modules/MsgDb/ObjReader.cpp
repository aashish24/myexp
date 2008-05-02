
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
	  SmartPtr< Geode >       geode	    = new Geode();
	  SmartPtr< Geometry >    geom      = new Geometry();

	  SmartPtr< Vec3Array >   vertices	= new Vec3Array();	
	  SmartPtr< Vec3iArray >  vIndices	= new Vec3iArray();	
	  
    SmartPtr< Vec3Array >   normals	  = new Vec3Array();	
	  SmartPtr< Vec3iArray >  nIndices	= new Vec3iArray();	

    SmartPtr< Vec3Array >   texcoords = new Vec3Array();	
    SmartPtr< Vec3iArray >  tIndices	= new Vec3iArray();	
  	
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
        if ( fieldsRead==1 ) model->mVertices->push_back( Smtl::Vec3d( x,0.0f,0.0f ) );
			  else if ( fieldsRead==2 ) model->mVertices->push_back( Smtl::Vec3d( x,y,0.0f ) );
			  else if ( fieldsRead==3 ) model->mVertices->push_back( Smtl::Vec3d( x,y,z ) );
			  else if ( fieldsRead>=4 ) model->mVertices->push_back( Smtl::Vec3d( x/w,y/w,z/w ) );
		  }	

		  if( strncmp( line, "f ", 2 ) == 0 )
		  {
			  char* ptr = line+2;
			  unsigned int vi=0, ti=0, ni=0;

			  std::vector< unsigned int > vectorIndex;
			  std::vector< unsigned int > normalIndex;
        std::vector< unsigned int > textureIndex;

        int counter = -1;

			  while( *ptr != 0 )
        {
				  while ( *ptr == ' ' )
          {
            ++ptr;
          }
				 
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

				  while( *ptr != ' ' && *ptr != 0 )
          {
            ++ptr;
          }
          
           ++counter;

			  } // while( *ptr != 0 )

        if( counter == 4 )
        {
          model->mVertexIndices->push_back( Vec3i( vectorIndex[0], vectorIndex[1], vectorIndex[2] ) );
    			model->mVertexIndices->push_back( Vec3i( vectorIndex[0], vectorIndex[2], vectorIndex[3] ) );

			    if( !normalIndex.empty() )
			    {
            model->mNormalIndices->push_back( Vec3i( normalIndex[0], normalIndex[1], normalIndex[2] ) );
            model->mNormalIndices->push_back( Vec3i( normalIndex[0], normalIndex[2], normalIndex[3] ) );
			    }

          if( !textureIndex.empty() )
          {
            model->mTexCoordIndices->push_back( Vec3i( textureIndex[0], textureIndex[1], textureIndex[2] ) );
            model->mTexCoordIndices->push_back( Vec3i( textureIndex[0], textureIndex[2], textureIndex[3] ) );
          }
        }
        else
        {
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

        counter = 0;
		  }

		  if( strncmp( line, "vn ", 3 ) == 0 )
		  {
			  unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
        if( fieldsRead == 1 ) model->mNormals->push_back( Smtl::Vec3d( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 1 ) model->mNormals->push_back( Smtl::Vec3d( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 2 ) model->mNormals->push_back( Smtl::Vec3d( x, y, 0.0 ) );
			  else if( fieldsRead == 3 ) model->mNormals->push_back( Smtl::Vec3d( x, y, z ) );
		  }

      if( strncmp( line, "vt ", 3 ) == 0 )
		  {
			  unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
        if( fieldsRead == 1 )       model->mTexCoords->push_back( Smtl::Vec3d( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 1 )  model->mTexCoords->push_back( Smtl::Vec3d( x, 0.0, 0.0 ) );
			  else if( fieldsRead == 2 )  model->mTexCoords->push_back( Smtl::Vec3d( x, y, 0.0 ) );
			  else if( fieldsRead == 3 )  model->mTexCoords->push_back( Smtl::Vec3d( x, y, 0.0 ) );
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
	  ////geom->addPrimitiveSet( drawUInt.get() );
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
    // First iterate thru the indices. 
    int count = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    mVertexData.resize( model->mVertices->size() );

    // Create geode which will hold this geometry. 
    SmartPtr< Geode > geode = new Geode();

    // Node that actually holds the data. 
	  SmartPtr< Geometry > geom = new Geometry();

    for( size_t i=0; i < model->mVertexIndices->size(); ++i )
    {
      SmartPtr< DrawElementUInt > drawUInt( new DrawElementUInt( DrawElementUInt::TRIANGLES ) );


      VertexData vData1;     
      VertexData vData2;
      VertexData vData3;

      int v1 = model->mVertexIndices->at( i )[0];
      int v2 = model->mVertexIndices->at( i )[1];
      int v3 = model->mVertexIndices->at( i )[2];
      
      vData1.mVertexIndex = v1;
      vData1.mNormalIndex = model->mNormalIndices->at( i )[0];
      //vData1.mColorIndex  = model->mColorIndices->at( k )[0];
      vData1.mTextureIndex = model->mTexCoordIndices->at( i )[0];

      j = k = l = count = i+1;

      vData2.mVertexIndex = v2;
      vData2.mNormalIndex = model->mNormalIndices->at( i )[1];
      //vData1.mColorIndex  = model->mColorIndices->at( k )[0];
      vData2.mTextureIndex = model->mTexCoordIndices->at( i )[1];

      j = k = l = count = i+2;

      vData3.mVertexIndex = v3;
      vData3.mNormalIndex = model->mNormalIndices->at( i )[2];
      //vData1.mColorIndex  = model->mColorIndices->at( k )[0];
      vData3.mTextureIndex = model->mTexCoordIndices->at( i )[2];      

      if( mVertexData.at( v1 ).mVertexIndex == -1 ) 
      {
        mVertexData.at( v1 ) = vData1;
        drawUInt->push_back( vData1.mVertexIndex );
      }
      else if( ( mVertexData.at( v1 ).mTextureIndex != vData1.mTextureIndex ) ||
            ( mVertexData.at( v1 ).mNormalIndex != vData1.mNormalIndex ) )
      {
        // Check if we have same texutre coordinate and normals.. else 
        // create new vertex and 
        // add texture coordinate 
        // add normal
        {         
          model->mVertices->push_back( model->mVertices->at( vData1.mVertexIndex ) );
          model->mNormals->push_back( model->mNormals->at( vData1.mNormalIndex ) );
          model->mTexCoords->push_back( model->mTexCoords->at( vData1.mTextureIndex ) );
          vData1.mVertexIndex = mVertexData.size();
          mVertexData.push_back( vData1 );
          drawUInt->push_back( vData1.mVertexIndex );
        }
      }
      else
      {
        drawUInt->push_back( vData1.mVertexIndex );
      }

      // If we dont have any allocated value at this position. 
      if( mVertexData.at( v2 ).mVertexIndex == -1 ) 
      {
        mVertexData.at( v2 ) = vData2;
        drawUInt->push_back( vData2.mVertexIndex );
      }
      // Else check if already have one data at this position but if the current and the one 
      // in the vertex data set are not same then create new vertex hence new vertex index
      // along with the normals, colors, texture coords etc. 
      // @Todo: We have very poor error checking. Need to fix that. 
      // @Todo: We are not updating indices for normals, colors etc which could cause some issues. 
      else if( ( mVertexData.at( v2 ).mTextureIndex != vData2.mTextureIndex ) ||
            ( mVertexData.at( v2 ).mNormalIndex != vData2.mNormalIndex ) )
      {        
        {          
          model->mVertices->push_back( model->mVertices->at( vData2.mVertexIndex ) );
          model->mNormals->push_back( model->mNormals->at( vData2.mNormalIndex ) );
          model->mTexCoords->push_back( model->mTexCoords->at( vData2.mTextureIndex ) );
          vData2.mVertexIndex = mVertexData.size();
          mVertexData.push_back( vData2 );         
          drawUInt->push_back(  vData2.mVertexIndex );
        }
      }
      else
      {
        drawUInt->push_back( vData2.mVertexIndex );
      }

      if( mVertexData.at( v3 ).mVertexIndex == -1 ) 
      {
        mVertexData.at( v3 ) = vData3;
        drawUInt->push_back( vData3.mVertexIndex );
      }
      else if( ( mVertexData.at( v3 ).mTextureIndex != vData3.mTextureIndex ) ||
            ( mVertexData.at( v3 ).mNormalIndex != vData3.mNormalIndex ) )
      {        
        model->mVertices->push_back( model->mVertices->at( vData3.mVertexIndex ) );
        model->mNormals->push_back( model->mNormals->at( vData3.mNormalIndex ) );
        model->mTexCoords->push_back( model->mTexCoords->at( vData3.mTextureIndex ) );
        vData3.mVertexIndex = mVertexData.size();
        mVertexData.push_back( vData3 );       
        drawUInt->push_back(  vData3.mVertexIndex );
      }
      else
      {
        drawUInt->push_back( vData3.mVertexIndex );
      }      

      geom->addPrimitiveSet( drawUInt.get() );
    } // for( ... )

   //  // Create geode which will hold this geometry. 
   // SmartPtr< Geode > geode = new Geode();

   // // Node that actually holds the data. 
	  //SmartPtr< Geometry > geom = new Geometry();

    size_t sizeArray = mVertexData.size();

    SmartPtr< Vec3Array > vertexArray( new Vec3Array( sizeArray ) );
    SmartPtr< Vec3Array > normalArray( new Vec3Array( sizeArray ) );
    SmartPtr< Vec3Array > textureArray( new Vec3Array( sizeArray ) );
    SmartPtr< Vec3Array > colorArray( new Vec3Array( sizeArray ) );

    

   for( size_t i=0; i < mVertexData.size(); ++i )
   {
     vertexArray->at( i ) = ( model->mVertices->at( mVertexData.at( i ).mVertexIndex ) );
     normalArray->at( i ) = ( model->mNormals->at( mVertexData.at( i ).mNormalIndex ) );
     textureArray->at( i ) = ( model->mTexCoords->at( mVertexData.at( i ).mTextureIndex ) );     
   }
   
   Geometry::PrimitiveSets primSets = geom->getPrimitiveSets();
   SmartPtr< Vec3iArray > vertexIndicesArray( new Vec3iArray() );

   std::fstream; 
   std::ostringstream;

   std::ofstream file;
   file.open( "out.txt" ); 
   
   if( !file.is_open() )
   {
     std::cout << "Bad file: " << std::endl;
   }

   for( size_t i=0; i < primSets.size(); ++i )
   {     
    Vec3i vector;
    DrawElementUInt* elem = ( dynamic_cast< DrawElementUInt* > ( primSets[i].get() ) );
    if( elem ) 
    {
      vector[0] = elem->at( 0 );
      vector[1] = elem->at( 1 );
      vector[2] = elem->at( 2 );

      file << vector[0] << " " << vector[1] << " " << vector[2] << std::endl;
    }

    vertexIndicesArray->push_back(  vector );
   }

   for( size_t i=0; i < vertexArray->size(); ++i )
   {
     Vec3d vertex = vertexArray->at( i );

     file << vertex[0] << " " << vertex[1] << " " << vertex[2] << std::endl;     
   }

   file.close();
    

#if 0

    // Create geode which will hold this geometry. 
    SmartPtr< Geode > geode = new Geode();

    // Node that actually holds the data. 
	  SmartPtr< Geometry > geom = new Geometry();

    // Place holders for vertex data. 
    SmartPtr< Vec3Array > vertexArray( new Vec3Array( model->mVertices->size() ) );
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
    geom->setTexCoordArray( model->mTexCoords.get() );
    geom->setTextureIndices( model->mTexCoordIndices.get() ); 
    geom->setNormalArray( model->mNormals.get() );
    geom->setNormalIndices( model->mNormalIndices.get() ); 
/*
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

      if( model->mVertices.valid() )
      {
        vertexArray->at(v1) = model->mVertices->at( model->mVertexIndices->at(i)[0] );
        vertexArray->at(v2) = model->mVertices->at( model->mVertexIndices->at(i)[1] );
        vertexArray->at(v3) = model->mVertices->at( model->mVertexIndices->at(i)[2] );        
      }
      else
      {
        vertexArray = 0x00;
      }

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
*/
#endif // 
     
    if( vertexArray.valid() )
    {
      geom->setVertexArray( vertexArray.get() );
    }

    if( vertexIndicesArray.valid() )
    {
      geom->setVertexIndices( vertexIndicesArray.get() );
    }

    // Set normal array. 
    if( normalArray.valid() )
    {
      geom->setNormalArray( normalArray.get() );
    }

    // Set texture coordinate array. 
    if( textureArray.valid() )
    {
      geom->setTexCoordArray( textureArray.get() );
    }

    //// Set normal index array. 
    if( !model->mNormalIndices->empty() )
    {
      geom->setNormalIndices( model->mNormalIndices.get() );
    }

    //// Set texture coordinate index array. 
    if( !model->mTexCoordIndices->empty() )
    {
      geom->setTextureIndices( model->mTexCoordIndices.get() );
    }

    //// Set color index array. 
    //if( !model->mColorIndices->empty() )
    //{
    //  // @Todo: Implement. 
    //  //geom->setColorArray( model->mColorIndices );
    //}

    // Add geometry to this geode. 
    geode->addDrawable( geom.get() );

    // Return this newly created geode. 
    return geode.release();
//#endif // #if 0
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
