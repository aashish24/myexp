
#ifndef __STRING_H__
#define __STRING_H__

#include <string>

namespace oge
{
	namespace util
	{
		std::string& toUpper( std::string& str )
		{

			char* aCharArray = new char[str.length() + 1];
			strcpy(aCharArray, str.c_str());

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

		char* toUpper( char* str )
		{
			;			
		}

	}
}

#endif // __STRING_H__