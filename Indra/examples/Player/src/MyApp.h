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
		void appDraw();
		void appSceneInit();
		//void loadGroupedData(osg::Group* groupNode, const std::string& fileName);

		osg::Geometry* createTexturedQuadGeometry(const osg::Vec3& pos,float width,float height, osg::Image* image);

	private:	
};
#endif //: _MY_APP_H_

