///////////////////////////////////////////////////////////////////////////////
//
// Defines the attributes of a material. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Export.h"
#include "Core/Object.h"
#include "Core/StateAttribute.h"
#include "Core/MirageOpenGL.h"

#include "Math/Vec.h"

#ifdef _WIN32
	#include <windows.h>
#endif 

#include "GL/glew.h"
#include "GL/gl.h"

namespace Mirage 
{
	namespace Core
	{
    class MSG_EXPORT Material : public StateAttribute
		{
			public:     


        ///////////////////////////////////////////////////////////////////////
        //
        // Constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				Material() : 
          StateAttribute  ( ),
					mFrontAmbient	  ( Math::Vec4f() ), 
					mFrontDiffuse	  ( Math::Vec4f() ), 
					mFrontSpecular	( Math::Vec4f() ), 
					mFrontShininess	( 0.0 ), 
          mBackAmbient		( Math::Vec4f() ),
					mBackDiffuse		( Math::Vec4f() ), 
					mBackSpecular	  ( Math::Vec4f() ),
					mBackShininess	( 0.0 ), 
          mFront          ( true ), 
          mBack           ( false )					
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
				  mFront          ( mat.mFront ), 
          mBack           ( mat.mBack )          
				{
				}

        
        ///////////////////////////////////////////////////////////////////////
        //
        // Set color components.  
        //
        ///////////////////////////////////////////////////////////////////////

        void getProperty( LightMode mode, Math::Vec4f& val, Face face=FRONT ) const;
				void setProperty( LightMode mode, const Math::Vec4f& val, Face face=FRONT );								
 
        void getProperty( LightMode mode, float& val, Face face=FRONT ) const;
				void setProperty( LightMode mode, const float& val, Face face=FRONT );								


        void enable( const Face& face );


        ///////////////////////////////////////////////////////////////////////
        //
        // Check if both FRONT and BACK faces open to material property. 
        //
        ///////////////////////////////////////////////////////////////////////

				bool enabledFrontAndBack();


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
        // Initialization. 
        //
        ///////////////////////////////////////////////////////////////////////
        
        virtual void init(){;}


        ///////////////////////////////////////////////////////////////////////
        //
        // Context specific initialization. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void contextInit(){;}


        ///////////////////////////////////////////////////////////////////////
        //
        // Activate OpenGL states. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void activate( Node*  node );



        ///////////////////////////////////////////////////////////////////////
        //
        // Activate OpenGL states. 
        //
        ///////////////////////////////////////////////////////////////////////

        virtual void deActivate( Node*  node );


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

        Math::Vec4f	    mFrontAmbient;
				Math::Vec4f	    mFrontDiffuse;
				Math::Vec4f	    mFrontSpecular;
				float	              mFrontShininess;

				Math::Vec4f	    mBackAmbient;
				Math::Vec4f	    mBackDiffuse;
				Math::Vec4f	    mBackSpecular;
				float	              mBackShininess;

        bool                mFront; 
        bool                mBack;      
        bool                mFrontAndBack;
		};
	}
}

#endif  __MATERIAL_H__
