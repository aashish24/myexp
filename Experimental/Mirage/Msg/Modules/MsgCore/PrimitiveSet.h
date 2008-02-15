#ifndef __PRIMITIVE_SET_H__
#define __PRIMITIVE_SET_H__

#include <vector>

#include <oge/core/Object.h>

namespace oge 
{
	namespace core 
	{
		class OGE_EXPORT VectorGLubyte: public std::vector< GLubyte >
		{
			typedef std::vector< value_type > vector_type;
			
			public:    
				VectorGLubyte(): vector_type() 
				{
				}
				
				VectorGLubyte( const VectorGLubyte &copy ): 
					vector_type(copy) 
				{
				}

				VectorGLubyte( GLubyte* beg, GLubyte* end ) : 
					vector_type( beg, end ) 
				{
				}

				explicit VectorGLubyte( unsigned int n ) : 
					vector_type( n ) 
				{
				}
		};

		class OGE_EXPORT VectorGLushort: public std::vector< GLushort >
		{
			typedef std::vector< value_type > vector_type;
			
			public:    
				VectorGLushort(): 
					vector_type() 
				{
				}

				VectorGLushort( const VectorGLushort &copy ) : 
					vector_type(copy) 
				{
				}

				VectorGLushort( GLushort* beg, GLushort* end ): 
					vector_type( beg, end ) 
				{
				}

					explicit VectorGLushort( unsigned int n ) : 
					vector_type( n ) 
				{
				}
		};

		class OGE_EXPORT VectorGLuint: public std::vector< GLuint >
		{
			typedef std::vector< value_type > vector_type;
			
			public:    
				VectorGLuint(): 
					vector_type() 
				{
				}

				VectorGLuint( const VectorGLuint &copy ) : 
					vector_type(copy) 
				{
				}

				VectorGLuint( GLuint* beg, GLuint* end ): 
					vector_type( beg, end ) 
				{
				}

					explicit VectorGLuint( unsigned int n ) : 
					vector_type( n ) 
				{
				}
		};

		// As of now it will draw only use the glDrawElements. 
		class  OGE_EXPORT PrimitiveSet : public Object
		{
			public:
				enum Type
				{
					BYTE  = GL_UNSIGNED_BYTE,
					SHORT = GL_UNSIGNED_SHORT, 
					INT   = GL_UNSIGNED_INT
				};

				enum Mode
				{
					POINTS			= GL_POINTS,
					LINES			= GL_LINES,
					LINE_STRIP		= GL_LINE_STRIP,
					LINE_LOOP		= GL_LINE_LOOP,					
					TRIANGLES		= GL_TRIANGLES,
					TRIANGLE_STRIP	= GL_TRIANGLE_STRIP,
					TRIANGLE_FAN	= GL_TRIANGLE_FAN,					
					QUADS			= GL_QUADS,
					QUAD_STRIP		= GL_QUAD_STRIP,
					POLYGON			= GL_POLYGON
				};

				PrimitiveSet( GLenum mode, Type type ) :
					mMode( mode ), 
					mType( type )
				{
				}

				PrimitiveSet( const PrimitiveSet& primitiveSet ) :
					Object( primitiveSet )
				{
				}

				// This should be overridden in the derived class. 
				virtual void draw() const = 0;

				Type getType()
				{
					return mType;
				}

				GLenum getMode()
				{
					return mMode;
				}

				virtual unsigned int getSize() const = 0;

			protected:
				virtual ~PrimitiveSet()
				{
				}

			protected:
				GLenum	mMode;

				Type	mType;				
		};

		class OGE_EXPORT DrawElementsUByte : public PrimitiveSet, public VectorGLubyte 
		{
			public:
				DrawElementsUByte( GLenum mode=0 ) :
					PrimitiveSet( mode, BYTE )
				{
				}

				DrawElementsUByte( const DrawElementsUByte& drawElemUByte ) :
					PrimitiveSet( drawElemUByte )
				{
				}

				virtual void draw() const 
				{
					glDrawElements( mMode, ( GLsizei )size(), mType,  &front() );
				}
		
				virtual size_t getSize() const
				{
					return size();
				}

			protected:
				virtual ~DrawElementsUByte()
				{
				}

		};

		class OGE_EXPORT DrawElementsUShort : public PrimitiveSet, public VectorGLushort 
		{
			public:
				DrawElementsUShort( GLenum mode=0 ) :
					PrimitiveSet( mode, SHORT )
				{
				}

				DrawElementsUShort( const DrawElementsUShort& drawElementUShort ) :
					PrimitiveSet( drawElementUShort )
				{
				}

				virtual void draw() const 
				{
					glDrawElements( mMode, ( GLsizei )size(), mType,  &front() );
				}


				virtual size_t getSize() const
				{
					return size();
				}
			protected:
				virtual ~DrawElementsUShort()
				{
				}
		};

		class OGE_EXPORT DrawElementUInt : public PrimitiveSet, public VectorGLuint 
		{
			public:				
				DrawElementUInt( GLenum mode=0 ) :
				  PrimitiveSet( mode, INT )
				{
				}

				DrawElementUInt( const DrawElementUInt& drawElementUInt )
					: PrimitiveSet( drawElementUInt )
				{
				}

				virtual void draw() const 
				{
					std::cout << " testing: " << std::endl;
					std::cout << " size is: " << size() << std::endl;					
					glDrawElements( mMode, ( GLsizei ) size(), mType,  &front() );
				}				

				virtual size_t getSize() const
				{
					return size();
				}

			protected:
				virtual ~DrawElementUInt()
				{
				}
		};
	}	
}

#endif // __PRIMITIVE_SET_H__