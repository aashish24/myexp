#ifndef __OBJ_READER_H__
#define __OBJ_READER_H__

#include <istream>

#include <oge/core/Referenced.h>
#include <oge/Export.h>

using namespace oge::core;

namespace oge { namespace core { class Node; } }

namespace oge
{
	namespace db
	{
		class OGE_EXPORT ObjReader : public Referenced
		{
			public:
				ObjReader()
				{
				}

				ObjReader( const ObjReader& obj )
				{

				}
			
				Node*	readFile( std::istream& fin, const char* fileName, const bool& ignoreNormals=false );

				Node*	readFile( std::istream& fin, const std::string& fileName, const bool& ignoreNormals=false );

			protected:
				virtual ~ObjReader()
				{
				}
		};
	}
}

#endif // __OBJ_READER_H__