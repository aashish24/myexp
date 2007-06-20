
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
// This class CORE_EXPORT provides the functionality of sharing tweek commands to the 
// the cluster nodes. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_DTUSERDATA_H__
#define __CORE_DTUSERDATA_H__

#include <deque> 

#include "vpr/Sync/Mutex.h" 
#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"
#include "plugins/ApplicationDataManager/UserData.h"

#include "Core/CommandFactory.h"
#include "Core/TweekCommand.h"

#include "Export.h"

namespace Core
{
  class CORE_EXPORT UserData : public vpr::SerializableObject
  {  
    public:
      virtual ~UserData()
      {
      }

      ///////////////////////////////////////////////////////////////////////////////
      //
      // Read data values. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      virtual vpr::ReturnStatus readObject( vpr::ObjectReader* reader )
      {
        unsigned int dataSize  = reader->readUint32();
        for( size_t i = 0; i < dataSize ; ++i )
        {      
          mPendingTweekCommandList.push_back(new TweekCommand());  

          mPendingTweekCommandList[ i ]->mIdentifier      = reader->readString();
          mPendingTweekCommandList[ i ]->mEntity          = reader->readString();
          mPendingTweekCommandList[ i ]->mStateAttribute  = reader->readString();
          mPendingTweekCommandList[ i ]->mModifierString  = reader->readString();
          mPendingTweekCommandList[ i ]->mModifierBoolean  = reader->readBool();
          mPendingTweekCommandList[ i ]->mModifierLong    = reader->readUint64();        
        }
        return vpr::ReturnStatus::Succeed;
      }

      ///////////////////////////////////////////////////////////////////////////////
      //
      // Write data values. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      virtual vpr::ReturnStatus writeObject(vpr::ObjectWriter* writer)
      {
        unsigned int dataSize = mPendingTweekCommandList.size();
        
        writer->writeUint32( dataSize );

        for(size_t i = 0; i < dataSize; ++i)
        {          
          writer->writeString ( mPendingTweekCommandList[ i ]->mIdentifier      );
          writer->writeString ( mPendingTweekCommandList[ i ]->mEntity          );
          writer->writeString ( mPendingTweekCommandList[ i ]->mStateAttribute  );
          writer->writeString ( mPendingTweekCommandList[ i ]->mModifierString  );
          writer->writeBool   ( mPendingTweekCommandList[ i ]->mModifierBoolean );
          writer->writeUint64 ( mPendingTweekCommandList[ i ]->mModifierLong    );                  
        }      

        // Release the memory allocated. 
        for( size_t i = 0; i < dataSize; ++i )
        {
          delete mPendingTweekCommandList[ i ];

          // Set the pointer to null.
          mPendingTweekCommandList[ i ] = 0x00;
        }

        mPendingTweekCommandList.clear();

        return vpr::ReturnStatus::Succeed;
      }

    public:

      std::deque< TweekCommand* > mPendingTweekCommandList;

      std::deque< TweekCommand* > mReadyTweekCommandList;
  };  

  class CORE_EXPORT UserDataController
  {
    public: 
      
      ///////////////////////////////////////////////////////////////////////////////
      //
      // Initialization. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      static void init()
      {              
        vpr::GUID new_guid( "d6be4359-e8cf-41fc-a72b-a5b4f3f29aa2" );
        mUserData.init( new_guid, "viz0" );
      }

      ///////////////////////////////////////////////////////////////////////////////
      //
      // Add new command. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      static void addCommand( TweekCommand* tweek_command )
      {
        mCommandLock.acquire();
        {
          mUserData->mPendingTweekCommandList.push_back( tweek_command );
        }
        mCommandLock.release();
      }

      ///////////////////////////////////////////////////////////////////////////////
      //
      // Get command that is ready to be executed. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      static std::deque<TweekCommand*> getReadyTweekCommandList()
      {
        return mUserData->mReadyTweekCommandList;
      }

      ///////////////////////////////////////////////////////////////////////////////
      //
      // Clean already executed commands. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      static void clearTweekCommandList()
      {
        for( size_t i = 0; i < mUserData->mReadyTweekCommandList.size(); ++i )
        {
          mUserData->mReadyTweekCommandList.pop_front();
        }      
      }

      ///////////////////////////////////////////////////////////////////////////////
      //
      // Update ready commands list. 
      //
      ///////////////////////////////////////////////////////////////////////////////

      static void updateTweekCommandList()
      {
        mCommandLock.acquire();
        {
          mUserData->mReadyTweekCommandList = mUserData->mPendingTweekCommandList;
          mUserData->mPendingTweekCommandList.clear();
        }
        mCommandLock.release();
      }

    public:

      static cluster::UserData< UserData >    mUserData;
      static vpr::Mutex                        mCommandLock;
  };
}

#endif // __CORE_DTUSERDATA_H__

