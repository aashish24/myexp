
#ifndef __MSG_CORE_GEODE_H__
#define __MSG_CORE_GEODE_H__

#include "Export.h"

#include "MirageCore/BoundingBox.h"
#include "MirageCore/Node.h"
#include "MirageCore/Group.h"
#include "MirageCore/Drawable.h"

#include <assert.h>

namespace Mirage
{
	namespace MirageCore 
	{
		class Drawable; 

		// Typedefs. 
		typedef std::vector< SmartPtr< Drawable > > DrawableList;

    class MSG_EXPORT Geode : public Mirage::MirageCore::Group 
		{
			public:
				Geode() :
					Group()
				{
				}

				Geode( const Geode& geode ) :
					Group( geode )
				{
				}


				virtual void addDrawable( Drawable* drawable )
				{
          if( drawable )
          {
            _drawables.push_back( drawable );
            drawable->addParent( static_cast< Group* >( this ) );
          }
				}

				
				virtual void removeDrawable( Drawable* drawable )
				{
					// @Todo: implement this. 
				}


				virtual Drawable* getDrawable( const unsigned int& index )
				{
					assert( index < _drawables.size() );
					return _drawables[index].get();
				}


				virtual DrawableList getDrawableList()
				{
					return _drawables;
				}


				void compileDrawables();


				const BoundingBox& getBoundingBox() const
				{
					return _boundingBox;
				}		


				virtual void traverse( NodeVisitor& nv );


			protected:

				virtual ~Geode();

				mutable BoundingBox	  _boundingBox;

				DrawableList		      _drawables;
		};
	}
}

#endif // __MSG_CORE_GEODE_H__
