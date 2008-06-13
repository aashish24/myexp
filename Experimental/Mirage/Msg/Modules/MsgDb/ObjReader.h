#ifndef __MSG_DB_OBJ_READER_H__
#define __MSG_DB_OBJ_READER_H__

#include <istream>

#include "MsgCore/Referenced.h"
#include "MsgCore/Array.h"

#include "Export.h"

using namespace Msg::MsgCore;

namespace Msg { namespace MsgCore { class Node; } }

namespace Msg
{
	namespace MsgDB
	{
    class MSG_EXPORT ObjReader : public MsgCore::Referenced
		{
			public:

        struct Model : public Referenced 
        {
          Model() : 
            Referenced      (),
            _vertices       ( new Vec3Array() ), 
            _normals        ( new Vec3Array() ), 
            _textureCoords      ( new Vec3Array() ), 
            _colors         ( new Vec4Array() ), 
            _vertexIndices  ( new Vec3iArray() ), 
            _normalIndices  ( new Vec3iArray() ), 
            _texCoordIndices( new Vec3iArray() ), 
            _colorIndices   ( new Vec3iArray() )
          {
          }

          SmartPtr< Vec3Array > _vertices;
          SmartPtr< Vec3Array > _normals;
          SmartPtr< Vec3Array > _textureCoords;          
          SmartPtr< Vec4Array > _colors;

          SmartPtr< Vec3iArray > _vertexIndices;
          SmartPtr< Vec3iArray > _normalIndices;
          SmartPtr< Vec3iArray > _texCoordIndices;
          SmartPtr< Vec3iArray > _colorIndices;          

          protected: 
          
            virtual ~Model()
            {
            }
        };


        ///////////////////////////////////////////////////////////////////////
        //
        // Data structure to hold data related with a vertex. 
        //
        ///////////////////////////////////////////////////////////////////////

        struct VertexData
        {
          VertexData() : 
            _vertexIndex( -1 ), 
            _colorIndex( -1 ), 
            _textureIndex( -1 ), 
            _normalIndex( -1 )
          {
          }

          long _vertexIndex;
          long _colorIndex;
          long _textureIndex;
          long _normalIndex;
        };


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


        ///////////////////////////////////////////////////////////////////////
        //
        // Parse obj file.
        //
        ///////////////////////////////////////////////////////////////////////

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

        
        ///////////////////////////////////////////////////////////////////////
        //
        // Convert data stored as Model into Node. 
        //
        ///////////////////////////////////////////////////////////////////////

        Node* convertDataIntoNode( Model* model ); 


      protected:

        std::vector< VertexData > _vertexData;
		};
	}
}

#endif // __MSG_DB_OBJ_READER_H__
