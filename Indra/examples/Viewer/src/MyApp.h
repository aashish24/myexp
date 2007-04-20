
#ifndef __MYAPP_H__
#define __MYAPP_H__

#include "Core/OsgBase.h"

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

		void loadGroupedData( osg::Group* group, const std::string& file );	

	private:	
		int count;		
};

#endif __MYAPP_H__
