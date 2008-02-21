#ifndef __REFERENCED_H__
#define __REFERENCED_H__

#include "Export.h"

namespace Msg
{
	namespace MsgCore
	{
		class MSG_EXPORT Referenced
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

#endif // __REFERENCED_H__