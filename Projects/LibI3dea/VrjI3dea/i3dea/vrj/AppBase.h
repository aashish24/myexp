
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

#include "i3dea/Functors/DisplayFunctor.h"

namespace i3dea
{
	namespace vrj
	{		
		
		///////////////////////////////////////////////////////////////////////
		// 
		// 
		// 
		///////////////////////////////////////////////////////////////////////

		class VRJ_I3DEA_EXPORT AppBase : public ::vrj::GlApp
		{
			public:
			
				static AppBase&   instance();
				static void	      exit();

				void	            run();				

        void	            displayFunc( IFunctor* displayFunctor );			

        void              exitFunc( IFunctor* exitFunctor );

			private:
								          AppBase(); 

				virtual		       ~AppBase();

			protected:

				IFunctor*		      _displayFunctor;

        IFunctor*         _exitFunctor;

				void	            contextInit();

				void	            init();

				void	            preFrame();
				
				void	            intraFrame();

				void	            postFrame();

        void              bufferPreDraw();

				void	            draw();		

        void              clean();

			private:
				
				static AppBase*	  _appInstance;
		};
	}
}


#endif // __I3DEA_VRJ_APP_BASE_H__


