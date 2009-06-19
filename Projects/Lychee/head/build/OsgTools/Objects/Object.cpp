
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Perry L Miller IV
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for objects.
//
///////////////////////////////////////////////////////////////////////////////

#include "OsgTools/Objects/Object.h"

#include "Usul/Adaptors/MemberFunction.h"
#include "Usul/Bits/Bits.h"
#include "Usul/Functions/SafeCall.h"
#include "Usul/Trace/Trace.h"

using namespace OsgTools::Objects;

OSG_TOOLS_OBJECTS_IMPLEMENT_CLASS ( Object );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Object::Object() : BaseClass(),
  _parent ( 0x0 ),
  _dirty  ( Dirty::VERTICES | Dirty::NORMALS )
{
  USUL_TRACE_SCOPE;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy constructor.
//
///////////////////////////////////////////////////////////////////////////////

Object::Object ( const Object &copyMe ) : BaseClass ( copyMe ),
  _parent ( 0x0 ),
  _dirty  ( 0 )
{
  USUL_TRACE_SCOPE;
  Guard guard ( copyMe.mutex() );
  _parent = copyMe._parent;
  _dirty  = copyMe._dirty;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Object::~Object()
{
  USUL_TRACE_SCOPE;
  Usul::Functions::safeCall ( Usul::Adaptors::memberFunction ( this, &Object::_destroy ), "7938480890" );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy.
//
///////////////////////////////////////////////////////////////////////////////

void Object::_destroy()
{
  USUL_TRACE_SCOPE;
  _parent = 0x0;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the parent.
//
///////////////////////////////////////////////////////////////////////////////

void Object::parent ( Object::RefPtr p )
{
  USUL_TRACE_SCOPE;
  _parent = p;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the parent.
//
///////////////////////////////////////////////////////////////////////////////

Object::RefPtr Object::parent()
{
  USUL_TRACE_SCOPE;
  return _parent;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the parent.
//
///////////////////////////////////////////////////////////////////////////////

const Object::RefPtr Object::parent() const
{
  USUL_TRACE_SCOPE;
  return _parent;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the dirty flag.
//
///////////////////////////////////////////////////////////////////////////////

void Object::setDirty ( unsigned char bits, bool state )
{
  USUL_TRACE_SCOPE;

  // Set flags.
  _dirty = Usul::Bits::set ( _dirty, bits, state );

  // If setting dirty to true then set parent.
  if ( ( true == _parent.valid() ) && ( true == state ) )
  {
    _parent->setDirty ( bits, state );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the dirty flag.
//
///////////////////////////////////////////////////////////////////////////////

bool Object::isDirty() const
{
  USUL_TRACE_SCOPE;
  return ( 0 != _dirty );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the dirty flag.
//
///////////////////////////////////////////////////////////////////////////////

bool Object::isDirty ( unsigned char bits ) const
{
  USUL_TRACE_SCOPE;
  return Usul::Bits::has ( _dirty, bits );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Update the object.
//
///////////////////////////////////////////////////////////////////////////////

void Object::update ( Usul::Interfaces::IUnknown * )
{
  USUL_TRACE_SCOPE;
  this->setDirty ( Dirty::ALL, false );
}
