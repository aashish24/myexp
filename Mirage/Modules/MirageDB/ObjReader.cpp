
#include "MirageDB/ObjReader.h"

#include "MirageCore/Node.h"
#include "MirageCore/Geode.h"
#include "MirageCore/Geometry.h"
#include "MirageCore/Array.h"

#include "MirageMath/Vec.h"

#include <fstream>

using namespace Mirage::MirageCore;

namespace Mirage
{
  namespace MirageDB
  {
    Node* ObjReader::readFile( std::istream& fin, const std::string& fileName )
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
            if ( fieldsRead==1 ) model->_vertices->push_back( MirageMath::Vec3d( x,0.0f,0.0f ) );
			      else if ( fieldsRead==2 ) model->_vertices->push_back( MirageMath::Vec3d( x,y,0.0f ) );
			      else if ( fieldsRead==3 ) model->_vertices->push_back( MirageMath::Vec3d( x,y,z ) );
			      else if ( fieldsRead>=4 ) model->_vertices->push_back( MirageMath::Vec3d( x/w,y/w,z/w ) );
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
                if( vi != ti || vi != ni )
                {
                  _useFastPath = false;
                }

					      vectorIndex.push_back ( vi - 1 );
                textureIndex.push_back( ti - 1 );
                normalIndex.push_back ( ni - 1 );
                
                // Assuming that we have same value for three different indices and also 
                // that we have same number of values for each of them.           
                //drawUInt->push_back( vi - 1 );					
				      }
				      else if( sscanf_s( ptr, "%d//%d", &vi, &ni ) == 2 )
				      {
                if( vi != ni )
                {
                  _useFastPath = false;
                }

					      vectorIndex.push_back( vi - 1  );
					      normalIndex.push_back( ni -1 );
      					
                // Assuming that we have same value for three different indices and also 
                // that we have same number of values for each of them. 
                //drawUInt->push_back( vi - 1 );					
				      }
				      else if( sscanf_s( ptr, "%d/%d", &vi, &ti ) == 2 )
				      {
                if( vi != ti )
                {
                  _useFastPath = false;
                }

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
              model->_vertexIndices->push_back( MirageMath::Vec3i( vectorIndex[0], vectorIndex[1], vectorIndex[2] ) );
    			    model->_vertexIndices->push_back( MirageMath::Vec3i( vectorIndex[0], vectorIndex[2], vectorIndex[3] ) );

			        if( !normalIndex.empty() )
			        {
                model->_normalIndices->push_back( MirageMath::Vec3i( normalIndex[0], normalIndex[1], normalIndex[2] ) );
                model->_normalIndices->push_back( MirageMath::Vec3i( normalIndex[0], normalIndex[2], normalIndex[3] ) );
			        }

              if( !textureIndex.empty() )
              {
                model->_texCoordIndices->push_back( MirageMath::Vec3i( textureIndex[0], textureIndex[1], textureIndex[2] ) );
                model->_texCoordIndices->push_back( MirageMath::Vec3i( textureIndex[0], textureIndex[2], textureIndex[3] ) );
              }
            }
            else
            {
              model->_vertexIndices->push_back( MirageMath::Vec3i( vectorIndex[0], vectorIndex[1], vectorIndex[2] ) );
        			
			        if( !normalIndex.empty() )
			        {
                model->_normalIndices->push_back( MirageMath::Vec3i( normalIndex[0], normalIndex[1], normalIndex[2] ) );
			        }

              if( !textureIndex.empty() )
              {
                model->_texCoordIndices->push_back( MirageMath::Vec3i( textureIndex[0], textureIndex[1], textureIndex[2] ) );
              }
            }        

