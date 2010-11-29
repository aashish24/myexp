
#ifndef __MY_APP_H__
#define __MY_APP_H__

#include "Veda/Core/OsgBase.h"

class MyApp : public Veda::Core::OsgBase 
{
	public:

		MyApp( vrj::Kernel* kern, int& argc, char** argv );

    ~MyApp(){}

		void appInit();
		void appBufferPreDraw();		
		void appSceneInit();
		void appLatePreFrame();
		void appPostFrame();
			
    void takeAction( const std::string& key, const std::string& value );

		void loadGroupedData(osg::Group* groupNode, const std::string& fileName);
};

#endif // __MY_APP_H__

