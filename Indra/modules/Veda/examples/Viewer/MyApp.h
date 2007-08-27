
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MYAPP_H__
#define __MYAPP_H__

#ifdef _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgDBd.lib" )
# pragma comment( lib, "osgUtild.lib" )
# pragma comment( lib, "osgFXd.lib" )
# pragma comment( lib, "osgTextd.lib" )
# else
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgUtil.lib" )
# pragma comment( lib, "osgFX.lib" )
# pragma comment( lib, "osgText.lib" )  
#endif

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

