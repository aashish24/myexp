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

		//: Initializations. 
		//-------------------------------------------------------------
		MyApp( vrj::Kernel* kern, int& argc, char** argv );
		~MyApp(){;}		

		void appInit();

		void appBufferPreDraw();	

		void appSceneInit();

		//: App frame functions.
		//-------------------------------------------------------------
		
		/** OpenGL draw routine. */
		void appOpenGLDraw();


		/** 
		 * Read data from text descriptor and attahced it to the <BR>
		 * groupNode. 
		 */
		void loadGroupedData(osg::Group* groupNode, const std::string& fileName);	

	private:	
		int count;
};
#endif //: _MY_APP_H_

