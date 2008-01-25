
#ifndef __App_H__
#define __App_H__

#define TWO_PI
#include "Oge/OgePrithvi/PrithviCore/Planet.h"
#undef TWO_PI

#include "Oge/OgeVrj/VrjOsg/VrjViewer.h"

#include <vector>

class App : public Oge::OgeVrj::VrjOsg::VrjViewer
{
	public:

    OGE_DELCARE_SMART_PTR( App );

		App( int& argc, char** argv );

		~App()
		{
		}

    void contextInit();
		void init();					 
    void initScene();

  private: 
    
    Oge::OgePrithvi::PrithviCore::Planet::RefPtr _planet;    
};

#endif // __App_H__


