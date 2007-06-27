
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
// Class wraps tweek corba complexity. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_TWEEKWRAPPER_H__
#define __CORE_TWEEKWRAPPER_H__

#include "tweek/CORBA/CorbaManager.h"

#include "vpr/Util/Debug.h"

#include "Export.h"

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

#if ( VRJUGGLER_MAJOR_VERSION <= 2 ) && ( VRJUGGLER_MINOR_VERSION > 0 )
        
        bool init()
        {
          int    argc = 0;      
          char** argv = NULL;

          std::string namingContext( "TWEEK_INTERFACE" );      

          try
          {
            if( mCorbaManager.init( namingContext, argc, argv ) )
            {  
              try 
              {
                if( mCorbaManager.createSubjectManager() )
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

#else
        bool init()
        {
          int    argc = 0;      
          char** argv = NULL;

          std::string namingContext( "TWEEK_INTERFACE" );      

          try
          {
            if( mCorbaManager.init( namingContext, argc, argv ).success() )
            {  
              try 
              {
                if( mCorbaManager.createSubjectManager().success() )
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

#endif

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
        // Set applicatio name.
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
