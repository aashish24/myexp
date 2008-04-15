///////////////////////////////////////////////////////////////////////////////
//
// Defines the attributes of a material. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Export.h"
#include "MsgCore/Object.h"

#include "Smtl/Vector.h"

#ifdef _WIN32
	#include <windows.h>
#endif 

#include "GL/glew.h"
#include "GL/gl.h"

using namespace Smtl;

namespace Msg 
{
	namespace MsgCore
	{
		class MSG_EXPORT Material : public Object
		{
			public:
				enum Face
				{
					FRONT			= GL_FRONT, 
					BACK			= GL_BACK, 
					FRONT_AND_BACK  = GL_FRONT_AND_BACK
				};

				enum ColorMode
				{
					AMBIENT				= GL_AMBIENT,
					DIFFUSE				= GL_DIFFUSE, 
					SPECULAR			= GL_SPECULAR, 
					AMBIENT_AND_DIFFUSE	= GL_AMBIENT_AND_DIFFUSE
				};

				Material() : 
					Object				(), 
					mFrontAmbientCom	( Vec4f() ), 
					mFrontDiffuseCom	( Vec4f() ), 
					mFrontSpecularCom	( Vec4f() ), 
					mFrontShininess		( 0.0 ), 
					mBackAmbientCom		( Vec4f() ),
					mBackDiffuseCom		( Vec4f() ), 
					mBackSpecularCom	( Vec4f() ),
					mBackShininess		( 0.0 ), 
					mFrontAndBack		( false )
				{
				}
				
				Material( const Material& mat ) :
					Object			 ( mat ), 
					mFrontAmbientCom ( mat.mFrontAmbientCom ), 
					mFrontDiffuseCom ( mat.mFrontDiffuseCom ), 
					mFrontSpecularCom( mat.mFrontSpecularCom ), 
					mFrontShininess  ( mat.mFrontShininess ), 
					mBackAmbientCom  ( mat.mBackAmbientCom ),
					mBackDiffuseCom  ( mat.mBackDiffuseCom ), 
					mBackSpecularCom ( mat.mBackSpecularCom ),
					mBackShininess   ( mat.mBackShininess ), 
					mFrontAndBack    ( mat.mFrontAndBack )
				{
				}

				void	setAmbient( const Vec4f& ambient, Face face=FRONT );
				Vec4f	getAmbient( Face face=FRONT ) const;

				void	setDiffuse( const Vec4f diffuse, Face face=FRONT );
				Vec4f	getDiffuse( Face face=FRONT ) const;

				void	setSpecular( const Vec4f specular, Face face=FRONT );
				Vec4f	getSpecular( Face face=FRONT ) const;
				
				void	setShininess( float shininess, Face face=FRONT );
				float	getShininess( Face face=FRONT ) const;				

				bool	frontAndBack();

			
			protected:
				virtual	~Material()
				{
				}

			protected:
				Vec4f	mFrontAmbientCom;
				Vec4f	mFrontDiffuseCom;
				Vec4f	mFrontSpecularCom;
				float	mFrontShininess;

				Vec4f	mBackAmbientCom;
				Vec4f	mBackDiffuseCom;
				Vec4f	mBackSpecularCom;
				float	mBackShininess;

				bool	mFrontAndBack;
		};
	}
}

#endif  __MATERIAL_H__
