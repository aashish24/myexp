#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Export.h"
#include "MsgCore/Drawable.h"
#include "MsgCore/Array.h"
#include "MsgCore/PrimitiveSet.h"

#include <vector>

namespace Msg
{
	namespace MsgCore
	{		
		class PrimitiveSet;

		class MSG_EXPORT Geometry : public Drawable
		{
			public:
				typedef std::vector< SmartPtr< PrimitiveSet > >	 PrimitiveSets;
        
				enum AttributeBinding
				{
					BIND_PER_PRIMITIVE, 
					BIND_PER_VERTEX
				};

				Geometry();

				Geometry( const Geometry& geometry );

        bool              hasFastPath() const;

        PrimitiveSets&    getPrimitiveSets();

				Vec3Array*			  getVertexArray();
				void				      setVertexArray( Vec3Array* vArray );

				Vec3Array*			  getNormalArray();
				void				      setNormalArray( Vec3Array* nArray );

				Vec3Array*			  getTexCoordArray();
				void				      setTexCoordArray( Vec3Array* texCoordArray );
				
				Vec4Array*			  getColorArray();
				void				      setColorArray( Vec4Array* colorArray );

        Vec3Array*			  getTangentTBNArray();
				void				      setTangetTBNArray( Vec3Array* tangetArray );

        Vec3Array*			  getBinormalTBNArray();
				void				      setBinormalTBNArray( Vec3Array* binormalArray );

        Vec3Array*			  getNormalTBNArray();
				void				      setNormalTBNArray( Vec3Array* binormalArray );

				AttributeBinding	getAttrBinding();
				void				      setAttrBinding( const AttributeBinding& attrBinding );

				Vec3iArray*			  getVertexIndices();
				void				      setVertexIndices( Vec3iArray* viArray );

				Vec3iArray*			  getNormalIndices();
				void				      setNormalIndices( Vec3iArray* niArray );

        Vec3iArray*			  getTextureIndices();
				void				      setTextureIndices( Vec3iArray* niArray );

				void			  	    generateNormals( Geometry::AttributeBinding attrBinding=BIND_PER_VERTEX );

				void				      addPrimitiveSet( PrimitiveSet* primitiveSet );

				virtual void		  drawImplementation();

			protected:
				
        virtual ~Geometry()
				{
				}

			protected:			

        bool                    mFastPath;

				SmartPtr< Vec3Array >	  mVertices;
				SmartPtr< Vec3Array	>	  mNormals;
				SmartPtr< Vec3Array	>	  mTexCoords;
				SmartPtr< Vec4Array >	  mColors;
      
        // For fast path. 
        SmartPtr< Vec3Array >   mNormalArray;
        SmartPtr< Vec3Array >   mTexCoordArray;
        SmartPtr< Vec4Array >	  mColorArray;

        SmartPtr< Vec3Array >   mTangetsTBN;
        SmartPtr< Vec3Array >   mBinormalsTBN;
        SmartPtr< Vec3Array >   mNormalsTBN;  

				SmartPtr< Vec3iArray >	mVertexIndices;
				SmartPtr< Vec3iArray >	mNormalIndices;
        SmartPtr< Vec3iArray >	mTextureIndices;
	
				AttributeBinding		    mAttrBinding;
				PrimitiveSets			      mPrimitiveSets;
		};
	}
}

#endif // __GEOMETRY_H__
