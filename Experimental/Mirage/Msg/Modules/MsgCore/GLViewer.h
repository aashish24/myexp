/******************************************************************************
 *
 * Application class. 
 *
 ******************************************************************************
 */

#ifndef __GL_VIEWER_H__
#define __GL_VIEWER_H__

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <glCore/Navigation.h>

#include <glControl/Keys.h>
#include <glControl/Action.h>
#include <glControl/ActionHandler.h>

#include <glUtil/AnimationManager.h>
#include <glUtil/Animation.h>

#include <glCore/Navigation.h>

#include <gmtl/Math.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/gmtl.h>
#include <gmtl/Math.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace glCore
{
	class SceneManager;
	class User;	
}

namespace glUtil
{
	class Animation ;
	class Timer;
}

using namespace glControl;

namespace glCore
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
			glCore::SceneManager* mSceneManager;

			/******************************************************************
			 * 
			 * Object that manages and draw a scene. 
			 * 
			 ******************************************************************
			 */
			glUtil::AnimationManager* mAnimationMgr;

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
			glUtil::Timer* mTimer;

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
