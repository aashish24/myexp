#ifndef __OBJ_READER_H__
#define __OBJ_READER_H__

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
		class MSG_EXPORT ObjReader : public Referenced
		{
			public:

        struct Model : public Referenced 
        {
          Model() : 
            Referenced      (),
            mVertices       ( new Vec3Array() ), 
            mNormals        ( new Vec3Array() ), 
            mTexCoords      ( new Vec3Array() ), 
            mColors         ( new Vec4Array() ), 
            mVertexIndices  ( new Vec3iArray() ), 
            mNormalIndices  ( new Vec3iArray() ), 
            mTexCoordIndices( new Vec3iArray() ), 
            mColorIndices   ( new Vec3iArray() )
          {
          }

          SmartPtr< Vec3Array > mVertices;
          SmartPtr< Vec3Array > mNormals;
          SmartPtr< Vec3Array > mTexCoords;          
          SmartPtr< Vec4Array > mColors;

          SmartPtr< Vec3iArray > mVertexIndices;
          SmartPtr< Vec3iArray > mNormalIndices;
          SmartPtr< Vec3iArray > mTexCoordIndices;
          SmartPtr< Vec3iArray > mColorIndices;          

          protected: 
          
            virtual ~Model()
            {
            }
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

				Node*	readFile( std::istream& fin, const std::string& fileName, const bool& ignoreNormals=false );

        Node* convertDataIntoNode( Model* model ); 

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