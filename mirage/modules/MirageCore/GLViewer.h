/******************************************************************************
 *
 * Application class. 
 *
 ******************************************************************************
 */

#ifndef __GL_VIEWER_H__
#define __GL_VIEWER_H__

#include <windows"
#include <GL/gl"
#include <GL/glu"
#include <GL/glut"

#include <MirageCore/Navigation"

#include <glControl/Keys"
#include <glControl/Action"
#include <glControl/ActionHandler"

#include <MirageUtil/AnimationManager"
#include <MirageUtil/Animation"

#include <MirageCore/Navigation"

#include <gmtl/Math"
#include <gmtl/MatrixOps"
#include <gmtl/gmtl"
#include <gmtl/Math"
#include <gmtl/Vec"
#include <gmtl/VecOps"

namespace MirageCore
{
	class SceneManager;
	class User;	
}

namespace MirageUtil
{
	class Animation ;
	class Timer;
}

using namespace glControl;

namespace MirageCore
{
	class GLViewer
	{
		public:	
			GLViewer();
			~GLViewer();						

			void init();
			void draw();
			void drawControls();
			void idle();

			void setInputArea( int width, int height );

			void clearGLBuffers();

			Action getAction( const Keys key );
			Action getAction( const MouseButtons mouseButton );

			void updateMouse( const MouseButtons mouseButton, int state, int x, int y );

			bool isDisplayStateChanged();
			void setDisplayStateChanged( bool val );
		
			void takeAction( const Keys key, int x, int y );
			void takeAction( int x, int y );

			

		private:
			ActionHandler mActionHandler;

			/******************************************************************
			 * 
			 * Flag to check if the scene has been changed and display needs to 
			 * be refreshed. 
			 * 
			 ******************************************************************
			 */
			bool   mDisplayStateChanged;
			
			/******************************************************************
			 * 
			 * Mouse last position on the screen. 
			 * 
			 ******************************************************************
			 */
			float mLastPos[3];		

			/******************************************************************
			 * 
			 * Object that manages and draw a scene. 
			 * 
			 ******************************************************************
			 */
			MirageCore::SceneManager* mSceneManager;

			/******************************************************************
			 * 
			 * Object that manages and draw a scene. 
			 * 
			 ******************************************************************
			 */
			MirageUtil::AnimationManager* mAnimationMgr;

			/******************************************************************
			 *
			 * Display area. 
			 *
			 ******************************************************************
			 */
			GLint mWidth;
			GLint mHeight;
			GLint mWinHeight;
			GLint mWinWidth;
			
			/******************************************************************
			 *
			 * Navigation. 
			 *
			 ******************************************************************
			 */
			Navigation* mNav;			

			/******************************************************************
			 *
			 * Flags. 
			 *
			 ******************************************************************
			 */
			bool mAnimate;
			bool mIsManual;
			bool mIsAtStart;
			bool mIsAtFinish;
			bool mStartManual;
			
			/******************************************************************
			 *
			 * Timer object. 
			 *
			 ******************************************************************
			 */
			MirageUtil::Timer* mTimer;

			/******************************************************************
			 *
			 * Number of users and their ids. 
			 *
			 ******************************************************************
			 */
			int mMaxNoUsers;
			std::map< const std::string, User* > mUsers; 			
	};
}

#endif // __GL_VIEWER_H__
