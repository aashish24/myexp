#ifndef __OBJ_READER_H__
#define __OBJ_READER_H__

#include <istream>

#include "MsgCore/Referenced.h"
#include "Export.h"

using namespace Msg::MsgCore;

namespace Msg { namespace MsgCore { class Node; } }

namespace Msg
{
	namespace MsgDB
	{
		class MSG_EXPORT ObjReader : public Referenced
		{
			public:

        ///////////////////////////////////////////////////////////////////////
        //
        // Constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				ObjReader()
				{
				}


        ///////////////////////////////////////////////////////////////////////
        //
        // Copy constructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				ObjReader( const ObjReader& obj )
				{

				}

        ///////////////////////////////////////////////////////////////////////
        //
        // Parse obj file.
        //
        ///////////////////////////////////////////////////////////////////////
			
				Node*	readFile( std::istream& fin, const char* fileName, const bool& ignoreNormals=false );

				Node*	readFile( std::istream& fin, const std::string& fileName, const bool& ignoreNormals=false );


			protected:

        ///////////////////////////////////////////////////////////////////////
        //
        // Destructor. 
        //
        ///////////////////////////////////////////////////////////////////////

				virtual ~ObjReader()
				{
				}
		};
	}
}

#endif // __OBJ_READER_H__