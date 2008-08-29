
#ifndef __MSG_EXPORT_H__
#define __MSG_EXPORT_H__

  #if defined( _MSC_VER )
	  // Not sure why I am getting this warning. 
	  #pragma warning( disable : 4251 )
  #endif

  #if defined( _MSC_VER ) 
    #if defined( MSG_BUILD_STATIC_LIBRARY )
      #define MSG_EXPORT
    #else
      #if  defined ( MSG_BUILD_SHARED_LIBRARY )
	      #define MSG_EXPORT __declspec(dllexport)
      #else
        #define MSG_EXPORT __declspec(dllimport)      
      #endif    
    #endif
#endif
#endif // __MSG_EXPORT_H__