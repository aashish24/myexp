
#include "MsgUtil/GeometryFuncs.h"

#include "MsgCore/Geometry.h"
#include "MsgCore/Array.h"

void Msg::MsgUtil::GeometryFuncs::generateNormals( Msg::MsgCore::Geometry* geom )
{
}


void Msg::MsgUtil::GeometryFuncs::generateTBNs( Msg::MsgCore::Geometry* geom )
{
  try
  {
    // Query data from the geometry node. 
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array >   vertices  = geom->vertexArray();
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3iArray >  indices   = geom->vertexIndices();
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array >   texcoords = geom->textureCoordArray();
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array >   normals   = geom->normalArray();

    // If geometey has missing vertices, texture coordinates or normals we cannot 
    // calculate T B N vectors. 
    if( !vertices.valid() || !texcoords.valid() || !normals.valid() ) 
    {    
      std::cerr << " ERROR 1284947715: One of the dataset ( vertices, texture coordinates or normals ) "
                << " is missing in this geometry. " << std::endl;
      return;
    }

    // Tangent, Binormal, and Normal vectors. 
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > tangentArray( new Msg::MsgCore::Vec3Array() );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > binormalArray( new Msg::MsgCore::Vec3Array() );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > normalArray( new Msg::MsgCore::Vec3Array() );

    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > tan1 = new Msg::MsgCore::Vec3Array( vertices->size() );
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array > tan2 = new Msg::MsgCore::Vec3Array( vertices->size() );
    
    // For this algorithm see "Mathematics for 3D Game Programming & Computer Graphics", 
    // Section 6.8.3.
    //
    // @Assumption: Geometry has indices which defines how many faces / triangles are 
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

      double denom = 1.0 / ( s1 * t2 - s2 * t1 );
      
      if( ( denom > -0.0001 ) && ( denom < 0.0001 ) )
      {        
        MsgMath::Vec3d T, B, N;

        T = MsgMath::Vec3d( 1.0f, 0.0f, 0.0f );
        B = MsgMath::Vec3d( 0.0f, 1.0f, 0.0f );
        N = MsgMath::Vec3d( 0.0f, 0.0f, 1.0f );

        tan1->at( i1 ) = T;
        tan1->at( i2 ) = T;
        tan1->at( i3 ) = T;
        
        tan2->at( i1 ) = B;
        tan2->at( i2 ) = B;
        tan2->at( i3 ) = B;

        normals->at( i1 ) =  N;
        normals->at( i2 ) =  N;
        normals->at( i3 ) =  N;       
      }
      else
      {
        MsgMath::Vec3d T, B;
      
        T = MsgMath::Vec3d( ( t2 * x1 - t1 * x2 ) * denom, ( t2 * y1 - t1 * y2 ) * denom, ( t2 * z1 - t1 * z2 ) * denom );
        B = MsgMath::Vec3d( ( s1 * x2 - s2 * x1 ) * denom, ( s1 * y2 - s2 * y1 ) * denom, ( s1 * z2 - s2 * z1 ) * denom ); 

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
      MsgMath::Vec3d& n = normals->at( i );
      MsgMath::Vec3d& t = tan1->at( i );
      MsgMath::Vec3d& b = tan2->at( i );
      
      // We have to make sure that n is normalized. 
      n.normalize();

      MsgMath::Vec3d tan3v = ( ( t - n * n.dot( t ) ) );            

      tan3v.normalize();      
      
      double f = ( ( ( n.cross( t ) ).dot( b ) ) < 0.0f ? -1.0f : 1.0f ); 

      tw->push_back( MsgMath::Vec3d( f, 0.0, 0.0 ) );

      tangentArray->push_back( tan3v );
    }      

    for( size_t j = 0; j < ( vertices->size() ); ++j )
    {
      MsgMath::Vec3d& n = normals->at( j );
      MsgMath::Vec3d& t = tangentArray->at( j );      
      
      MsgMath::Vec3d bin3v = n.cross( t ) * tw->at( j )[0];

      bin3v.normalize();
      
      binormalArray->push_back( bin3v );
    }

    for( size_t j = 0; j < ( vertices->size() ); ++j )
    {      
      MsgMath::Vec3d norV = normals->at( j );
      norV.normalize();
      normalArray->push_back( norV );     
    }

    geom->tangentArray( tangentArray.get() );
    geom->binormalArray( binormalArray.get() );
    geom->normalArray( normalArray.get() );
  }
  catch( std::bad_alloc )
  {
    std::cerr << " ERROR 3717832430: Bad allocation error." << std::endl;
    return;
  }
  catch( std::exception& e )
  {
    std::cerr << " ERROR 3812433206: " << e.what() << std::endl;
    throw;
  }
  catch( ... )
  {
    std::cerr << " ERROR 1054372311: Unknown error." << std::endl;
    throw;
  }
}