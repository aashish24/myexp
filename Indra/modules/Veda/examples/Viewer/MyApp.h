
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

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
    void appLatePreFrame();

	private:	
		
    std::vector< std::string > mFileNames; 
};

#endif // __MYAPP_H__

