
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class wraps tweek corba complexity. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_TWEEKWRAPPER_H__
#define __CORE_TWEEKWRAPPER_H__

#include "tweek/CORBA/CorbaManager.h"

#include "vpr/Util/Debug.h"

#include "Veda/Export.h"
#include "Veda/VedaDefines.h"

namespace Veda
{
  namespace Tweek
  {
    class VEDA_EXPORT TweekWrapper
    {
      public:

        /////////////////////////////////////////////////////////////////////////
        //
        // Constructor.
        //
        /////////////////////////////////////////////////////////////////////////

        TweekWrapper() :
          mTweekInitialized ( false ),
          mApplicationName  ( "" )
        {        
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor.
        //
        /////////////////////////////////////////////////////////////////////////

       ~TweekWrapper()
        {        
        }
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Initialization
        //
        /////////////////////////////////////////////////////////////////////////

        bool init()
        {
          int    argc = 0;      
          char** argv = NULL;

          std::string namingContext( "TweekSubject" );      

          try
          {
	    std::cout << "Initializing CORBA manager: " << std::endl;

#if defined( __TWEEK_version ) && ( __TWEEK_version >= 1001013 )
            if( mCorbaManager.init( namingContext, argc, argv ) )
#else
  	    if( mCorbaManager.init( namingContext, argc, argv ).success() )	
#endif // defined( __TWEEK_version ) && ( __TWEEK_version >= 1001013 )
            {  
              try 
              {
	    	std::cout << "Creating SUBJECT  manager: " << std::endl;
#if defined( __TWEEK_version ) && ( __TWEEK_version >= 1001013 )
		if( mCorbaManager.createSubjectManager() )
#else
		if( mCorbaManager.createSubjectManager().success() )
#endif //defined( __TWEEK_version ) && ( __TWEEK_version >= 1001013 )
                {
                  mTweekInitialized = true;                  
                }
              }
              catch( CORBA::Exception& e )
              {                
              }
            }
          }
          catch( ... )
          {          
          }

          return mTweekInitialized;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set tweel subject with a unique name.
        //
        /////////////////////////////////////////////////////////////////////////

        void setSubject( tweek::SubjectImpl* subject, const std::string& name )
        {
          if( mTweekInitialized )
          {
            try
            {
              mCorbaManager.getSubjectManager()->registerSubject( subject, name.c_str( ));
              mCorbaManager.getSubjectManager()->setApplicationName( mApplicationName );

              mSubject = subject;
            }      
            catch( CORBA::Exception& ex )
            {            
            }
          }
          else
          {          
          }
        }

        
        /////////////////////////////////////////////////////////////////////////
        //
        // Get application name.
        //
        /////////////////////////////////////////////////////////////////////////

        const std::string& applicationName() const
        {
          return mApplicationName;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set application name.
        //
        /////////////////////////////////////////////////////////////////////////

        void applicationName( const std::string& applicationName )
        {
          mApplicationName = applicationName;
        }      

      private:      
        
        bool                                           mTweekInitialized;    

        std::string                                    mApplicationName;

        tweek::CorbaManager                            mCorbaManager;

        tweek::SubjectImpl*                            mSubject;    
    };
  }
}

#endif // __CORE_TWEEKWRAPPER_H__
