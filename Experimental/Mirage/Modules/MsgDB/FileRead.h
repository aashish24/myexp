
#ifndef __OGE_DB_H__
#define __OGE_DB_H__

#include "Export.h"
#include "MsgCore/Referenced.h"

#include "MsgCore/MirageOpenGL.h"

#include <string>

using namespace Msg::MsgCore;

namespace Msg { namespace MsgCore { class Node; class Image; } }

namespace Msg
{
	namespace MsgDB
	{
    class MSG_EXPORT FileRead : public Msg::MsgCore::Referenced
		{
			public:
				
        FileRead()
				{
				}


				FileRead( const FileRead& ogeDB )
				{
				}

				static Node*	readFile( const char* fileName, const MsgCore::OpenGLDrawMethod& method = MsgCore::VERTEX_ARRAYS, const bool& ignoreNormals=false );

				static Node*	readFile( const std::string& fileName, const MsgCore::OpenGLDrawMethod& method = MsgCore::VERTEX_ARRAYS, const bool& ignoreNormals=false );

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