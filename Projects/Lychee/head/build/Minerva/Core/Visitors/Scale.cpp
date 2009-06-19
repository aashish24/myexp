
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Perry L Miller IV
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Visitor class for scaling the scene.
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Visitors/Scale.h"
#include "Minerva/Core/TileEngine/Body.h"

#include "Usul/Trace/Trace.h"

using namespace Minerva::Core::Visitors;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor
//
///////////////////////////////////////////////////////////////////////////////

Scale::Scale ( double scale ) : BaseClass(),
  _scale ( scale )
{
  USUL_TRACE_SCOPE;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
///////////////////////////////////////////////////////////////////////////////

Scale::~Scale()
{
  USUL_TRACE_SCOPE;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit the node.
//
///////////////////////////////////////////////////////////////////////////////

void Scale::visit ( Minerva::Core::TileEngine::Body &body )
{
  USUL_TRACE_SCOPE;
  Guard guard ( this->mutex() );

  // Get the current scale amount.
  const double old ( body.scale() );

  // Set the scale.
  body.scale ( _scale );

  // Split distance multiplier.
  const double mutliplier ( old > _scale ? _scale : 1.0 / old );
  
  // Set the new split distance.
  body.splitDistance ( body.splitDistance() * mutliplier, false );

  // Call the base class's function.
  BaseClass::visit ( body );
}
