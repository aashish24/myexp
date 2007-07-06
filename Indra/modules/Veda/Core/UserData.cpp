
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/Core/UserData.h"

namespace Veda
{
  namespace Core
  {
    cluster::UserData<UserData> UserDataController::mUserData;

    vpr::Mutex                  UserDataController::mCommandLock;
  }
}
