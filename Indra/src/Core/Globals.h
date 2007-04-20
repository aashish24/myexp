
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// This class CORE_EXPORT defines the globals used. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Export.h"

namespace Core
{
	class CORE_EXPORT Display
	{
		public:
			void			        setDisplay( int originx, int originy, int width, int height );

      const int&        width() const;
			const int&			  height() const;

			const int&        originX()const; 
			const int&			  originY() const;

		public:
			
      int		            mOriginX;
      int               mOriginY;
			int		            mWidth;
      int               mHeight;
	};

	class CORE_EXPORT RenderGlobals
	{
		public:

			void static		    setDisplay( int originx, int originy, int width, int height );
		
		public:

			static Display	  mDisplay;
	};
}

#endif // __GLOBALS_H__