            counter = 0;
		      }

		      if( strncmp( line, "vn ", 3 ) == 0 )
		      {
			      unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
            if( fieldsRead == 1 ) model->_normals->push_back( MirageMath::Vec3d( x, 0.0, 0.0 ) );
			      else if( fieldsRead == 1 ) model->_normals->push_back( MirageMath::Vec3d( x, 0.0, 0.0 ) );
			      else if( fieldsRead == 2 ) model->_normals->push_back( MirageMath::Vec3d( x, y, 0.0 ) );
			      else if( fieldsRead == 3 ) model->_normals->push_back( MirageMath::Vec3d( x, y, z ) );
		      }

          if( strncmp( line, "vt ", 3 ) == 0 )
		      {
			      unsigned int fieldsRead = sscanf_s( line+3 , "%f %f %f %f", &x, &y, &z, &w );
            if( fieldsRead == 1 )       model->_textureCoords->push_back( MirageMath::Vec3d( x, 0.0, 0.0 ) );
			      else if( fieldsRead == 1 )  model->_textureCoords->push_back( MirageMath::Vec3d( x, 0.0, 0.0 ) );
			      else if( fieldsRead == 2 )  model->_textureCoords->push_back( MirageMath::Vec3d( x, y, 0.0 ) );
			      else if( fieldsRead == 3 )  model->_textureCoords->push_back( MirageMath::Vec3d( x, y, 0.0 ) );
		      }
	      }      

        model->_useFastPath = _useFastPath;

        return this->convertDataIntoNode( model.get() );
	      //geom->vertexArray( vertices.get() );
  	    //
       // geom->vertexIndices( vIndices.get() );

	      //if( !normals->empty() && !ignoreNormals )
	      //{
		     // geom->normalArray( normals.get() );
	      //}
	      //else if( !ignoreNormals )
	      //{
		     // geom->generateNormals( Geometry::BIND_PER_VERTEX );
	      //}

	      //if( !nIndices->empty() )
	      //{
		     // geom->normalIndices( nIndices.get() );
	      //}

       // if( !texcoords->empty() )
       // {
       //   geom->textureCoordArray( texcoords.get() );
       // }

       // if( !tIndices->empty() )
       // {
       //   geom->textureCoordIndices( tIndices.get() );
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

        if( false )
        {
          // First iterate thru the indices. 
          int count = 0;
          int j = 0;
          int k = 0;
          int l = 0;

          _vertexData.resize( model->_vertices->size() );          

          // Lets create a map of vertex index to VertexData.
          // We need to have this as we need to loop thru all the 
          // VertexData which has the same vertex index and if we find one 
          // which has the same texture index then we wont push a new vertex 
          // but rather will use the vertex index of that VertexData. 
          std::map< int, std::vector< int > > vertexIndexVertexDataTable;

          for( size_t i=0; i < model->_vertexIndices->size(); ++i )
          {
            SmartPtr< DrawElementUInt > drawUInt( new DrawElementUInt( DrawElementUInt::TRIANGLES ) );


            VertexData vData1;     
            VertexData vData2;
            VertexData vData3;

            int v1 = model->_vertexIndices->at( i )[0];
            int v2 = model->_vertexIndices->at( i )[1];
            int v3 = model->_vertexIndices->at( i )[2];
            
            vData1._vertexIndex = v1;
            vData1._normalIndex = model->_normalIndices->at( i )[0];
            //vData1._colorIndex  = model->_colorIndices->at( k )[0];
            vData1._textureIndex = model->_texCoordIndices->at( i )[0];

            j = k = l = count = i+1;

            vData2._vertexIndex = v2;
            vData2._normalIndex = model->_normalIndices->at( i )[1];
            //vData1._colorIndex  = model->_colorIndices->at( k )[0];
            vData2._textureIndex = model->_texCoordIndices->at( i )[1];

            j = k = l = count = i+2;

            vData3._vertexIndex = v3;
            vData3._normalIndex = model->_normalIndices->at( i )[2];
            //vData1._colorIndex  = model->_colorIndices->at( k )[0];
            vData3._textureIndex = model->_texCoordIndices->at( i )[2];      

            if( _vertexData.at( v1 )._vertexIndex == -1 ) 
            {
              _vertexData.at( v1 ) = vData1;
              vertexIndexVertexDataTable[v1].push_back( v1 );
              drawUInt->push_back( vData1._vertexIndex );
            }
            else if( _vertexData.at( v1 )._textureIndex == vData1._textureIndex )
            {
              drawUInt->push_back( vData1._vertexIndex );
            }
            else
            {        
              bool found = false;
              std::map< int, std::vector< int > >::iterator itr = vertexIndexVertexDataTable.find( v1 );
              int size = itr->second.size();

              //for( itr; itr != vertexIndexVertexDataTable.end(); ++itr )
              for( size_t i=0; i < size; ++i )
              {              
                if( _vertexData.at( itr->second[i] )._textureIndex == vData1._textureIndex )
                { 
                  vData1._vertexIndex = _vertexData.at( itr->second[i] )._vertexIndex;
                  drawUInt->push_back( vData1._vertexIndex );
                  found = true;
                }
              }  

              if( !found ) 
              {
                model->_vertices->push_back( model->_vertices->at( vData1._vertexIndex ) );
                model->_normals->push_back( model->_normals->at( vData1._normalIndex ) );
                model->_textureCoords->push_back( model->_textureCoords->at( vData1._textureIndex ) );
                vData1._vertexIndex = _vertexData.size();
                _vertexData.push_back( vData1 );
                vertexIndexVertexDataTable[v1].push_back( vData1._vertexIndex );
                drawUInt->push_back( vData1._vertexIndex );        
              }
            }

            // @Todo: Write the algorithm here. 
            if( _vertexData.at( v2 )._vertexIndex == -1 ) 
            {
              _vertexData.at( v2 ) = vData2;
              vertexIndexVertexDataTable[v2].push_back( v2 );
              drawUInt->push_back( vData2._vertexIndex );
            }
            else if( _vertexData.at( v2 )._textureIndex == vData2._textureIndex )
            {
              drawUInt->push_back( vData2._vertexIndex );
            }
            else
            {        
              bool found = false;
              std::map< int, std::vector< int > >::iterator itr = vertexIndexVertexDataTable.find( v2 );
              size_t size = itr->second.size();
              
              for( size_t i=0; i < size; ++i )
              {
                //std::cout << "Test: " << _vertexData.at( itr->second[i] )._textureIndex << " "  
                //          << vData2._textureIndex << std::endl;
                if( _vertexData.at( itr->second[i] )._textureIndex == vData2._textureIndex )
                {            
                  vData2._vertexIndex = _vertexData.at( itr->second[i] )._vertexIndex;
                  drawUInt->push_back( vData2._vertexIndex );
                  found = true;
                }
              } 
              if( !found ) 
              {
                model->_vertices->push_back( model->_vertices->at( vData2._vertexIndex ) );
                model->_normals->push_back( model->_normals->at( vData2._normalIndex ) );
                model->_textureCoords->push_back( model->_textureCoords->at( vData2._textureIndex ) );
                vData2._vertexIndex = _vertexData.size();
                _vertexData.push_back( vData2 );
                vertexIndexVertexDataTable[v2].push_back( vData2._vertexIndex );
                drawUInt->push_back( vData2._vertexIndex );        
              }
            }

            if( _vertexData.at( v3 )._vertexIndex == -1 ) 
            {
              _vertexData.at( v3 ) = vData3;
              vertexIndexVertexDataTable[v3].push_back( v3 );
              drawUInt->push_back( vData3._vertexIndex );
            }
            else if( _vertexData.at( v3 )._textureIndex == vData3._textureIndex )
            {
              drawUInt->push_back( vData3._vertexIndex );
            }
            else
            {        
              bool found = false;
              std::map< int, std::vector< int > >::iterator itr = vertexIndexVertexDataTable.find( v3 );
              size_t size = itr->second.size();
              
              for( size_t i=0; i < size; ++i )
              {
                //std::cout << "Test: " << _vertexData.at( itr->second[i] )._textureIndex << " "  
                //          << vData3._textureIndex << std::endl;
                if( _vertexData.at( itr->second[i] )._textureIndex == vData1._textureIndex )
                {            
                  vData3._vertexIndex = _vertexData.at( itr->second[i] )._vertexIndex;
                  drawUInt->push_back( vData3._vertexIndex );
                  found = true;
                }
              } 
              if( !found ) 
              {
                model->_vertices->push_back( model->_vertices->at( vData3._vertexIndex ) );
                model->_normals->push_back( model->_normals->at( vData3._normalIndex ) );
                model->_textureCoords->push_back( model->_textureCoords->at( vData3._textureIndex ) );
                vData3._vertexIndex = _vertexData.size();
                _vertexData.push_back( vData3 );
                vertexIndexVertexDataTable[v3].push_back( vData3._vertexIndex );
                drawUInt->push_back( vData3._vertexIndex );        
              }
            }
                

            geom->addPrimitiveSet( drawUInt.get() );
          } // for( ... )
       
          size_t sizeArray = _vertexData.size();

          SmartPtr< Vec3Array > vertexArray( new Vec3Array( sizeArray ) );
          SmartPtr< Vec3Array > normalArray( new Vec3Array( sizeArray ) );
          SmartPtr< Vec3Array > textureArray( new Vec3Array( sizeArray ) );
          SmartPtr< Vec3Array > colorArray( new Vec3Array( sizeArray ) );    

          for( size_t i=0; i < _vertexData.size(); ++i )
          {
            vertexArray->at( i ) = ( model->_vertices->at( _vertexData.at( i )._vertexIndex ) );
            normalArray->at( i ) = ( model->_normals->at( _vertexData.at( i )._normalIndex ) );
            textureArray->at( i ) = ( model->_textureCoords->at( _vertexData.at( i )._textureIndex ) );     
          }
         
          Geometry::PrimitiveSets primSets = geom->primitiveSets();
          SmartPtr< Vec3iArray > vertexIndicesArray( new Vec3iArray() );

          for( size_t i=0; i < primSets.size(); ++i )
          {     
            MirageMath::Vec3i vector;
            DrawElementUInt* elem = ( dynamic_cast< DrawElementUInt* > ( primSets[i].get() ) );
            if( elem ) 
            {
              vector[0] = elem->at( 0 );
              vector[1] = elem->at( 1 );
              vector[2] = elem->at( 2 );
            }
            vertexIndicesArray->push_back(  vector );
          }

               
          if( vertexArray.valid() )
          {
            geom->vertexArray( vertexArray.get() );
          }

          if( vertexIndicesArray.valid() )
          {
            geom->vertexIndices( vertexIndicesArray.get() );
          }

          // Set normal array. 
          if( normalArray.valid() )
          {
            geom->normalArray( normalArray.get() );
          }

          // Set texture coordinate array. 
          if( textureArray.valid() )
          {
            geom->textureCoordArray( textureArray.get() );
          }

          //// Set normal index array. 
          if( !model->_normalIndices->empty() )
          {
            geom->normalIndices( model->_normalIndices.get() );
          }

          //// Set texture coordinate index array. 
          if( !model->_texCoordIndices->empty() )
          {
            geom->textureCoordIndices( model->_texCoordIndices.get() );
          }
        }        
        else 
        { 
          // Still we would like to duplicate vertices for which we have more than one texture 
          // coordinates. 
          geom->useFastPath( _useFastPath );

          // Place holders for vertex data. 
          /*SmartPtr< Vec3Array > vertexArray( new Vec3Array( model->_vertices->size() ) );
          SmartPtr< Vec3Array > normalArray( new Vec3Array( model->_vertices->size() ) );
          SmartPtr< Vec3Array > textureCoordArray( new Vec3Array( model->_vertices->size() ) );
          SmartPtr< Vec3Array > colorArray( new Vec3Array( model->_vertices->size() ) );*/

          // Vertices are Vertex Indices are must in an obj. 
          if( model->_vertices->empty() || model->_vertexIndices->empty() )
          {
            return 0x00;
          }    

          // Set vertices and vertex index array. 
          geom->vertexArray( model->_vertices.get() );
          geom->vertexIndices( model->_vertexIndices.get() );    
          geom->textureCoordArray( model->_textureCoords.get() );
          geom->textureCoordIndices( model->_texCoordIndices.get() ); 
          geom->normalArray( model->_normals.get() );
          geom->normalIndices( model->_normalIndices.get() );
        
          /*
          for( size_t i=0; i < model->_vertexIndices->size(); ++i )
          {
            SmartPtr< DrawElementUInt > drawUInt( new DrawElementUInt( DrawElementUInt::TRIANGLES ) );
            drawUInt->push_back( model->_vertexIndices->at( i )[0] );
            drawUInt->push_back( model->_vertexIndices->at( i )[1] );
            drawUInt->push_back( model->_vertexIndices->at( i )[2] );
            geom->addPrimitiveSet( drawUInt.get() );

            // Find the index for the vectices. 
            int v1 = model->_vertexIndices->at( i )[0];
            int v2 = model->_vertexIndices->at( i )[1];
            int v3 = model->_vertexIndices->at( i )[2];

            if( model->_vertices.valid() )
            {
              vertexArray->at(v1) = model->_vertices->at( model->_vertexIndices->at(i)[0] );
              vertexArray->at(v2) = model->_vertices->at( model->_vertexIndices->at(i)[1] );
              vertexArray->at(v3) = model->_vertices->at( model->_vertexIndices->at(i)[2] );        
            }
            else
            {
              vertexArray = 0x00;
            }

            // Now for these vertices set their normals. 
            if( model->_normals.valid() && model->_normalIndices.valid() )
            {
              normalArray->at(v1) = model->_normals->at( model->_normalIndices->at(i)[0] );
              normalArray->at(v2) = model->_normals->at( model->_normalIndices->at(i)[1] );
              normalArray->at(v3) = model->_normals->at( model->_normalIndices->at(i)[2] );        
            }
            else
            {
              normalArray  = 0x00;
            }

            // Now for these vertices set their texture coordinates. 
            if( model->_textureCoords.valid() && model->_texCoordIndices.valid() )
            { 
              textureCoordArray->at(v1) = model->_textureCoords->at( model->_texCoordIndices->at(i)[0] );
              textureCoordArray->at(v2) = model->_textureCoords->at( model->_texCoordIndices->at(i)[1] );
              textureCoordArray->at(v3) = model->_textureCoords->at( model->_texCoordIndices->at(i)[2] );          
            }
            else
            {
              textureCoordArray = 0x00;
            }

            // Now for these vertces set their colors. 
            if( model->_colors.valid() && model->_colorIndices.valid() )
            { 
              // @Todo: Implement this. 
            }
            else
            {
              colorArray = 0x00;
            }
          } // End for(... )            
          */    

          //// Set color index array. 
          //if( !model->_colorIndices->empty() )
          //{
          //  // @Todo: Implement. 
          //  //geom->colorArray( model->_colorIndices );
          //}

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
  }
}
