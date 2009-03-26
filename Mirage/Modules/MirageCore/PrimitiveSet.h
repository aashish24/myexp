
#ifndef __PRIMITIVE_SET_H__
#define __PRIMITIVE_SET_H__

#include <vector>

#include "Core/Object.h"

namespace Mirage 
{
	namespace Core 
	{
		class MSG_EXPORT VectorGLubyte: public std::vector< GLubyte >
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


		class MSG_EXPORT VectorGLushort: public std::vector< GLushort >
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


		class MSG_EXPORT VectorGLuint: public std::vector< GLuint >
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
		class  MSG_EXPORT PrimitiveSet : public Object
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
					POINTS			    = GL_POINTS,
					LINES			      = GL_LINES,
					LINE_STRIP		  = GL_LINE_STRIP,
					LINE_LOOP		    = GL_LINE_LOOP,					
					TRIANGLES		    = GL_TRIANGLES,
					TRIANGLE_STRIP	= GL_TRIANGLE_STRIP,
					TRIANGLE_FAN  	= GL_TRIANGLE_FAN,					
					QUADS			      = GL_QUADS,
					QUAD_STRIP		  = GL_QUAD_STRIP,
					POLYGON			    = GL_POLYGON
				};


				PrimitiveSet( GLenum mode, Type type ) :
					_mode( mode ), 
					_type( type )
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
					return _type;
				}


				GLenum getMode()
				{
					return _mode;
				}


				virtual unsigned int getSize() const = 0;


			protected:
				
        virtual ~PrimitiveSet()
				{
				}


			protected:
				
        GLenum	_mode;

				Type	  _type;				
		};


		class MSG_EXPORT DrawElementsUByte : public PrimitiveSet, public VectorGLubyte 
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
					glDrawElements( _mode, ( GLsizei )size(), _type,  &front() );
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


		class MSG_EXPORT DrawElementsUShort : public PrimitiveSet, public VectorGLushort 
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
					glDrawElements( _mode, ( GLsizei )size(), _type,  &front() );
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


		class MSG_EXPORT DrawElementUInt : public PrimitiveSet, public VectorGLuint 
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
					glDrawElements( _mode, ( GLsizei ) size(), _type,  &front() );
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
