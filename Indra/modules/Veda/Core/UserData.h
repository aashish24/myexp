
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Class UserData provides the functionality of sharing tweek commands to the 
// the cluster nodes. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VEDA_CORE_USERDATA_H__
#define __VEDA_CORE_USERDATA_H__

#include <deque> 

#include "vpr/Sync/Mutex.h" 
#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"
#include "plugins/ApplicationDataManager/UserData.h"

#include "Veda/Core/CommandFactory.h"

#include "Veda/Tweek/TweekCommand.h"

#include "Veda/Export.h"
#include "Veda/VedaDefines.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT UserData : public vpr::SerializableObject
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

#if defined( __VPR_version ) && ( __VPR_version > 1001005 )
        virtual void 
#else 
        virtual vpr::ReturnStatus  
#endif // defined( __VPR_version ) && ( __VPR_version > 1001005 )
        readObject( vpr::ObjectReader* reader )
        {
          unsigned int dataSize  = reader->readUint32();
          
          for( size_t i = 0; i < dataSize ; ++i )
          {      
            mPendingTweekCommandList.push_back( new Tweek::TweekCommand() );  

            mPendingTweekCommandList[ i ]->mKey    = reader->readString();
            mPendingTweekCommandList[ i ]->mValue  = reader->readString();        
          }                     
#if defined( __VPR_version ) && ( __VPR_version > 1001005 )
#else
          return vpr::ReturnStatus::Succeed;
#endif // defined( __VPR_version ) && ( __VPR_version > 1001005 )
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // Write data values. 
        //
        ///////////////////////////////////////////////////////////////////////////////

#if defined( __VPR_version ) && ( __VPR_version > 1001005 )
        virtual void 
#else
        vpr::ReturnStatus
#endif // defined( __VPR_version ) && ( __VPR_version > 1001005 )
        writeObject(vpr::ObjectWriter* writer)
        {
          unsigned int dataSize = mPendingTweekCommandList.size();
          
          writer->writeUint32( dataSize );

          for(size_t i = 0; i < dataSize; ++i)
          {          
            writer->writeString ( mPendingTweekCommandList[ i ]->mKey   );
            writer->writeString ( mPendingTweekCommandList[ i ]->mValue );
          }      

          // Release the memory allocated. 
          for( size_t i = 0; i < dataSize; ++i )
          {
            delete mPendingTweekCommandList[ i ];

            // Set the pointer to null.
            mPendingTweekCommandList[ i ] = 0x00;
          }

          mPendingTweekCommandList.clear();        

#if defined( __VPR_version ) && ( __VPR_version > 1001005 )
#else
          return vpr::ReturnStatus::Succeed;   
#endif	// defined( __VPR_version ) && ( __VPR_version > 1001005 ) 
        }

      public:
  			
        std::deque< Tweek::TweekCommand* > mPendingTweekCommandList;
        std::deque< Tweek::TweekCommand* > mReadyTweekCommandList;
    };  


    class VEDA_EXPORT UserDataController
    {
      public: 
        
        ///////////////////////////////////////////////////////////////////////////////
        //
        // Initialization. 
        //
        ///////////////////////////////////////////////////////////////////////////////

        static void init()
        {              
          vpr::GUID guid( "d6be4359-e8cf-41fc-a72b-a5b4f3f29aa2" );
          mUserData.init( guid );
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // Add new command. 
        //
        ///////////////////////////////////////////////////////////////////////////////

        static void addCommand( Tweek::TweekCommand* tweek_command )
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

        static std::deque< Tweek::TweekCommand* > getReadyTweekCommandList()
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
        static vpr::Mutex                       mCommandLock;
    };
  }
}

#endif // __VEDA_CORE_USERDATA_H__

