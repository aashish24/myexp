
#ifndef __OGE_EXPORT_H__
#define __OGE_EXPORT_H__

#if defined( _MSC_VER )  
  #pragma warning( disable : 4251 )
  #pragma warning( disable : 4273 )
#endif 

#if defined( _MSC_VER ) || defined( __CYGWIN__ ) || defined( __MINGW32__ )
  # if defined( OGE_BUILD_STATIC_LIBRARY )
  #  define OGE_EXPORT  
  # else
  #  ifdef OGE_BUILD_SHARED_LIBRARY
  #    define OGE_EXPORT __declspec(dllexport)
  #  else
  #    define OGE_EXPORT __declspec(dllimport)
  #  endif
  # endif
#else
  # define OGE_EXPORT
#endif 

#endif // __OGE_EXPORT_H__

