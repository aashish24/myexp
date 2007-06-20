
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

namespace dt 
{
  void SubjectImpl::setCommand( const char* identifier, 
                                  const char* entity, 
                                  const char* state_attribute,
                                  const char* modifier_string,
                                  CORBA::Boolean modifier_boolean, 
                                  CORBA::Long modifier_long )
  {    
    if( UserDataController::mUserData.isLocal() )
    {
      TweekCommand* tweekCommand      = CommandFactory::create( CommandFactory::TWEEK_COMMAND );
      tweekCommand->mIdentifier       = identifier;
      tweekCommand->mEntity           = entity;
      tweekCommand->mStateAttribute   = state_attribute;
      tweekCommand->mModifierString   = modifier_string;
      tweekCommand->mModifierBoolean  = modifier_boolean;
      tweekCommand->mModifierLong     = modifier_long;
      UserDataController::addCommand( tweekCommand );
    }
    
    // Now notify all the obsevers / clients about server update. 
    tweek::SubjectImpl::notify();
  }
}
