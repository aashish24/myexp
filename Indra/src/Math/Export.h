
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_EXPORT_H__
#define __MATH_EXPORT_H__

#if defined( _MSC_VER )	
	#pragma warning( disable : 4251 )
	#pragma warning( disable : 4273 )
#endif 

#if defined( _MSC_VER ) || defined( __CYGWIN__ ) || defined( __MINGW32__ )
	# if defined( INDRA_STATIC_LIBRARY )
	#	define MATH_EXPORT	
	# else
	#	ifdef INDRA_SHARED_LIBRARY
	#		define MATH_EXPORT __declspec(dllexport)
	#	else
	#		define MATH_EXPORT __declspec(dllimport)
	#	endif
	# endif
#else
	# define MATH_EXPORT
#endif 

#endif // __MATH_EXPORT_H__








