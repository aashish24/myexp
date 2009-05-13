
#ifndef __SYSTEM_TGA_READER_H__
#define __SYSTEM_TGA_READER_H__

// C++ includes. 
#include <string>

#include "Core/Image.h"
#include "Core/SmartPtr.h"
#include "Core/Object.h"

namespace Mirage
{
  namespace System
  {
    class TgaReader : public Core::Object
    {
        public:
        
          TgaReader( void );          
          
          Core::SmartPtr<Core::Image> read( const std::string& name );


        protected: 

         ~TgaReader();

    };
  }
}

#endif // __SYSTEM_TGA_READER_H__

