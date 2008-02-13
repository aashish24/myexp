///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GEODE_H__
#define __GEODE_H__

#include <oge/Export.h>

#include <oge/core/BoundingBox.h>
#include <oge/core/Node.h>
#include <oge/core/Drawable.h>

#include <assert.h>

namespace oge
{
	namespace core 
	{
		class Drawable; 

		// Typedefs. 
		typedef std::vector< SmartPtr< Drawable > > DrawableList;

		class OGE_EXPORT Geode : public Node 
		{
			public:
				Geode() :
					Node()
				{
				}

				Geode( const Geode& geode ) :
					Node( geode )
				{
				}

				virtual void addDrawable( Drawable* drawable )
				{
					mDrawables.push_back( drawable );
				}
				
				virtual void removeDrawable( Drawable* drawable )
				{
					// @Todo: implement this. 
				}

				virtual Drawable* getDrawable( const unsigned int& index )
				{
					assert( index < mDrawables.size() );
					return mDrawables[index].get();
				}

				virtual DrawableList getDrawableList()
				{
					return mDrawables;
				}

				void compileDrawables();

				const BoundingBox& getBoundingBox() const
				{
					return mBBox;
				}		

				virtual void traverse( NodeVisitor& nv );

			protected:
				virtual ~Geode();

				mutable BoundingBox	mBBox;

				DrawableList		mDrawables;

			private:
		};
	}
}

#endif // __GEODE_H__