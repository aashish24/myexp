


#ifndef _MY_APP_H_
#define _MY_APP_H_

/// VJApp include.
#include <vjCore/OsgVJApp.h>
#include <vjDevice/KeyboardMouse.h>
#include <vjDevice/VJKeyboardMouseCallback.h>

#include <Producer/Trackball>

using namespace vjDevice;
using namespace vjCore;
using namespace vjUtil;

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
		void appPostOsgDraw();
		void loadGroupedData(osg::Group* groupNode, const std::string& fileName);	

	private:	
		int count;
		KeyboardMouse* mKm;
		VJKeyboadMouseCallback* mKmCallBack;
		
		bool mIsSceneView;
};

#endif /// _MY_APP_H_

