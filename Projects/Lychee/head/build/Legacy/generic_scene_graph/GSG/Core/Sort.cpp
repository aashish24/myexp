
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  The base culling class.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Core/Precompiled.h"
#include "GSG/Core/Sort.h"
#include "GSG/Core/Transform.h"
#include "GSG/Core/Lod.h"
#include "GSG/Core/Camera.h"
#include "GSG/Core/Shape.h"

using namespace GSG;

GSG_IMPLEMENT_REFERENCED ( Sort );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Sort::Sort ( RenderBin *bin ) : BinBuilder ( bin )
{
  // Empty.
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy constructor.
//
///////////////////////////////////////////////////////////////////////////////

Sort::Sort ( const Sort &s ) : BinBuilder ( s )
{
  // Empty.
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Sort::~Sort()
{
  // Empty.
}


/////////////////////////////////////////////////////////////////////////////
//
//  Set from the given object.
//
/////////////////////////////////////////////////////////////////////////////

void Sort::setFrom ( const Sort &s )
{
  // Call the base class's function.
  BaseClass::setFrom ( s );
}
