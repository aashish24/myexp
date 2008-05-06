
#ifndef __MSG_UTIL_STRING_H__
#define __MSG_UTIL_STRING_H__

#include "Msg/MsgCore/Referenced.h"

#include <string>

namespace Msg
{
	namespace MsgUtil
	{
    class String : public Msg::MsgCore::Referenced
    {
      ///////////////////////////////////////////////////////////////////////////
      //
      // Convert all characters in a string to uppercase characters. 
      //
      ///////////////////////////////////////////////////////////////////////////

		  static std::string& toUpper( std::string& str )
		  {
        // If empty. 
        if( str.empty() )
        {
          return str;
        }

			  char* aCharArray = new char[str.length() + 1];
			  strcpy( aCharArray, str.c_str() );

			  unsigned int i = 0;
  			
        for( i=0; i < str.size(); ++i )
			  {
				  aCharArray[i] = toupper(aCharArray[i]);
			  }

			  aCharArray[i] = '\0';

			  str = std::string(aCharArray);
			  delete aCharArray;
			  return str;
		  }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Convert all characters in a string to lowercase characters. 
      //
      ///////////////////////////////////////////////////////////////////////////

		  static char* toUpper( char* str )
		  {
        if( !str )
        {
          return str;
        }

        // @Todo: Implement this. 
		  }
    };
	}
}

#endif // __MSG_UTIL_STRING_H__
