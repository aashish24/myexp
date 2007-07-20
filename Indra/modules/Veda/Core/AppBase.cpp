
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/Core/AppBase.h"
#include "Veda/Core/Defs.h"

#include "vrj/Display/Projection.h"

namespace Veda
{
  namespace Core
  {

    static const std::string TWEEK_SUBJECT_ID = "TweekSubject";

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Constructor. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    AppBase::AppBase()  : 
      mApplicationName( "Application" ), 
      mNearFarSet     ( false ), 
      mEnableVnc      ( false ), 
      mEnableTweek    ( false )
    {  
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Destructor. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    AppBase::~AppBase()
    {
      if( mTweekWrapper != 0x00 )
      {      
        delete mTweekWrapper;
        mTweekWrapper = 0x00;
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialize features.  
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::initFeatures()
    {
      if( mEnableTweek )
      {
        initTweek();
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set application name for Tweek purposes. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::applicationName( const std::string& name )
    {
      mApplicationName = name;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Get current getInteractor in use. 
    //
    //////////////////////////////////////////////////////////////////////////////

    void* AppBase::getInteractor()
    {
      return ( static_cast< void* >( mUser.getInteractor() ) );
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set getInteractor. 
    //
    //////////////////////////////////////////////////////////////////////////////

    void AppBase::setInteractor( void* ptr )
    {
      mUser.setInteractor( ptr );
    }  


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialize. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::init()
    { 
      // Initialize definitions. 
      Defs::init();

      // Initialize cluster data sharing. 
      SharedData::init(); 

      // User related initialization. 
      mUser.init();          

      // Set default near far. 
      if( !mNearFarSet )
      {
        setNearFar( 0.1f, 1000000.0f ); 
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Get commands that are ready to execute. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    AppBase::TweekCommandList AppBase::getReadyCommandList()
    {        
      return mReadyCommandList;
    }  


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Clean command that are already executed. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::clearReadyCommandList()
    {      
      if( mReadyCommandList.size() != 0 && ( mEnableTweek ) )
      {
        for( size_t i = 0; i < mReadyCommandList.size(); ++i )
        {
          delete ( mReadyCommandList[ i ] );
          
          mReadyCommandList[ i ]  = 0;        

          mReadyCommandList.pop_front();
        }        
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set near far. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::setNearFar( const float& nearVal, const float& farVal )
    { 
      vrj::Projection::setNearFar( nearVal, farVal );
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialize tweek. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::initTweek()
    {
      // Initialize cluste data sharing for tweek. 
      UserDataController::init();

      // Initialize the tweek wrapper object. 
      mTweekWrapper = new Tweek::TweekWrapper();

      std::cout << "Initializing tweek: " << std::endl; 
 
      // Check if tweek has been initialized if not then set state off and return. 
      if(!mTweekWrapper->init())
      {    
        mEnableTweek = false;
        return;
      }
      
      // Else initialize tweek server. 
      Veda::SubjectImpl* mSubject;

      mSubject = new Veda::SubjectImpl();
      mSubject->init();

      mTweekWrapper->applicationName( mApplicationName );
      mTweekWrapper->setSubject( mSubject, TWEEK_SUBJECT_ID );      
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Update tweek. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::updateTweek()
    {
      if( mEnableTweek )
      {
        // First copy the commands over at the current list. 
        mReadyCommandList  = UserDataController::getReadyTweekCommandList();

        // Now clear the list in the shared memory. 
        UserDataController::clearTweekCommandList();

        // Now update it.
        UserDataController::updateTweekCommandList();
      }
      else 
      {
        return;
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Update everything else. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::updateAll()
    {
      mUser.update();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Update device data. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::updateDeviceData()
    {
      mUser.updateDeviceData();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set features. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::enableFeature( FEATURE feature )
    {  
      switch( feature )
      {
        case VJVNC: 
        {
          mEnableVnc  = true;          
          break;        
        }
        case TWEEK: 
        {        
          mEnableTweek = true;
          break;
        }
        case ALL: 
        {      
          mEnableTweek = mEnableVnc = true;
          break;
        }
        default: 
        { 
          break;
        }
      };
      
      initFeatures();
    } 
  }
}

