
#ifndef __NEIV_BASE_REFERENCED_H__
#define __NEIV_BASE_REFERENCED_H__

// This should be the first include. 
#include "Neiv/NeivConfig.h"

#include "Neiv/Export.h"

namespace Neiv
{
	namespace Base
	{
		class NEIV_EXPORT Referenced
		{
			public:

				Referenced();

				Referenced( const Referenced& ref );

				Referenced& operator = ( const Referenced& ref ) 
				{ 
					return *this; 
				}

				void ref();

				void unref();

				void unrefDoNotDelete();

			protected:

        virtual ~Referenced();

			private:

        ///////////////////////////////////////////////////////////////
				//
				// This can be changed even thouth the instance defined  
				// /c const.
				//
				///////////////////////////////////////////////////////////////

				mutable int mRefCount;
		};
	}
}

#endif // __NEIV_BASE_REFERENCED_H__
