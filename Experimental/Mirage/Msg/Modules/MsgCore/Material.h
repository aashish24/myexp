///////////////////////////////////////////////////////////////////////////////
//
// Defines the attributes of a material. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Export.h"
#include "MsgCore/Object.h"
#include "MsgCore/StateAttribute.h"

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
    class MSG_EXPORT Material : public StateAttribute
		{
			public:

        ///////////////////////////////////////////////////////////////////////
        //
        // Define types of face. 
        //
        ///////////////////////////////////////////////////////////////////////

				enum Face
				{
					FRONT			      = GL_FRONT, 
					BACK			      = GL_BACK, 
					FRONT_AND_BACK  = GL_FRONT_AND_BACK
				};


        ///////////////////////////////////////////////////////////////////////
        //
        // Define types of ColorMode. 
        //
        ///////////////////////////////////////////////////////////////////////

				enum ColorMode
				{
					AMBIENT				      = GL_AMBIENT,
					DIFFUSE				      = GL_DIFFUSE, 
					SPECULAR			      = GL_SPECULAR, 
					AMBIENT_AND_DIFFUSE	= GL_AMBIENT_AND_DIFFUSE,
          SHININESS           = GL_SHININESS
				};


        ///////////////////////////////////////////////////////////////////////
        //
        // Constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				Material() : 
          StateAttribute  ( ),
					mFrontAmbient	  ( Vec4f() ), 
					mFrontDiffuse	  ( Vec4f() ), 
					mFrontSpecular	( Vec4f() ), 
					mFrontShininess	( 0.0 ), 
					mBackAmbient		( Vec4f() ),
					mBackDiffuse		( Vec4f() ), 
					mBackSpecular	  ( Vec4f() ),
					mBackShininess	( 0.0 ), 
					mFrontAndBack		( false )
				{
				}


        ///////////////////////////////////////////////////////////////////////
        //
        // Copy constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				Material( const Material& mat ) :
					StateAttribute  ( mat ), 
					mFrontAmbient   ( mat.mFrontAmbient ), 
					mFrontDiffuse   ( mat.mFrontDiffuse ), 
					mFrontSpecular  ( mat.mFrontSpecular ), 
					mFrontShininess ( mat.mFrontShininess ), 
					mBackAmbient    ( mat.mBackAmbient ),
					mBackDiffuse    ( mat.mBackDiffuse ), 
					mBackSpecular   ( mat.mBackSpecular ),
					mBackShininess  ( mat.mBackShininess ), 
					mFrontAndBack   ( mat.mFrontAndBack )
				{
				}

        
        ///////////////////////////////////////////////////////////////////////
        //
        // Set color components.  
        //
        ///////////////////////////////////////////////////////////////////////

        void	getProperty( ColorMode mode, Vec4f& val, Face face=FRONT ) const;
				void	setProperty( ColorMode mode, const Vec4f& val, Face face=FRONT );								
 
        void	getProperty( ColorMode mode, float& val, Face face=FRONT ) const;
				void	setProperty( ColorMode mode, const float& val, Face face=FRONT );								

        ///////////////////////////////////////////////////////////////////////
        //
        // Check if both FRONT and BACK faces open to material property. 
        //
        ///////////////////////////////////////////////////////////////////////

				bool	enabledFrontAndBack();


        ///////////////////////////////////////////////////////////////////////
        //
        // Uniquely identify this attribute.
        //
        ///////////////////////////////////////////////////////////////////////

        std::string id() const
        {
          return std::string( "Material" );
        }

			
        ///////////////////////////////////////////////////////////////////////
        //
        // Draw function. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void activateStateSet( Node*  node );


			protected:

        ///////////////////////////////////////////////////////////////////////
        //
        // Destructor.
        //
        ///////////////////////////////////////////////////////////////////////

				virtual	~Material()
				{
				}


			protected:

        ///////////////////////////////////////////////////////////////////////
        //
        // Data members. 
        //
        ///////////////////////////////////////////////////////////////////////

				Vec4f	    mFrontAmbient;
				Vec4f	    mFrontDiffuse;
				Vec4f	    mFrontSpecular;
				float	    mFrontShininess;

				Vec4f	    mBackAmbient;
				Vec4f	    mBackDiffuse;
				Vec4f	    mBackSpecular;
				float	    mBackShininess;

				bool	    mFrontAndBack;
		};
	}
}

#endif  __MATERIAL_H__
