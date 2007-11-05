
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

#include "I3dea/Functors/GlobalDisplayFunctor.h"

namespace I3dea
{
	namespace Vrj
	{
		class VRJ_I3DEA_EXPORT AppBase : public vrj::GlApp
		{
			public:

								AppBase(); 
				virtual		   ~AppBase();

				virtual void	displayFunc( IFunctor* displayFunctor );
				
				//virtual void	keyboardFunc();
				//virtual void	gamepadFunc();				

			protected:

				virtual void	contextInit();
				virtual void	init();
				virtual void	preFrame();
				virtual void	postFrame();
				virtual void	draw();
		};
	}
}


#endif // __I3DEA_VRJ_APP_BASE_H__


