#ifndef __OGE_DB_H__
#define __OGE_DB_H__

#include <oge/Export.h>
#include <oge/core/Referenced.h>

#include <string>

using namespace oge::core;

namespace oge { namespace core { class Node; class Image; } }

namespace oge
{
	namespace db
	{
		class OGE_EXPORT OgeDB : public Referenced
		{
			public:
				OgeDB()
				{
				}

				OgeDB( const OgeDB& ogeDB )
				{
				}

				static Node*	readFile( const char* fileName, const bool& ignoreNormals=false );

				static Node*	readFile( const std::string& fileName, const bool& ignoreNormals=false );

				/*
					static Image*	readImageFile( const char* fileName );

					static Image*	readImageFile( const std::string& fileName );
				*/

			protected:
				virtual ~OgeDB()
				{
				}

			protected:	
		};
	}
}

#endif // __OGE_DB_H__