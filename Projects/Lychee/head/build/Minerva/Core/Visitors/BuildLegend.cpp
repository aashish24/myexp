
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Visitors/BuildLegend.h"
#include "Minerva/Core/Data/Container.h"

#include "Usul/Interfaces/IAddRowLegend.h"

using namespace Minerva::Core::Visitors;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

BuildLegend::BuildLegend ( OsgTools::Widgets::Legend *legend ) :
  BaseClass (),
  _legend ( legend )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

BuildLegend::~BuildLegend()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit a layer.
//
///////////////////////////////////////////////////////////////////////////////

void BuildLegend::visit ( Minerva::Core::Data::Container &layer )
{
  Usul::Interfaces::IAddRowLegend::QueryPtr addRow ( &layer );
  if( layer.showLayer() && addRow.valid() && addRow->showInLegend() )
  {
    OsgTools::Widgets::LegendObject::RefPtr row ( new OsgTools::Widgets::LegendObject );
    addRow->addLegendRow( row.get() );
    
    if ( _legend.valid() )
      _legend->addRow ( row.get() );
  }

}
