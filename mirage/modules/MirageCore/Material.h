///////////////////////////////////////////////////////////////////////////////
//
// Defines the attributes of a material. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Export.h"
#include "MirageCore/Object.h"
#include "MirageCore/StateAttribute.h"
#include "MirageCore/MirageOpenGL.h"

#include "MirageMath/Vector.h"

#ifdef _WIN32
	#include <windows.h>
#endif 

#include "GL/glew.h"
#include "GL/gl.h"

namespace Mirage 
{
	namespace MirageCore
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
					mFrontAmbient	  ( MirageMath::Vec4f() ), 
					mFrontDiffuse	  ( MirageMath::Vec4f() ), 
					mFrontSpecular	( MirageMath::Vec4f() ), 
					mFrontShininess	( 0.0 ), 
          mBackAmbient		( MirageMath::Vec4f() ),
					mBackDiffuse		( MirageMath::Vec4f() ), 
					mBackSpecular	  ( MirageMath::Vec4f() ),
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

        void getProperty( LightMode mode, MirageMath::Vec4f& val, Face face=FRONT ) const;
				void setProperty( LightMode mode, const MirageMath::Vec4f& val, Face face=FRONT );								
 
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

        MirageMath::Vec4f	    mFrontAmbient;
				MirageMath::Vec4f	    mFrontDiffuse;
				MirageMath::Vec4f	    mFrontSpecular;
				float	              mFrontShininess;

				MirageMath::Vec4f	    mBackAmbient;
				MirageMath::Vec4f	    mBackDiffuse;
				MirageMath::Vec4f	    mBackSpecular;
				float	              mBackShininess;

        bool                mFront; 
        bool                mBack;      
        bool                mFrontAndBack;
		};
	}
}

#endif  __MATERIAL_H__
