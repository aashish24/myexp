
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VEDA_CORE_USER_H__
#define __VEDA_CORE_USER_H__

#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"
#include "plugins/ApplicationDataManager/UserData.h"

#include "Veda/Design/Interaction.h"

#include "Veda/Export.h"

#include <vector>

namespace Veda
{
  namespace Core 
  {
    class VEDA_EXPORT User
    {   
      public:

        /////////////////////////////////////////////////////////////////////////
        //
        // Constructor.
        //
        /////////////////////////////////////////////////////////////////////////

        User() 
        {
        }
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor. 
        //
        /////////////////////////////////////////////////////////////////////////

       ~User()
        {
          for( size_t i=0; i < mInteractions.size(); i++ )
          {
            delete mInteractions[ i ];
            
            mInteractions[ i ] = 0;
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Initialization.
        //
        /////////////////////////////////////////////////////////////////////////

        void init()
        {        
          for(unsigned int i=0; i < mInteractions.size(); ++i )
          {
            mInteractions[ i ]->init();
            mInteractions[ i ]->reset();
          }
        }    
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Get interaction.
        //
        /////////////////////////////////////////////////////////////////////////

        void* getInteaction( const unsigned int& pos=0 )
        {
          if( !mInteractions.empty() )
          {
            return mInteractions.at( pos );
          }
          else
          {        
            return 0;
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set interaction.
        //
        /////////////////////////////////////////////////////////////////////////

        void setInteraction( void* ptr )
        {
	        Design::Interaction* in = static_cast< Design::Interaction* >( ptr );                  

          // If its a valid interactor. 
          if( in ) 
          {
            if( mInteractions.size() >= 1)
            {
			        std::vector< Design::Interaction* >::iterator itr = mInteractions.begin();
                          
              for( int i = 0; itr != mInteractions.end(); ++i)
              {
                if(i == 0)
                {
                  delete *itr;
                  itr = mInteractions.erase( itr );                                            
                }  

                // Only swapTexture the iterator if we the list is not empty. 
                if( mInteractions.size() > 0 )
                {
                  ++itr;
                }
              }
              mInteractions.push_back( in );
            }
            else
            {
              mInteractions.push_back( in );
            }
          }         
	        else
	        {
		        std::cerr << "Invalid or corrupted pointer: " << std::endl;
	        }
        }
      

        /////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        /////////////////////////////////////////////////////////////////////////

        void updateDeviceData()
        {
          for( size_t i=0; i < mInteractions.size(); i++ )
          {
            ( mInteractions[ i ] )->updateDeviceData();        
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Update.
        //
        /////////////////////////////////////////////////////////////////////////

        void update()
        {
          for( size_t i=0; i < mInteractions.size(); ++i )
          {
            ( mInteractions[ i ] )->updateAll();
          }        
        }       

      private:    

		  std::vector< Design::Interaction* >    mInteractions;

    };
  }
}

#endif // __VEDA_CORE_USER_H__
