
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/Core/SharedData.h"

namespace Veda
{
  namespace Core
  {
    cluster::UserData< Command > SharedData::mCommand;
    bool                         SharedData::mActive = false;
  }
}