
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, John K. Grant.
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Visitor that sets the flags to all items.
//
///////////////////////////////////////////////////////////////////////////////

#include "MenuKit/FlagsVisitor.h"
#include "MenuKit/Menu.h"
#include "MenuKit/Button.h"

#include "Usul/Bits/Bits.h"

#include <stdexcept>

using namespace MenuKit;


///////////////////////////////////////////////////////////////////////////////
//
//  Default constructor.
//
///////////////////////////////////////////////////////////////////////////////

FlagsVisitor::FlagsVisitor ( Action action, unsigned  int flags ): BaseClass ( BaseClass::ALL ),
  _flags  ( flags ),
  _action ( action )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

FlagsVisitor::~FlagsVisitor()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Apply the visitor to the item.
//
///////////////////////////////////////////////////////////////////////////////

void FlagsVisitor::_apply ( Item &item )
{
  switch ( _action )
  {
  case ADD:
    item.flags ( Usul::Bits::add <unsigned int> ( item.flags(), _flags ) );
    break;
  case REMOVE:
    item.flags ( Usul::Bits::remove <unsigned int> ( item.flags(), _flags ) );
    break;
  case TOGGLE:
    item.flags ( Usul::Bits::toggle <unsigned int> ( item.flags(), _flags ) );
    break;
  default:
    throw std::runtime_error ( "Error 2410737922, invalid '_action' member." );
    break;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Apply the visitor to the menu.
//
///////////////////////////////////////////////////////////////////////////////

void FlagsVisitor::apply ( Menu &m )
{
  this->_apply ( m );
  this->traverse ( m );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Apply the visitor to the button.
//
///////////////////////////////////////////////////////////////////////////////

void FlagsVisitor::apply ( Button &b )
{
  this->_apply ( b );
}
