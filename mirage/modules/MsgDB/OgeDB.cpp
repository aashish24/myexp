#include <oge/db/OgeDB.h>
#include <oge/db/ObjReader.h>

#include <oge/core/Node.h>
#include <oge/core/Group.h>
#include <oge/core/Image.h>

#include <fstream>

using namespace oge::db;

Node* OgeDB::readFile( const char* fileName, const bool& ignoreNormals )
{
	std::ifstream fin( fileName, std::ios::in );	


	if( !fin.good() )
	{
		return 0x00;
	}

	std::string file( fileName );

	int comp = file.compare( ( file.size() - 4 ), 4, ".obj" );
	if( comp == 0 )
	{
		SmartPtr< ObjReader > objReader = new ObjReader();
		return objReader->readFile( fin, file ); 
	}
	else
	{
		std::cerr <<"[OgeDB::readFile] File extension not handled for file: " << file << std::endl;
		return NULL;
	}
}

Node* OgeDB::readFile( const std::string &fileName, const bool& ignoreNormals )
{
	return readFile( fileName.c_str() );
}

/*
	Image* OgeDB::readImageFile( const char *fileName )
	{
		re
	}

	Image* OgeDB::readImageFile( const std::string &fileName )
	{
	}
*/

