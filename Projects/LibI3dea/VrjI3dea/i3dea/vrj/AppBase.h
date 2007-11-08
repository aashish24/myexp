
#ifndef	__I3DEA_VRJ_APP_BASE_H__
#define __I3DEA_VRJ_APP_BASE_H__

#include "Export.h"

#include "vrj/vrjConfig.h"

#include <iostream>
#include <iomanip>

#if defined(__APPLE__)
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

#include "vrj/Draw/OGL/GlApp.h"

#include "i3dea/Functors/GlobalDisplayFunctor.h"

namespace i3dea
{
	namespace vrj
	{		
		///////////////////////////////////////////////////////////////////////
		// 
		// Non member functions. 
		// 
		///////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////
		// 
		// GLUT style display function. 
		// 
		///////////////////////////////////////////////////////////////////////

		template< typename T >
		void setDisplayFunc( T func ) 
		{
			AppBase::instance().displayFunc( new GlobalDisplayFunctor< T >( func ) );
		}


		///////////////////////////////////////////////////////////////////////
		// 
		// 
		// 
		///////////////////////////////////////////////////////////////////////

		class VRJ_I3DEA_EXPORT AppBase : public ::vrj::GlApp
		{
			public:
			
				static AppBase&   instance();
				
				static  void	    run();

				static	void	    exit();

        virtual void	    displayFunc( IFunctor* displayFunctor );			

			private:
								          AppBase(); 

				virtual		       ~AppBase();

			protected:

				IFunctor*		      _displayFunctor;

				virtual void	    contextInit();

				virtual void	    init();

				virtual void	    preFrame();
				
				virtual void	    intraFrame();

				virtual void	    postFrame();

        virtual void      bufferPreDraw();

				virtual void	    draw();			

			private:
				
				static AppBase*	  _appBaseInstance;
		};
	}
}


#endif // __I3DEA_VRJ_APP_BASE_H__


