//
//:
//:

#ifndef _MY_APP_H_
#define _MY_APP_H_

//: VJApp include.
#include <OsgVJApp.h>
#include <OsgDigitalDashboard.h>

//:
#include <osg/StateSet>

//: Users's application class.
class MyApp : public OsgVJApp 
{
	public:

		MyApp( vrj::Kernel* kern, int& argc, char** argv );
		~MyApp(){;}		

		void appInit();
		void appBufferPreDraw();	
		void appPreFrame();
        void appPostOsgDraw();
		void appSceneInit();
		void loadGroupedData(osg::Group* groupNode, const std::string& fileName);	

	private:	
		OsgDigitalDashboard mAppDigitalDashboard;

		int count;
};
#endif //: _MY_APP_H_

