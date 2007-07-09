
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
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

    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    AppBase::AppBase()  : 
      mApplicationName( "Application" ), 
      mNearFarSet     ( false )
    {  
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
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
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::initDevices()
    {
      if( mTweekState == ON )
      {
        initTweek();
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::applicationName( const std::string& name )
    {
      mApplicationName = name;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    //////////////////////////////////////////////////////////////////////////////

    void* AppBase::interaction()
    {
      return mUser.getInteaction();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    //////////////////////////////////////////////////////////////////////////////

    void AppBase::interaction( void* ptr )
    {
      mUser.setInteraction( ptr );
    }  


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
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
        setNearFar( 0.1, 1000000.0 ); 
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    AppBase::TweekCommandList AppBase::getReadyCommandList()
    {        
      return mReadyCommandList;
    }  


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::clearReadyCommandList()
    {      
      if( mReadyCommandList.size() != 0 && ( mTweekState == ON ) )
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
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::setNearFar( const long double& near, const long double& far )
    {  
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::initTweek()
    {
      // Initialize the tweek wrapper object. 
      mTweekWrapper = new Tweek::TweekWrapper();

      // Check if tweek has been initialized if not then set state off and return. 
      if(!mTweekWrapper->init())
      {    
        return;
      }
      
      Veda::SubjectImpl* mSubject;

      mSubject = new Veda::SubjectImpl();
      mSubject->init();

      mTweekWrapper->applicationName( mApplicationName );
      mTweekWrapper->setSubject( mSubject, "Subject");      
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::updateTweek()
    {
      if( mTweekState == ON )
      {
        // First copy the commands over at the current list. 
        mReadyCommandList  = UserDataController::getReadyTweekCommandList();
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
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::updateAll()
    {
      mUser.update();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::updateDeviceData()
    {
      mUser.updateDeviceData();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void AppBase::setDevice( DEVICE device, STATE state )
    {  
      switch( device )
      {
        case VJVNC: 
        {
          mVncState   = state;
          mTweekState = OFF;
          break;        
        }
        case TWEEK: 
        {        
          mTweekState = state;
          mVncState   = OFF;
          break;
        }
        case ALL: 
        {      
          mVncState    = state;    
          mTweekState  = state;
          break;
        }
        default: 
        {
          mVncState    = OFF;
          mTweekState  = OFF;
          break;
        }
      };
      
      initDevices();
    } 
  }
}

