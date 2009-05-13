
// Mirage includes. 
#include "Core/Image.h"

// GL includes. 
#include "GL/glew.h"

namespace Mirage
{
	namespace Core
	{
    Image::Image() : 
      _width  ( 0 ), 
      _height ( 0 ), 
      _aspect ( 0 ), 
      _data   ( 0 ), 
      _format ( GL_RGB )
    {
    }
		
    
    Image::Image( const Image& image )
    {
    }
  }
}


