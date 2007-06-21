
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Core/SubjectImpl.h"

#include "vpr/Util/Debug.h"

using namespace Core;

namespace Veda 
{
  void SubjectImpl::setCommand( const char* key, const char* value )
  {    
    if( UserDataController::mUserData.isLocal() )
    {
      Tweek::TweekCommand* tweekCommand  = CommandFactory::create( CommandFactory::TWEEK_COMMAND );

      tweekCommand->mKey   = key;
      tweekCommand->mValue = value;

      UserDataController::addCommand( tweekCommand );
    }
    
    // Now notify all the obsevers / clients about server update. 
    tweek::SubjectImpl::notify();
  }
}
