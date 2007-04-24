
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

namespace Core
{
	class CORE_EXPORT TweekWrapper
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

				std::string namingContext( "TWEEK_INTERFACE" );			

				try
				{
					if( ( mCorbaManager.init( namingContext, argc, argv ) ).success() )
					{	
						vpr::ReturnStatus status;
						try 
						{
							status = mCorbaManager.createSubjectManager();

							if( status.success() )
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

#endif // __CORE_TWEEKWRAPPER_H__
