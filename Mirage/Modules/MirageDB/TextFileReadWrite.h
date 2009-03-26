
#ifndef __MSG_DB_TEXT_FILE_READ_WRITE_H__
#define __MSG_DB_TEXT_FILE_READ_WRITE_H__

#include "Export.h"

namespace Mirage
{
  namespace System
  {
    class MSG_EXPORT TextFileReadWrite
    {
      public: 

        /////////////////////////////////////////////////////////////////////////////
        //
        // Parse a ASCII shader. 
        //
        /////////////////////////////////////////////////////////////////////////////

        static char *read( char *fn );

        
        /////////////////////////////////////////////////////////////////////////////
        //
        // Write shader as ASCII file.
        //
        /////////////////////////////////////////////////////////////////////////////

        static int write( char *fn, char *s );
    };
  }
}

#endif // __MSG_DB_TEXT_FILE_READ_WRITE_H__

