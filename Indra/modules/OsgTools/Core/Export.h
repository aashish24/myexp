
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _OSGTOOLS_CORE_EXPORT_H__
#define _OSGTOOLS_CORE_EXPORT_H__

#if defined( _MSC_VER )  
  #pragma warning( disable : 4251 )
  #pragma warning( disable : 4273 )
#endif 

#if defined( _MSC_VER ) || defined( __CYGWIN__ ) || defined( __MINGW32__ )
  # if defined( OSGTOOLS_STATIC )
  #  define OSGTOOLS_EXPORT  
  # else
  #  ifdef OSGTOOLS_SHARED
  #    define OSGTOOLS_EXPORT __declspec(dllexport)
  #  else
  #    define OSGTOOLS_EXPORT __declspec(dllimport)
  #  endif
  # endif
#else
  # define OSGTOOLS_EXPORT
#endif 

#endif // _OSGTOOLS_CORE_EXPORT_H__








