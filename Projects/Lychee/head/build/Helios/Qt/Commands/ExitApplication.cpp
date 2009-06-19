
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Perry L Miller IV
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Command to exit the application.
//
///////////////////////////////////////////////////////////////////////////////

#include "Helios/Qt/Commands/ExitApplication.h"

#include "Usul/Trace/Trace.h"

#include "QtGui/QApplication"

using namespace CadKit::Helios::Commands;

USUL_IMPLEMENT_COMMAND ( ExitApplication );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

ExitApplication::ExitApplication ( IUnknown *caller ) : BaseClass ( caller )
{
  USUL_TRACE_SCOPE;
  this->text ( "E&xit" );
  this->statusTip ( "Exit the application" );
  this->toolTip ( "Exit the application" );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

ExitApplication::~ExitApplication()
{
  USUL_TRACE_SCOPE;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Execute the command. This function is re-entrant.
//
///////////////////////////////////////////////////////////////////////////////

void ExitApplication::_execute()
{
  USUL_TRACE_SCOPE;
  // Do not lock the mutex. This function is re-entrant.

  // Closing all windows will exit the program.
  QApplication::closeAllWindows();
}
