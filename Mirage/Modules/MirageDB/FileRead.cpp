
#include "MirageDB/FileRead.h"
#include "MirageDB/ObjReader.h"

#include "MirageCore/Node.h"
#include "MirageCore/Group.h"
#include "MirageCore/Image.h"

#include <fstream>

using namespace Mirage::MirageDB;

Node* FileRead::readFile( const std::string& fileName )
{
  std::ifstream fin( fileName.c_str(), std::ios::in );	


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

/*
	Image* FileRead::readImageFile( const char *fileName )
	{
		re
	}

	Image* FileRead::readImageFile( const std::string &fileName )
	{
	}
*/

