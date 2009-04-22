
#ifndef __MIRAGE_CORE_IMAGE_H__
#define __MIRAGE_CORE_IMAGE_H__

#include "Export.h"

#include "Core/Referenced.h"

#include "GL/glew.h"

namespace Mirage
{
	namespace Core
	{
		class MSG_EXPORT Image : public Referenced
		{
			public:
				
        Image();
				Image( const Image& image );

        const unsigned char* const getData() const
        {
          return _data;
        }

        unsigned char* editData() 
        {
          return _data;
        }


        void setData( unsigned char* data )
        {
          _data = data;
        }


        unsigned  getWidth() 
        {
          return _width;
        }


        unsigned getHeight()
        {
          return _height;
        }


        float getAspect()
        {
          return _aspect;
        }


      protected: 

        virtual ~Image()
        {
        }


      public: 

        unsigned        _width;
        unsigned        _height;
        float           _aspect;
        unsigned char*  _data;
        GLenum          _format;

		};
	}
}

#endif  __MIRAGE_CORE_IMAGE_H__

