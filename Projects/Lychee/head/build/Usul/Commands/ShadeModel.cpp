
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author(s): Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Commands/ShadeModel.h"

using namespace Usul::Commands;

USUL_IMPLEMENT_COMMAND ( ShadeModel );

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

ShadeModel::ShadeModel ( const std::string& name, Mode mode, Usul::Interfaces::IUnknown *caller ) : 
BaseClass ( caller ),
_mode ( mode )
{
  this->text ( name );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

ShadeModel::~ShadeModel ()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Execute.
//
///////////////////////////////////////////////////////////////////////////////

void ShadeModel::_execute ()
{
  Usul::Interfaces::IShadeModel::QueryPtr sm ( this->caller().get() );

  if ( sm.valid () )
    sm->shadeModel ( _mode );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Update the check.
//
///////////////////////////////////////////////////////////////////////////////

bool ShadeModel::updateCheck() const
{
  Usul::Interfaces::IShadeModel::QueryPtr sm ( const_cast < Usul::Interfaces::IUnknown * > ( this->caller().get() ) );
  return sm.valid () ? _mode == sm->shadeModel () : false;
}
