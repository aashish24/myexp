
#ifndef __MYAPP_H__
#define __MYAPP_H__

//#if defined _MSC_VER && _DEBUG
//# pragma comment( lib, "osgd.lib" )
//# pragma comment( lib, "osgDBd.lib" )
//# pragma comment( lib, "osgUtild.lib" )
//# pragma comment( lib, "osgFXd.lib" )
//# pragma comment( lib, "osgTextd.lib" )
//# elif defined _MSC_VER
//# pragma comment( lib, "osg.lib" )
//# pragma comment( lib, "osgDB.lib" )
//# pragma comment( lib, "osgUtil.lib" )
//# pragma comment( lib, "osgFX.lib" )
//# pragma comment( lib, "osgText.lib" )  
//#endif

#include "Veda/Core/OsgBase.h"

#include "Prithvi/Core/Planet.h"

#include <vector>

class MyApp : public Veda::Core::OsgBase
{
	public:

		MyApp( vrj::Kernel* kern, int& argc, char** argv );

		~MyApp()
    		{
    		}

		void appInit();		
		void appBufferPreDraw();	
	  void appSceneInit();			
    void appLatePreFrame();	  

  private: 
    
    Prithvi::Core::Planet::RefPtr mPlanet;    
};

#endif // __MYAPP_H__


