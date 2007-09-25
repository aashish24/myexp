
#ifndef __MYAPP_H__
#define __MYAPP_H__


#include "Veda/VedaConfig.h"
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


