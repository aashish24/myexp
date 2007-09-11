
#ifndef __VEDA_AUTOLINK_H__
#define __VEDA_AUTOLINK_H__

#if defined _MSC_VER && _DEBUG && !VEDA_BUILD
# pragma comment( lib, "Vedad.lib" )
#elif defined _MSC_VER && !VEDA_BUILD
# pragma comment( lib, "Veda.lib" )
#endif // defined _MSC_VER && _DEBUG

#endif // __VEDA_AUTOLINK_H__
