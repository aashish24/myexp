
///////////////////////////////////////////////////////////////////////////////
//
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

// This should be the first include. 
#include "Veda/VedaConfig.h"

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

#include "Neiv/Base/Referenced.h"
#include "Neiv/Pointer/SmartPointer.h"
#include "Neiv/Pointer/Pointer.h"

#include <vector>
#include <string>

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT AppBase : public Neiv::Base::Referenced
    {
      public:    

        NEIV_DELCARE_SMART_PTR( AppBase );

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

        enum FEATURE 
        { 
          TWEEK  = 0, 
          VJVNC = 1, 
          ALL = 2 
        };

        AppBase();

        virtual void                                   init();

        virtual void                                   initFeatures();       

        virtual void                                   initTweek();      
        
        virtual void                                   initMenus(){}      

        virtual void                                   enableFeature( FEATURE feature=ALL );                  
        
        virtual void                                   applicationName( const std::string& name );

        virtual void*                                  getInteractor();
        virtual void                                   setInteractor( void* ptr );
        
        virtual TweekCommandList                       getReadyCommandList();
        virtual void                                   clearReadyCommandList();

        virtual void                                   setNearFar( const float& nearVal, const float& farVal );       

        virtual void                                   updateAll();
        virtual void                                   updateDeviceData();
        virtual void                                   updateTweek();

      protected:
        
        virtual                                         ~AppBase();

      protected:

        /////////////////////////////////////////////////////////////////////////
        //
        // Single user. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        User::RefPtr                                   mUser;      
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Application name that will be used to identify the 
        // server. 
        //
        /////////////////////////////////////////////////////////////////////////
         
        std::string                                    mApplicationName;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////
        
        Tweek::TweekWrapper*                           mTweekWrapper;    
      

        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////
         
        TweekCommandList                               mReadyCommandList;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        bool                                           mNearFarSet;


      private:       
        
        /////////////////////////////////////////////////////////////////////////
        //
        // VjVnc state. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        bool                                           mEnableVnc;
        

        /////////////////////////////////////////////////////////////////////////
        //
        // Tweek state. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        bool                                          mEnableTweek;    


        ////////////////////////////////////////////////////////////////////////
        //
        // Shared data. 
        //
        /////////////////////////////////////////////////////////////////////////

        cluster::UserData< UserData >                 mUserData;
    };
  }
}

#endif // __CORE_APPBASE_H__

