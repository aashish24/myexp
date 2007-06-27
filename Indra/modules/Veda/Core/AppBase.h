
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
// This class VEDA_EXPORT provies functionality independent of scenegraph implemenations. 
// It also provides some advanced level functionality from vrjuggler like 
// tweek, vjvnc.
// 
// @NOTE: 
// Application should never be derived directly from this class VEDA_EXPORT. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_APPBASE_H__
#define __CORE_APPBASE_H__

#include "vrj/Draw/OGL/GlApp.h"

#include "tweek/CORBA/CorbaManager.h"

#include "vpr/Util/Debug.h"
#include "vpr/Sync/Mutex.h" 

#include "Veda/Core/User.h"
#include "Veda/Core/SubjectImpl.h"
#include "Veda/Core/UserData.h"
#include "Veda/Core/SharedData.h"
#include "Veda/Core/Types.h"

#include "Veda/Tweek/TweekWrapper.h"

#include "Veda/Export.h"

#include <vector>
#include <string>

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT AppBase 
    {
      public:    

        /////////////////////////////////////////////////////////////////////////
        //
        // Typedefs.
        //
        /////////////////////////////////////////////////////////////////////////

        typedef std::deque< Tweek::TweekCommand* >         TweekCommandList;


        /////////////////////////////////////////////////////////////////////////
        //
        // Data types.
        //
        /////////////////////////////////////////////////////////////////////////

        enum DEVICE 
        { 
          TWEEK  = 0, VJVNC = 1, ALL = 2 
        };      
        
        enum STATE  
        { 
          OFF = 0, ON = 1 
        };

        AppBase();

        virtual ~AppBase();
        
        virtual void                                   init();

        virtual void                                   initDevices();       

        virtual void                                   initTweek();      
        
        virtual void                                   initMenus(){}      

        virtual void                                   setDevice( DEVICE device=ALL, STATE state=OFF );                  
        
        virtual void                                   applicationName( const std::string& name );

        virtual void*                                  interaction();
        virtual void                                   interaction( void* ptr );
        
        virtual TweekCommandList                       getReadyCommandList();
        virtual void                                   clearReadyCommandList();

        virtual void                                   setNearFar( const long&  near, const long& far );       

        virtual void                                   updateAll();
        virtual void                                   updateDeviceData();
        virtual void                                   updateTweek();

      protected:

        /////////////////////////////////////////////////////////////////////////
        //
        // Single user. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        User                                                      mUser;      
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Application name that will be used to identify the 
        // server. 
        //
        /////////////////////////////////////////////////////////////////////////
         
        std::string                                               mApplicationName;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////
        
        Tweek::TweekWrapper*                                      mTweekWrapper;    
      

        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////
         
        TweekCommandList                                          mReadyCommandList;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        bool                                                      mNearFarSet;


      private:       
        
        /////////////////////////////////////////////////////////////////////////
        //
        // VjVnc state. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        STATE                                          mVncState;
        

        /////////////////////////////////////////////////////////////////////////
        //
        // VjVnc state. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        STATE                                          mTweekState;    


        ////////////////////////////////////////////////////////////////////////
        //
        // Shared data. 
        //
        /////////////////////////////////////////////////////////////////////////

        cluster::UserData< UserData >                  mUserData;
    };
  }
}

#endif // __CORE_APPBASE_H__

