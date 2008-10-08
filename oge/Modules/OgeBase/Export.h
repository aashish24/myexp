
#ifndef __OGE_BASE_EXPORT_H__
#define __OGE_BASE_EXPORT_H__

#if defined( _MSC_VER )  
  #pragma warning( disable : 4251 )
  #pragma warning( disable : 4273 )
#endif 

#if defined( _MSC_VER ) || defined( __CYGWIN__ ) || defined( __MINGW32__ )
  # if defined( OGE_BASE_BUILD_STATIC_LIBRARY )
  #  define OGE_BASE_EXPORT  
  # else
  #  ifdef OGE_BASE_BUILD_SHARED_LIBRARY
  #    define OGE_BASE_EXPORT __declspec(dllexport)
  #  else
  #    define OGE_BASE_EXPORT __declspec(dllimport)
  #  endif
  # endif
#else
  # define OGE_BASE_EXPORT
#endif 

#endif // __OGE_BASE_EXPORT_H__

