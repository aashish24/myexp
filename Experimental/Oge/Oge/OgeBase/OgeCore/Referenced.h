
#ifndef __OGE_CORE_REFERENCED_H__
#define __OGE_CORE_REFERENCED_H__

#include "Oge/Export.h"

namespace Oge
{
	namespace OgeBase
	{
    namespace OgeCore
    {
		  class OGE_EXPORT Referenced
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
}

#endif // __OGE_CORE_REFERENCED_H__
