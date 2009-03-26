
#ifndef __OGE_DB_H__
#define __OGE_DB_H__

#include "Export.h"
#include "Core/Referenced.h"

#include "Core/MirageOpenGL.h"

#include <string>

using namespace Mirage::Core;

namespace Mirage { namespace Core { class Node; class Image; } }

namespace Mirage
{
	namespace System
	{
    class MSG_EXPORT FileRead : public Mirage::Core::Referenced
		{
			public:
				
        FileRead()
				{
				}


				FileRead( const FileRead& ogeDB )
				{
				}

				static Node*	readFile( const std::string& fileName );
				
        static Image*	readImageFile( const std::string& fileName );

			protected:

				virtual ~FileRead()
				{
				}

			protected:	
		};
	}
}

#endif // __OGE_DB_H__