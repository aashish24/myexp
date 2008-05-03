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

        bool              hasFastPath();

        PrimitiveSets&    getPrimitiveSets();

				Vec3Array*			  getVertexArray();
				void				      setVertexArray( Vec3Array* vArray );

				Vec3Array*			  getNormalArray();
				void				      setNormalArray( Vec3Array* nArray );

				Vec3Array*			  getTexCoordArray();
				void				      setTexCoordArray( Vec3Array* texCoordArray );
				
				Vec4Array*			  getColorArray();
				void				      setColorArray( Vec4Array* colorArray );

        Vec3Array*			  getTangentArray();
				void				      setTangentArray( Vec3Array* tangetArray );

        Vec3Array*			  getBinormalArray();
				void				      setBinormalArray( Vec3Array* binormalArray );

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

        SmartPtr< Vec3Array >   mTangents;
        SmartPtr< Vec3Array >   mBinormals;        

				SmartPtr< Vec3iArray >	mVertexIndices;
				
        SmartPtr< Vec3iArray >	mNormalIndices;
        SmartPtr< Vec3iArray >	mTextureIndices;
	
				AttributeBinding		    mAttrBinding;
				PrimitiveSets			      mPrimitiveSets;
		};
	}
}

#endif // __GEOMETRY_H__
