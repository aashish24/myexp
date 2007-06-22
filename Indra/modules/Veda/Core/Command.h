
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class that performs the task of sharing the data across cluster. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_COMMAND_H__
#define  __CORE_COMMAND_H__  

#include <string>

#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"

#include "plugins/ApplicationDataManager/UserData.h"

#include "gmtl/Matrix.h"
#include "gmtl/Vec.h"

#include "Export.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT Command : public vpr::SerializableObject
    {
      public:

        /////////////////////////////////////////////////////////////////////////
        //
        // Read data values. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual void readObject( vpr::ObjectReader* reader )
        {        
          float posData[ 16 ];
          
          for ( unsigned n = 0; n < 16; n++ )
          {
             posData[n] = reader->readFloat();
          }

          mSharedTransformMatrix.set( posData );
          
          int noOfAnalogInputs  = reader->readUint32();
          int noOfDigitalInputs = reader->readUint32(); 

          for( int i = 0; i < noOfAnalogInputs; i++ )
          {
            int first      = reader->readUint32();
            double second  = reader->readDouble();

            mAnalogInputs[ first ] = second;
          }
          
          for( int i = 0; i < noOfDigitalInputs; i++ )
          {
            int first  = reader->readUint32();
            int second = reader->readUint32();
             
            mDigitalInputs[ first ] = second;
          }
          
          unsigned int sizeLong   = reader->readUint32();    
          unsigned int sizeDouble = reader->readUint32();
          unsigned int sizeString = reader->readUint32();
          unsigned int sizeMatrix = reader->readUint32();
          unsigned int sizeVector = reader->readUint32();

          for( unsigned int i = 0; i < sizeLong; ++i )      
          {
            mSharedLongTypeObjects[ reader->readString() ]    = reader->readUint32();
          }

          for( unsigned int i = 0; i < sizeDouble; ++i )      
          {
            mSharedDoubleTypeObjects[ reader->readString() ]  = reader->readDouble();
          }      

          for( unsigned int i = 0; i < sizeString; ++i )      
          {
            mSharedStringTypeObjects[ reader->readString() ]  = reader->readString();
          }           
          
          for( unsigned int i = 0; i < sizeMatrix; ++i )      
          {             
            float posData[ 16 ];
            std::string str = reader->readString();  
            for ( unsigned n = 0; n < 16; n++ )
              {
                   posData[ n ] = reader->readFloat();
              }

            gmtl::Matrix44f mat;
            mat.set( posData );
            mSharedMatrixTypeObjects[str] = mat;          
          }

          for( unsigned int i = 0; i < sizeVector; ++i )      
          { 
            float vecData[ 3 ];
            std::string str = reader->readString();

            for( unsigned n = 0; n < 3; ++n )
            {
              vecData[n] = reader->readFloat();
            }

            gmtl::Vec3f vec;
            vec.set( vecData );
            
            mSharedVectorTypeObjects[ str ] = vec;
          }        

      }

      ///////////////////////////////////////////////////////////////////////////
      //
      // Write data values. 
      //
      ///////////////////////////////////////////////////////////////////////////

      virtual void writeObject(vpr::ObjectWriter* writer)
      {
          
          const float* posData = mSharedTransformMatrix.getData();

          for ( int n = 0; n < 16; n++ )
          {
            writer->writeFloat( posData[ n ] );
          }
          
          unsigned int noOfAnalogInputs  = mAnalogInputs.size();
          unsigned int noOfDigitalInputs = mDigitalInputs.size();

          writer->writeUint32( noOfAnalogInputs  );
          writer->writeUint32( noOfDigitalInputs );      

          std::map< int, double >::iterator itrAn;    
          for( itrAn = mAnalogInputs.begin(); itrAn!= mAnalogInputs.end(); ++itrAn )
          {      
            writer->writeUint32( itrAn->first );
            writer->writeDouble( itrAn->second );
          }

          std::map< int, int >::iterator itrDi;
          for( itrDi = mDigitalInputs.begin(); itrDi != mDigitalInputs.end(); ++itrDi )
          {      
            writer->writeUint32(itrDi->first);
            writer->writeUint32(itrDi->second);
          }

          unsigned int sizeLong     = mSharedLongTypeObjects.size();
          unsigned int sizeDouble   = mSharedDoubleTypeObjects.size();
          unsigned int sizeString   = mSharedStringTypeObjects.size();
          unsigned int sizeMatrix   = mSharedMatrixTypeObjects.size();
          unsigned int sizeVector   = mSharedVectorTypeObjects.size();

          writer->writeUint32( sizeLong );    
          writer->writeUint32( sizeDouble );
          writer->writeUint32( sizeString );
          writer->writeUint32( sizeMatrix );
          writer->writeUint32( sizeVector );

          std::map< std::string, long >::iterator itrL;
          for( itrL = mSharedLongTypeObjects.begin(); itrL != mSharedLongTypeObjects.end(); ++itrL )
          {
            writer->writeString( itrL->first  );
            writer->writeUint32( itrL->second );
          }

          std::map< std::string, double >::iterator itrF;
          for( itrF = mSharedDoubleTypeObjects.begin(); itrF != mSharedDoubleTypeObjects.end(); ++itrF )
          {
            writer->writeString( itrF->first  );
            writer->writeDouble( itrF->second );
          }

          std::map< std::string, std::string >::iterator itrS;
          for( itrS = mSharedStringTypeObjects.begin(); itrS != mSharedStringTypeObjects.end(); ++itrS )
          {
            writer->writeString( itrS->first  );
            writer->writeString( itrS->second );
          }

          std::map< std::string, gmtl::Matrix44f >::iterator itrM;        
          for( itrM = mSharedMatrixTypeObjects.begin(); itrM!=mSharedMatrixTypeObjects.end(); ++itrM )
          {
            writer->writeString( itrM->first );
            const float* posData = ( itrM->second ).getData();
              for ( int n = 0; n < 16; n++ )
              {
              writer->writeFloat( posData[ n ] );
              }            
          }
          
          std::map< std::string, gmtl::Vec3f >::iterator itrV;
          for( itrV = mSharedVectorTypeObjects.begin();itrV != mSharedVectorTypeObjects.end(); ++itrV )
          {
            writer->writeString( itrV->first );
            const float* vec_data = ( itrV->second ).getData();
            for( unsigned int i=0; i < 3; ++i  )
            {
              writer->writeFloat( vec_data[ i ] );
            }
          }
      }

      public:       

        gmtl::Matrix44f                            mSharedTransformMatrix;  
        
        std::map< int, int >                      mDigitalInputs;       
        std::map< int, double >                    mAnalogInputs;

        std::map< std::string, long  >              mSharedLongTypeObjects;
        std::map< std::string, double >            mSharedDoubleTypeObjects;
        std::map< std::string, std::string  >      mSharedStringTypeObjects;      
        std::map< std::string, gmtl::Matrix44f >  mSharedMatrixTypeObjects;      
        std::map< std::string, gmtl::Vec3f >      mSharedVectorTypeObjects;
    };
  }
}

#endif // __CORE_COMMAND_H__
