
#ifndef __MSG_CORE_OBJECT_H__
#define __MSG_CORE_OBJECT_H__

#include <string>

#include "Export.h"

#include "MsgCore/SmartPtr.h"
#include "MsgCore/Referenced.h"

namespace Msg
{
	namespace MsgCore
	{
    class MSG_EXPORT Object : public MsgCore::Referenced
		{
			public:

				///////////////////////////////////////////////////////////////
				//
				// Constructor. 
				//
				///////////////////////////////////////////////////////////////
				
        Object() :
					Referenced(),
					_name("")
				{
        }

  
        ///////////////////////////////////////////////////////////////
				//
				// Constructor. 
				//
				///////////////////////////////////////////////////////////////
				
        Object( const std::string name ) :
				  Referenced(),
					_name( name )
				{
        }


				///////////////////////////////////////////////////////////////
				//
				// Copy constructor. 
				//
				///////////////////////////////////////////////////////////////
				
        Object( const Object& obj ) :
					Referenced(), 
					_name( obj.getName() )
				{
        }


				///////////////////////////////////////////////////////////////
				//
				// Set name ( C++ style ).
				//
				////////////////////////////////////////////////////////////////
				
        void setName( const std::string& name )
				{
					_name = name;
				}


				///////////////////////////////////////////////////////////////
				//
				// Set name ( C style ).
				//
				///////////////////////////////////////////////////////////////
				
        void setName( const char* name )
				{
					_name = name;
				}

				///////////////////////////////////////////////////////////////
				//
				// Get name. 
				//
				///////////////////////////////////////////////////////////////
				
        const std::string getName() const
				{
					return _name;
				}

			
			protected:
				
        ///////////////////////////////////////////////////////////////
				//
				// Destructor. 
				//
				////////////////////////////////////////////////////////////////
				
        virtual ~Object()
				{
        }


			protected:

				std::string   _name;
		};
	}
}
		
#endif // __MSG_CORE_OBJECT_H__	
		