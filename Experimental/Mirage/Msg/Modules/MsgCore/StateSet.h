#ifndef __STATE_SET_H__
#define __STATE_SET_H__

#include "MsgCore/Material.h"

namespace Msg
{
	namespace MsgCore
	{
		class MSG_EXPORT StateSet : public Object 
		{
			public:
				StateSet() : 
					Object()
				{
				}

				StateSet( const StateSet& stateset ) :
					Object( stateset )
				{
				}

				void setMaterial( Material* mat )
				{
					mMaterial = mat;
				}

				Material* getMaterial()
				{
					return mMaterial.get();
				}

				void drawGLState()
				{
					if( mMaterial.valid() )
					{
						glMaterialfv( GL_FRONT,	GL_AMBIENT,		
									  mMaterial->getAmbient().front() );
						glMaterialfv( GL_FRONT,	GL_DIFFUSE,		
									  mMaterial->getDiffuse().front() );
						glMaterialfv( GL_FRONT, GL_SPECULAR,	
									  mMaterial->getSpecular().front() );					

						glMaterialfv( GL_BACK, GL_AMBIENT,		
									  mMaterial->getAmbient( Material::BACK ).front() );
						glMaterialfv( GL_BACK,	GL_DIFFUSE,		
									  mMaterial->getDiffuse( Material::BACK ).front() );
						glMaterialfv( GL_BACK, GL_SPECULAR,	
									  mMaterial->getSpecular( Material::BACK ).front() );
					}					
				}
	
			protected:
				virtual ~StateSet()
				{
				}

			protected:
				SmartPtr< Material >	mMaterial;
		};
	}
}

#endif // __STATE_SET_H__
