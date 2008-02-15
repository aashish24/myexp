/******************************************************************************
 *
 * Defines the scene. 
 *
 ******************************************************************************
 */

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <map>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <glMath/Vector.h>

#include <glCore/Texture.h>

using namespace glMath;

namespace glCore
{
	class Text;
}

namespace glCore
{
	class SceneManager
	{
		public:
			SceneManager();
			virtual ~SceneManager()
			{}

			void init();
			GLuint createLabyrinth();
			GLuint createCar( double size );
			GLuint createBox( double size );
			GLuint createFillBox( double size, const GLubyte* mask );
			GLuint createStarA( double size );
			void createStar();
			
			void setInitialPos( unsigned int index, Vec3f pos );
			Vec3f getInitialPos( unsigned int index );
			void setCurrentPos( unsigned int index, Vec3f pos );
			Vec3f getCurrentPos( unsigned int index );

			void setInitialRot( unsigned int index, Vec4f rot );
			Vec4f getInitialRot( unsigned int index );
			void setCurrentRot( unsigned int index, Vec4f pos );
			Vec4f getCurrentRot( unsigned int index );

			void setNoOfEnemies( long int count );
			long int getNoOfEnemies();

			Text* getText( unsigned int i );
			Text* getCtrlText( unsigned int i );

			virtual void draw();
			virtual void drawControls();

			public:
				GLuint mLabyrinthID;
				GLuint mCarID;
				GLuint mBoxID;
				GLuint mStarID;			
				GLuint mAnimeBoxID1;	
				GLuint mAnimeBoxID2;	
				std::vector< GLuint > mEnemyCars;
				Texture gTexture[4];

			private:
				std::map< unsigned int, Vec3f > mMapIndexToCurrPos;
				std::map< unsigned int, Vec3f > mMapIndexToInitPos;
				std::map< unsigned int, Vec4f > mMapIndexToCurrRot;
				std::map< unsigned int, Vec4f > mMapIndexToInitRot;

				/******************************************************************
				 *
				 * Text objects in the scene. 
				 *
				 ******************************************************************
				 */
				std::vector< Text* > mTexts;

				/******************************************************************
				 *
				 * Text objects in the controls. 
				 *
				 ******************************************************************
				 */
				std::vector< Text* > mCtrlTexts;


				long int mNoOfEnemies;
		};	
}

#endif // __SCENE_MANAGER_H__
