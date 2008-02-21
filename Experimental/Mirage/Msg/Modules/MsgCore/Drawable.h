#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "Export.h"
#include "MsgCore/Object.h"
#include "MsgCore/StateSet.h"

#ifdef WIN32
	#include <windows.h>
#endif 

#include "GL/gl.h"

#include <iostream>
#include <vector>

namespace Msg
{
	namespace MsgCore
	{
		class Geode;			

		class OGE_EXPORT Drawable : public Object
		{
			public:
				typedef std::vector< Geode* > Parents; 
				typedef std::vector< GLuint > GLObjectList;

				Drawable();

				Drawable( const Drawable& drawable );

				void addParent( Geode* parent )
				{
					mParents.push_back( parent );
				}

				const Parents getParents() const
				{
					return mParents;
				}

				Parents getParents()
				{
					return mParents;
				}

				unsigned int getNumParents()
				{
					return ( unsigned int )mParents.size();
				}
				
				const StateSet* getStateSet() const
				{
					return mStateSet.get();
				}

				StateSet* getStateSet() 
				{
					return mStateSet.get();
				}

				/*
					const BoundingBox getBound() const 
					{

					}

					void computeBound()
					{

					}
				*/

				void setUseDisplayList( bool flag )
				{
					mUseDisplayList = flag;
				}

				bool getUseDisplayList()
				{
					return mUseDisplayList;
				}

				GLuint& getDisplayList( unsigned int contextID )
				{
					// Only once display list is associated as of now. 
					return mGLObjectList[0];
				}

				virtual void drawImplementation() const 
				{					
				}

				void draw()
				{
					if( mStateSet.valid() )
					{
						mStateSet->drawGLState();
					}

					// If this is not the first time. 
					if( !mGLObjectList.empty() )
					{						
						for( size_t i=0; i < mGLObjectList.size(); ++i )
						{
							glCallList( mGLObjectList[i] );
						}
					}
					else
					{
						GLuint globj;
						std::cout << "[draw] New display list generated" << std::endl;
						globj = glGenLists( 1 );
						mGLObjectList.clear();
						mGLObjectList.push_back( globj );
						glNewList( globj, GL_COMPILE );
							drawImplementation();
						glEndList();
					}
					return;
				}

			protected:
				virtual ~Drawable() 
				{}

			protected:
				Parents					mParents;

				SmartPtr< StateSet >	mStateSet; 

				bool					mUseDisplayList;				

				mutable GLObjectList	mGLObjectList;
		};
	}
}

#endif // __DRAWABLE_H__
