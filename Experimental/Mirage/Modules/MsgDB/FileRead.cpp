
#include "MsgDB/FileRead.h"
#include "MsgDB/ObjReader.h"

#include "MsgCore/Node.h"
#include "MsgCore/Group.h"
#include "MsgCore/Image.h"

#include <fstream>

using namespace Msg::MsgDB;

Node* FileRead::readFile( const char* fileName, const bool& ignoreNormals )
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
    std::cerr <<"ERROR 1559475712: File extension not handled for file. " << file << std::endl;
		return 0x00;
	}
}

Node* FileRead::readFile( const std::string &fileName, const bool& ignoreNormals )
{
	return readFile( fileName.c_str(), ignoreNormals );
}

/*
	Image* FileRead::readImageFile( const char *fileName )
	{
		re
	}

	Image* FileRead::readImageFile( const std::string &fileName )
	{
	}
*/

