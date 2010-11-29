#ifdef WIN32
#define OS	"WINDOWS"
#else
#define OS "OTHER"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TextFileReadWrite.h"

namespace Msg
{
  namespace MsgDB
  {
    char* TextFileReadWrite::read( char *fn ) 
    {
      FILE *fp;
	    char *content = NULL;

	    int count=0;

	    if (fn != NULL) 
      {
		  #ifdef WIN32
		    fopen_s( &fp, fn,"rt" );
		  #else
			 fp=fopen(fn,"rt" );
		  #endif
		    if ( fp != NULL ) 
        {
          
          fseek( fp, 0, SEEK_END );
          count = ftell( fp );
          rewind( fp );

			    if ( count > 0) 
          {
				    content = ( char* )malloc( sizeof( char ) * ( count+1 ) );
				    count = fread( content,sizeof( char ),count,fp );
				    content[count] = '\0';
			    }
			    fclose( fp );
		    }
	    }
	    return content;
    }


    int TextFileReadWrite::write(char *fn, char *s) 
    {

	    FILE *fp;
	    int status = 0;

	    if (fn != NULL) {
		#ifdef WIN32
		    fopen_s( &fp, fn, "w" );
		#else
			fp=fopen(fn, "w" );
		#endif

		    if (fp != NULL) 
        {    			
			    if ( fwrite( s, sizeof( char ), strlen( s ),fp ) == strlen( s ) )
				    status = 1;
			    fclose( fp );
		    }
	    }
	    return( status );
    }
  }
}
