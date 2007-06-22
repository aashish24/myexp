//
//:
//:

#ifndef _MY_APP_H_
#define _MY_APP_H_

//: VJApp include.
#include <OsgVJApp.h>

//: Users's application class.
class MyApp : public OsgVJApp 
{
	public:

		MyApp( vrj::Kernel* kern, int& argc, char** argv );
		~MyApp(){;}		

		void appInit();
		void appBufferPreDraw();		
		//void appPostOsgDraw();
		void appSceneInit();
		void appLatePreFrame();
		void takeAction(std::string command_identifier, 
						std::string entity, 
						std::string state_attribute, 
						std::string modifier_string, 
						bool modifier_bool, 
						long modifier_long);
		void loadGroupedData(osg::Group* groupNode, const std::string& fileName);

};
#endif //: _MY_APP_H_

