#ifndef __GLUT_TEXT_H__
#define __GLUT_TEXT_H__

#include "MirageCore/Text"
#include "MirageCore/GLTextFactory"

namespace MirageCore
{
	class GlutText : public Text
	{
		public:
			virtual void draw()
			{
				// TODO:
				// Allocate on run time. 
				char buff[1000];
				strcpy( buff, mText.c_str() );				
				glPushMatrix();
					glLoadIdentity();
					//glTranslatef( mPos[0], mPos[1], mPos[2] );
					//glScalef( mScale[0], mScale[1], mScale[2] );					
					glRasterPos2f( mPos[0], mPos[1] );
					int i=0;					
					while( buff[i] != '\0' )
					{
						glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, buff[i] );
						++i;
					}
				glPopMatrix();
			}
			
	};
}

namespace 
{
	MirageCore::Text* create()
	{
		return new MirageCore::GlutText();
	}

	bool isRegis = MirageCore::GLTextFactory::instance()->tRegister( "GlutText", create );
}

#endif // __GLUT_TEXT_H__