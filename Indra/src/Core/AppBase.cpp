
#include "Core/AppBase.h"
#include "Core/Defs.h"

#include "vrj/Display/Projection.h"

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

Core::AppBase::AppBase()  : 
  mApplicationName( "Application" ), 
  mNearFarSet     ( false )
{  
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

Core::AppBase::~AppBase()
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

void Core::AppBase::initDevices()
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

void Core::AppBase::applicationName( const std::string& name )
{
  mApplicationName = name;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////

void* Core::AppBase::interaction()
{
  return mUser.getInteaction();
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////

void Core::AppBase::interaction( void* ptr )
{
  mUser.setInteraction( ptr );
}  


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::AppBase::init()
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

Core::AppBase::TweekCommandList Core::AppBase::getReadyCommandList()
{        
  return mReadyCommandList;
}  


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::AppBase::clearReadyCommandList()
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

void Core::AppBase::setNearFar( const long& near, const long& far )
{  
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::AppBase::initTweek()
{
  // Initialize the tweek wrapper object. 
  mTweekWrapper = new TweekWrapper();

  // Check if tweek has been initialized if not then set state off and return. 
  if(!mTweekWrapper->init())
  {    
    return;
  }
  
  dt::SubjectImpl* mSubject;

  mSubject = new dt::SubjectImpl();
  mSubject->init();

  mTweekWrapper->applicationName( mApplicationName );
  mTweekWrapper->setSubject( mSubject, "Subject");      
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::AppBase::updateTweek()
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

void Core::AppBase::update()
{
  mUser.update();
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::AppBase::updateDeviceData()
{
  mUser.updateDeviceData();
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::AppBase::setDevice( DEVICE device, STATE state )
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
