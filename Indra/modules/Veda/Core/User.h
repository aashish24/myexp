
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

#include "Veda/Design/Interactor.h"

#include "Veda/Export.h"

#include "Neiv/Base/Referenced.h"
#include "Neiv/Pointer/SmartPtr.h"

#include <vector>

namespace Veda
{
  namespace Core 
  {
    class VEDA_EXPORT User : public Neiv::Base::Referenced
    {   

      public:

        typedef Neiv::Pointer::SmartPtr< User >                               RefPtr;

        typedef std::vector< Neiv::Pointer::SmartPtr< Design::Interactor >  > Interactors;

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
        // Initialization.
        //
        /////////////////////////////////////////////////////////////////////////

        void init()
        {        
          for( unsigned int i=0; i < mInteractors.size(); ++i )
          {
            mInteractors[ i ]->init();
            mInteractors[ i ]->reset();
          }
        }    
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Get getInteractor.
        //
        /////////////////////////////////////////////////////////////////////////

        void* getInteractor( const unsigned int& pos=0 )
        {
          if( !mInteractors.empty() )
          {
            return ( mInteractors.at( pos ) ).get();
          }
          else
          {        
            return 0;
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set getInteractor.
        //
        /////////////////////////////////////////////////////////////////////////

        void setInteractor( void* ptr )
        {
          Neiv::Pointer::SmartPtr< Design::Interactor > in = static_cast< Design::Interactor* >( ptr );                  

          // If its a valid interactor. 
          if( in.valid() ) 
          {
            if( mInteractors.size() >= 1)
            {
              std::vector< Neiv::Pointer::SmartPtr< Design::Interactor > >::iterator itr = mInteractors.begin();
                          
              for( int i = 0; itr != mInteractors.end(); ++i)
              {
                if(i == 0)
                {
                  //delete *itr;
                  itr = mInteractors.erase( itr );
                }  

                // Only swapTexture the iterator if we the list is not empty. 
                if( mInteractors.size() > 0 )
                {
                  ++itr;
                }
              }
              mInteractors.push_back( in.get() );
            }
            else
            {
              mInteractors.push_back( in.get() );
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
          for( size_t i=0; i < mInteractors.size(); i++ )
          {
            ( mInteractors[ i ] )->updateDeviceData();        
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Update.
        //
        /////////////////////////////////////////////////////////////////////////

        void update()
        {
          for( size_t i=0; i < mInteractors.size(); ++i )
          {
            ( mInteractors[ i ] )->updateAll();
          }        
        }       
      

      protected:

        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor. 
        //
        /////////////////////////////////////////////////////////////////////////

       ~User()
        {
          
        }


      private:    

        Interactors mInteractors;

    };
  }
}

#endif // __VEDA_CORE_USER_H__
