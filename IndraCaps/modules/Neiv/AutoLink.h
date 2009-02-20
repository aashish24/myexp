
#ifndef __NEIV_AUTOLINK_H__
#define __NEIV_AUTOLINK_H__

#if defined _MSC_VER && _DEBUG && !NEIV_BUILD
# pragma comment( lib, "Neivd.lib" )
#elif defined _MSC_VER && !NEIV_BUILD
# pragma comment( lib, "Neiv.lib" )
#endif // defined _MSC_VER && _DEBUG

#endif // __NEIV_AUTOLINK_H__
