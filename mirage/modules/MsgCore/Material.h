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
#include "MsgCore/MirageOpenGL.h"

#include "MsgMath/Vector.h"

#ifdef _WIN32
	#include <windows.h>
#endif 

#include "GL/glew.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include "GL/gl.h"
#endif

namespace Msg 
{
	namespace MsgCore
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
					mFrontAmbient	  ( MsgMath::Vec4f() ), 
					mFrontDiffuse	  ( MsgMath::Vec4f() ), 
					mFrontSpecular	( MsgMath::Vec4f() ), 
					mFrontShininess	( 0.0 ), 
          mBackAmbient		( MsgMath::Vec4f() ),
					mBackDiffuse		( MsgMath::Vec4f() ), 
					mBackSpecular	  ( MsgMath::Vec4f() ),
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

        void getProperty( LightMode mode, MsgMath::Vec4f& val, Face face=FRONT ) const;
				void setProperty( LightMode mode, const MsgMath::Vec4f& val, Face face=FRONT );								
 
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

        MsgMath::Vec4f	    mFrontAmbient;
				MsgMath::Vec4f	    mFrontDiffuse;
				MsgMath::Vec4f	    mFrontSpecular;
				float	              mFrontShininess;

				MsgMath::Vec4f	    mBackAmbient;
				MsgMath::Vec4f	    mBackDiffuse;
				MsgMath::Vec4f	    mBackSpecular;
				float	              mBackShininess;

        bool                mFront; 
        bool                mBack;      
        bool                mFrontAndBack;
		};
	}
}

#endif  __MATERIAL_H__
