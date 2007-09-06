
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Aashish Chaudhary
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PRITHVI_EXPORT_H__
#define __PRITHVI_EXPORT_H__

#if defined( _MSC_VER )  
  #pragma warning( disable : 4251 )
  #pragma warning( disable : 4273 )
#endif 

#if defined( _MSC_VER ) || defined( __CYGWIN__ ) || defined( __MINGW32__ )
  # if defined( PRITHVI_STATIC )
  #  define PRITHVI_EXPORT  
  # else
  #  if defined PRITHVI_SHARED
  #    define PRITHVI_EXPORT __declspec(dllexport)
  #  else
  #    define PRITHVI_EXPORT __declspec(dllimport)
  #  endif
  # endif
#else
  # define PRITHVI_EXPORT
#endif 

#endif // __PRITHVI_EXPORT_H__








