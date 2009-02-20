
#ifndef __OSGTOOLS_AUTOLINK_H__
#define __OSGTOOLS_AUTOLINK_H__

#if defined _MSC_VER && _DEBUG && !OSGTOOLS_BUILD 
# pragma comment( lib, "OsgToolsd.lib" )
#elif defined _MSC_VER && !OSGTOOLS_BUILD
# pragma comment( lib, "OsgTools.lib" )
#endif // defined _MSC_VER && _DEBUG

#endif // __OSGTOOLS_AUTOLINK_H__
