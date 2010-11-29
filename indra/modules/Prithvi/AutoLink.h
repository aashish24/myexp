
#ifndef __PRITHVI_AUTOLINK_H__
#define __PRITHVI_AUTOLINK_H__

#if defined _MSC_VER && _DEBUG && !PRITHVI_BUILD
# pragma comment( lib, "Prithvid.lib" )
#elif defined _MSC_VER && !PRITHVI_BUILD
# pragma comment( lib, "Prithvi.lib" )
#endif // defined _MSC_VER && _DEBUG

#endif // __PRITHVI_AUTOLINK_H__
