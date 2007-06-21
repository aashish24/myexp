
#ifndef __MYAPP_H__
#define __MYAPP_H__

#include "Veda/Core/OsgBase.h"

class MyApp : public Core::OsgBase
{
	public:

		MyApp( vrj::Kernel* kern, int& argc, char** argv );

		~MyApp()
    {
    }

		void appInit();		
		void appBufferPreDraw();	
	  void appSceneInit();			

	private:	
		int count;		
};

#endif __MYAPP_H__
