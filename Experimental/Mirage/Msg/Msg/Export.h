
#ifndef __OGE_EXPORT_H__
#define __OGE_EXPORT_H__

#if defined( _MSC_VER )
	// Not sure why I am getting this warning. 
	#pragma warning( disable : 4251 )
#endif

#if defined( _MSC_VER )
	#define OGE_EXPORT __declspec(dllexport)
#else
	#define	OGE_EXPORT
#endif

#endif // __OGE_EXPORT_H__