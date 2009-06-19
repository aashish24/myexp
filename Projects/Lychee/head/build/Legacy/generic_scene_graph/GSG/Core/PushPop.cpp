
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene graph nodes.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Core/Precompiled.h"
#include "GSG/Core/PushPop.h"
#include "GSG/Core/Visitor.h"

namespace GSG {
namespace Detail {


/////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
/////////////////////////////////////////////////////////////////////////////

GSG::Detail::PushPop::PushPop ( Visitor &v, Node *n ) : 
  _v ( v )
{
  v._pushNode ( n );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
/////////////////////////////////////////////////////////////////////////////

PushPop::~PushPop()
{
  _v._popNode();
}


}; // namespace Detail
}; // namespace GSG
