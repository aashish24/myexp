
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2005, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Various macros to support using different versions of Qt.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_HEADERS_QT_H_
#define _USUL_HEADERS_QT_H_


///////////////////////////////////////////////////////////////////////////////
//
//  QT_VERSION_CHECK is introduced with Qt version 4.3.0
//
///////////////////////////////////////////////////////////////////////////////

#ifndef QT_VERSION_CHECK
#define QT_VERSION_CHECK(major, minor, patch) ( ( major << 16 ) | ( minor << 8 ) | ( patch ) )
#endif


#endif /*_USUL_HEADERS_QT_H_*/
