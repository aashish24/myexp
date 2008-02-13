#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

#include "oge/Export.h"

#include "oge/core/SmartPtr.h"
#include "oge/core/Referenced.h"

namespace oge
{
	namespace core
	{
		class OGE_EXPORT Object : public Referenced
		{
			public:
				///////////////////////////////////////////////////////////////
				//
				// Constructor. 
				//
				///////////////////////////////////////////////////////////////
				Object() :
					Referenced(),
					mName("")
				{}

				///////////////////////////////////////////////////////////////
				//
				// Copy constructor. 
				//
				///////////////////////////////////////////////////////////////
				Object( const Object& obj ) :
					Referenced(), 
					mName( obj.getName() )
				{}

				///////////////////////////////////////////////////////////////
				//
				// Set name ( C++ style ).
				//
				////////////////////////////////////////////////////////////////
				void setName( const std::string& name )
				{
					mName = name;
				}

				///////////////////////////////////////////////////////////////
				//
				// Set name ( C style ).
				//
				///////////////////////////////////////////////////////////////
				void setName( const char* name )
				{
					mName = name;
				}

				///////////////////////////////////////////////////////////////
				//
				// Get name. 
				//
				///////////////////////////////////////////////////////////////
				const std::string getName() const
				{
					return mName;
				}
			
			protected:
				///////////////////////////////////////////////////////////////
				//
				// Destructor. 
				//
				////////////////////////////////////////////////////////////////
				virtual ~Object()
				{}

			private:
				std::string mName;
		};
	}
}
		
#endif // __OBJECT_H__
	
		