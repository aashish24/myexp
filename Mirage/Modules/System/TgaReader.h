
#ifndef __SYSTEM_TGA_READER_H__
#define __SYSTEM_TGA_READER_H__

// C++ includes. 
#include <string>

#include "Core/Image.h"
#include "Core/SmartPtr.h"

namespace Mirage
{
  namespace System
  {
    class TgaReader
    {
        public:
        
          TgaReader( void );
          explicit TgaReader( const std::string& name );

         ~TgaReader();
          
          void read( const std::string& name );

          const Core::Image* const getImage() const;
          Core::Image*             editImage();

      private: 

        Core::SmartPtr< Core::Image > _image;
    };
  }
}

#endif // __SYSTEM_TGA_READER_H__

