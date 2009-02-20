
#ifndef __OGE_DB_H__
#define __OGE_DB_H__

#include "Export.h"
#include "MirageCore/Referenced.h"

#include "MirageCore/MirageOpenGL.h"

#include <string>

using namespace Mirage::MirageCore;

namespace Mirage { namespace MirageCore { class Node; class Image; } }

namespace Mirage
{
	namespace MirageDB
	{
    class MSG_EXPORT FileRead : public Mirage::MirageCore::Referenced
		{
			public:
				
        FileRead()
				{
				}


				FileRead( const FileRead& ogeDB )
				{
				}

				static Node*	readFile( const std::string& fileName );

				/*
					static Image*	readImageFile( const char* fileName );

					static Image*	readImageFile( const std::string& fileName );
				*/

			protected:

				virtual ~FileRead()
				{
				}

			protected:	
		};
	}
}

#endif // __OGE_DB_H__