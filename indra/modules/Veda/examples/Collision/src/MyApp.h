


#ifndef _MY_APP_H_
#define _MY_APP_H_

/// VJApp include.
#include <OsgVJApp.h>
#include <KeyboardMouseHandler.h>

/// Users's application class.
class MyApp : public OsgVJApp 
{
	public:

		MyApp( vrj::Kernel* kern, int& argc, char** argv );
		~MyApp(){;}		

		void appInit();		
		void appBufferPreDraw();	
	    void appSceneInit();	
		void appPreFrame();
		void appLatePreFrame();
		void loadGroupedData(osg::Group* groupNode, const std::string& fileName);	

	private:	
		int count;
		KeyboardMouseHandler mKMHandle;
};

#endif /// _MY_APP_H_

