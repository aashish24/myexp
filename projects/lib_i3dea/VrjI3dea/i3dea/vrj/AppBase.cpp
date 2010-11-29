

#include "i3dea/Vrj/AppBase.h"

#include "vrj/Kernel/Kernel.h"


i3dea::vrj::AppBase* i3dea::vrj::AppBase::_appInstance = 0x00; 	


namespace i3dea
{
	namespace vrj
	{
		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

    AppBase::AppBase() : 
      _displayFunctor( 0x00 ), 
      _contextInitFunctor( 0x00 ),
      _exitFunctor( 0x00 ) 
		{
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		AppBase::~AppBase()
		{			
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		AppBase&  AppBase::instance()
		{			
			if( _appInstance )
			{
				return ( *_appInstance );
			}
			else
			{
				_appInstance = new AppBase();
				return ( *_appInstance );
			}
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::displayFunc( IFunctor* displayFunctor )
		{
			_displayFunctor = displayFunctor;
		}


    ///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::contextInitFunc( IFunctor* contextInitFunctor )
		{
			_contextInitFunctor = contextInitFunctor;
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::run()
		{
			if( _appInstance ) 
			{			
				::vrj::Kernel* kernel = ::vrj::Kernel::instance();
				
				if(! kernel )
				{
				}
				
				kernel->start();
				kernel->setApplication( _appInstance );
				
				// Some how we have to do this: 
				// Find out where this dll is
				// Relative to that we will find the config. 
				kernel->loadConfigFile( "C:\\aashish\\src\\osve\\current\\osve\\trunk\\Indra\\configs\\vrjuggler\\2.2.x\\original\\simstandalone.jconf" );
				
				kernel->waitForKernelStop();
		
			}
			else
			{
				// Throw an exception here. 
			}
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////
		
		void AppBase::exit()
		{
      if( _appInstance )
      {
        _appInstance->clean();
        delete _appInstance; 
        _appInstance = 0x00;
      }
    }


    ///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::init()
		{
			::vrj::GlApp::init();
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::contextInit()
		{
			::vrj::GlApp::contextInit();

      if( _contextInitFunctor )
      {
        _contextInitFunctor->call();
      }
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::preFrame()
		{
			::vrj::GlApp::preFrame();
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::intraFrame()
		{
			::vrj::GlApp::intraFrame();
		}


		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::postFrame()
		{
			::vrj::GlApp::postFrame();
		}		
		

    void AppBase::bufferPreDraw()
    {
      glClearColor( 0.0, 0.0, 0.0, 1.0 );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

		///////////////////////////////////////////////////////////////////////
		//
		//
		//
		///////////////////////////////////////////////////////////////////////

		void AppBase::draw()
		{
      if( _displayFunctor )
      {
			  _displayFunctor->call();
      }
		}		


    void AppBase::clean()
    {
      if( _exitFunctor )
      {
        _exitFunctor->call();
      }
    }
	}
}