
#ifndef __MYAPP_H__
#define __MYAPP_H__

#include "osgDB/ReadFile"

#include "Veda/Core/OsgBase.h"

#include "OsgTools/Geom/OsgDashboard.h"

#include <vector>

#define viewDistance 2

class MyApp : public Veda::Core::OsgBase
{
	public:

		std::vector < osg::ref_ptr< OsgTools::Geom::OsgDashboard > > mDashBoardVec;
		std::vector < osg::Vec4f > mSignalPointsVec;

		int mCurrDashBoardOnNum;
		int mPrevDashBoardOnNum;

		int mTimer;

		MyApp( vrj::Kernel* kern, int& argc, char** argv );

		~MyApp()
    {
    }

		void appInit();
		int calculateSignalPoint();
		void displayDashBoard();
		void appBufferPreDraw();	
	  void loadDashBoards();
		void appSceneInit();
		void appLatePreFrame();
		
	private:	
		
    std::vector< std::string > mFileNames;
};

#endif // __MYAPP_H__
