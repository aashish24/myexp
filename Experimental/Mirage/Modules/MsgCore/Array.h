
#ifndef __MSG_CORE_ARRAY_H__
#define __MSG_CORE_ARRAY_H__

#include "Export.h"
#include "MsgCore/Object.h"

#include "MsgMath/Vector.h"

#include "GL/glew.h"
#include "GL/gl.h"

#include <vector>

namespace Msg
{
	namespace MsgCore
	{
		template< class T, unsigned int SIZE >
		class MSG_EXPORT Array : public Object, public std::vector< T >
		{
			public:
			  
        Array() :
				  _dataSize( SIZE )
			  {
			  }

				Array( const Array& tArray ) :					
				  std::vector< T >( tArray ), 
				  _dataSize( tArray._dataSize )
				{

				}

        Array( size_t count ) : 
        std::vector< T >( count ), 
          _dataSize( SIZE )
        {
        }

				virtual const GLvoid* getDataPointer() const
				{
					if( !this->empty() )
					{
						return &( this->front() );
					}
					else
					{
						return 0;
					}
				}
			
			protected:
				
        virtual ~Array()
				{
				}
			
			protected: 
				
        size_t	_dataSize;								
		};
	
		// Typedefs. 
		typedef Array< GLbyte, 1 >		          ByteArray;
		typedef Array< GLshort, 1 >		          ShortArray;
		typedef Array< GLint, 1 >		            IntArray;
		typedef Array< GLubyte, 1 >		          UByteArray;
		typedef Array< GLushort, 1 >	          UShortArray;		
		typedef Array< GLuint, 1 >		          UIntArray;

		typedef Array< GLfloat, 1 >		          FloatArray;

    typedef Array< MsgMath::Vec2f, 2 >		  Vec2fArray;
		typedef Array< MsgMath::Vec3f, 3 >		  Vec3fArray;
		typedef Array< MsgMath::Vec4f, 4 >		  Vec4fArray;

		typedef Array< MsgMath::Vec2d, 2 >		  Vec2Array;
		typedef Array< MsgMath::Vec3d, 3 >		  Vec3Array;
		typedef Array< MsgMath::Vec4d, 4 >		  Vec4Array;

		typedef Array< MsgMath::Vec2i, 2 >		  Vec2iArray;
		typedef Array< MsgMath::Vec3i, 3 >		  Vec3iArray;
		typedef Array< MsgMath::Vec4i, 4 >	    Vec4iArray;

		typedef Array< MsgMath::Vec2ui, 2 >		  Vec2uiArray;
		typedef Array< MsgMath::Vec3ui, 3 >		  Vec3uiArray;
		typedef Array< MsgMath::Vec4ui, 4 >		  Vec4uiArray;
	}
}

#endif // __MSG_CORE_ARRAY_H__
