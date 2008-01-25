
#ifndef __PRITHVI_AUTOLINK_H__
#define __PRITHVI_AUTOLINK_H__

#if defined _MSC_VER && _DEBUG && !PRITHVI_BUILD
# pragma comment( lib, "OgePrithvi_d.lib" )
#elif defined _MSC_VER && !PRITHVI_BUILD
# pragma comment( lib, "OgePrithvi.lib" )
#endif // defined _MSC_VER && _DEBUG

#endif // __PRITHVI_AUTOLINK_H__
