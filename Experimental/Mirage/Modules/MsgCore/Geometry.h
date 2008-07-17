
#ifndef __MSG_CORE_GEOMETRY_H__
#define __MSG_CORE_GEOMETRY_H__

#include "Export.h"
#include "MsgCore/Drawable.h"
#include "MsgCore/Array.h"
#include "MsgCore/PrimitiveSet.h"

#include "MsgCore/MirageOpenGL.h"

#include <vector>

namespace Msg
{
	namespace MsgCore
	{		
		class PrimitiveSet;

    class MSG_EXPORT Geometry : public MsgCore::Drawable
		{
			public:
				typedef std::vector< SmartPtr< PrimitiveSet > >	 PrimitiveSets;

				enum AttributeBinding
				{
					BIND_PER_PRIMITIVE, 
					BIND_PER_VERTEX
				};

				Geometry( const OpenGLDrawMethod& method = VERTEX_ARRAYS );

				Geometry( const Geometry& geometry );

        bool                      hasFastPath();

        PrimitiveSets&            primitiveSets();

				Vec3Array*			          vertexArray();
				void				              vertexArray( Vec3Array* vArray );

				Vec3Array*			          normalArray();
				void				              normalArray( Vec3Array* nArray );

				Vec3Array*			          textureCoordArray();
				void				              textureCoordArray( Vec3Array* textureCoordArray );
				
				Vec4Array*			          colorArray();
				void				              colorArray( Vec4Array* colorArray );

        Vec3Array*			          tangentArray();
				void				              tangentArray( Vec3Array* tangetArray );

        Vec3Array*			          binormalArray();
				void				              binormalArray( Vec3Array* binormalArray );

				AttributeBinding	        attributeBinding();
				void				              attributeBinding( const AttributeBinding& attrBinding );

				Vec3iArray*			          vertexIndices();
				void				              vertexIndices( Vec3iArray* viArray );

				Vec3iArray*			          normalIndices();
				void				              normalIndices( Vec3iArray* niArray );

        Vec3iArray*			          textureCoordIndices();
				void				              textureCoordIndices( Vec3iArray* niArray );

        const OpenGLDrawMethod&   glDrawMethod() const; 
        void                      glDrawMethod( const OpenGLDrawMethod& method );

				void			  	            generateNormals( Geometry::AttributeBinding attrBinding=BIND_PER_VERTEX );

				void				              addPrimitiveSet( PrimitiveSet* primitiveSet );

				virtual void		          drawImplementation();


			protected:
				
        virtual ~Geometry()
				{
				}


			protected:			

        bool                      _fastPath;

        OpenGLDrawMethod          _glDrawMethod;
        
				SmartPtr< Vec3Array >	    _vertices;
				SmartPtr< Vec3Array	>	    _normals;
				SmartPtr< Vec3Array	>	    _textureCoords;
				SmartPtr< Vec4Array >	    _colors;

        SmartPtr< Vec3Array >     _tangents;
        SmartPtr< Vec3Array >     _binormals;        

				SmartPtr< Vec3iArray >	  _vertexIndices;
				
        SmartPtr< Vec3iArray >	  _normalIndices;
        SmartPtr< Vec3iArray >	  _textureIndices;
	
				AttributeBinding		      _attrBinding;
				PrimitiveSets			        _primitiveSets;
		};
	}
}

#endif // __MSG_CORE_GEOMETRY_H__

