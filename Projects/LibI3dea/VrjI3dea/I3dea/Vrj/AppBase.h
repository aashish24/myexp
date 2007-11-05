
#ifndef	__I3DEA_VRJ_APP_BASE_H__
#define __I3DEA_VRJ_APP_BASE_H__

#include "Export.h"

namespace I3dea
{
	namespace Vrj
	{
		class VRJ_I3DEA_EXPORT AppBase : public vrj::OglApp
		{
			public:

								AppBase(); 
				virtual		   ~AppBase();

				virtual void	displayFunc( GlobalDisplayFunctor< T >* displayFunctor );
				
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


