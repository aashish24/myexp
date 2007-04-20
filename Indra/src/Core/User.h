
///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_USER_H__
#define __CORE_USER_H__

#include <vector>

#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"
#include "plugins/ApplicationDataManager/UserData.h"

#include "Core/Interaction.h"

#include "Export.h"

namespace Core 
{
	class CORE_EXPORT User
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
				Interaction* in = static_cast< Interaction* >( ptr );									

				if( in ) 
				{	
					if( mInteractions.size() >= 1)
					{
						std::vector< Interaction* >::iterator itr = mInteractions.begin();
												
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

			std::vector< Interaction* >	  mInteractions;

	};
}

#endif // __CORE_USER_H__
