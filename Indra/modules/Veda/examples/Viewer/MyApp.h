
#ifndef __MYAPP_H__
#define __MYAPP_H__

#include "Veda/Core/OsgBase.h"

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

	private:	
		
    std::vector< std::string > mFileNames; 
};

#endif // __MYAPP_H__

