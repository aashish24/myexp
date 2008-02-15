#ifndef __GLUT_TEXT_H__
#define __GLUT_TEXT_H__

#include<glCore/Text.h>
#include<glCore/GLTextFactory.h>

namespace glCore
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
	glCore::Text* create()
	{
		return new glCore::GlutText();
	}

	bool isRegis = glCore::GLTextFactory::instance()->tRegister( "GlutText", create );
}

#endif // __GLUT_TEXT_H__