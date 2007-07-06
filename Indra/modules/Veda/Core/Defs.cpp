
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/Core/Defs.h"

namespace Veda
{
  namespace Core
  {
    std::vector< std::string > Defs::mJoystickAnalogProxies;
    std::vector< std::string > Defs::mJoystickDigitalProxies;

    ActionState Defs::mAxis0[]  = { ON, OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mAxis1[]  = {OFF,  ON, OFF, OFF, OFF, OFF};
    ActionState Defs::mAxis2[]  = {OFF, OFF, OFF,  ON, OFF, OFF};
    ActionState Defs::mAxis3[]  = {OFF, OFF,  ON, OFF, OFF, OFF};
    ActionState Defs::mAxis4[]  = {OFF, OFF, OFF, OFF,  ON, OFF};
    ActionState Defs::mAxis5[]  = {OFF, OFF, OFF, OFF, OFF,  ON};

    // Regular digital mButtons. 
    ActionState Defs::mButton0[]  = {TOGGLE_ON, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mButton1[]  = {OFF, ON, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mButton2[]  = {OFF, OFF, TOGGLE_ON, OFF, OFF, OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mButton3[]  = {OFF, OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mButton4[]  = {OFF, OFF, OFF, OFF,  TOGGLE_ON,  OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mButton5[]  = {OFF, OFF, OFF, OFF,  OFF, TOGGLE_ON, OFF, OFF, OFF, OFF};
    ActionState Defs::mButton6[]  = {OFF, OFF, OFF, OFF,  OFF, OFF, TOGGLE_ON, OFF, OFF, OFF};
    ActionState Defs::mButton7[]  = {OFF, OFF, OFF, OFF,  OFF, OFF, OFF, TOGGLE_ON, OFF, OFF};  
    ActionState Defs::mButton8[]  = {OFF, OFF, OFF, OFF,  OFF, OFF, OFF, OFF, TOGGLE_ON, OFF};
    ActionState Defs::mButton9[]  = {OFF, OFF, OFF, OFF,  OFF, OFF, OFF, OFF, OFF,  TOGGLE_ON};

    // Shift( mButton9 + this ) mode. 
    ActionState Defs::mButtonSP0[]  = {TOGGLE_ON,  OFF,  OFF, OFF,  OFF, OFF, OFF, OFF, ON, OFF};  
    ActionState Defs::mButtonSP1[]  = {OFF,  TOGGLE_ON,  OFF, OFF,  OFF, OFF, OFF, OFF, ON, OFF};  
    ActionState Defs::mButtonSP2[]  = {OFF, OFF,  TOGGLE_ON, OFF, OFF, OFF, OFF, OFF,  ON, OFF};
    ActionState Defs::mButtonSP3[]  = {OFF, OFF,  OFF, TOGGLE_ON, OFF, OFF, OFF, OFF,  ON, OFF};  
    ActionState Defs::mButtonSP4[]  = {OFF, OFF,  OFF, OFF,  TOGGLE_ON, OFF, OFF, OFF, ON, OFF};
    ActionState Defs::mButtonSP5[]  = {OFF, OFF,  OFF, OFF, OFF,  TOGGLE_ON, OFF, OFF, ON, OFF};
    ActionState Defs::mButtonSP6[]  = {OFF, OFF,  OFF, OFF, OFF, OFF,  TOGGLE_ON, OFF, ON, OFF};  
    ActionState Defs::mButtonSP7[]  = {OFF, OFF,  OFF, OFF, OFF, OFF, OFF,  TOGGLE_ON, ON, OFF};

    std::vector< std::string > Defs::mTrackerAnalogProxies;
    std::vector< std::string > Defs::mTrackerDigitalProxies;

    ActionState Defs::mAxisTr0[]  = {ON,  OFF};
    ActionState Defs::mAxisTr1[]  = {OFF, ON};

    ActionState Defs::mButtonTr0[]  = { TOGGLE_ON, OFF, OFF, OFF, OFF, OFF};
    ActionState Defs::mButtonTr1[]  = { OFF, TOGGLE_ON, OFF, OFF, OFF, OFF};
    ActionState Defs::mButtonTr2[]  = { OFF, OFF, TOGGLE_ON, OFF, OFF, OFF};
    ActionState Defs::mButtonTr3[]  = { OFF, OFF, OFF, TOGGLE_ON, OFF, OFF};
    ActionState Defs::mButtonTr4[]  = { OFF, OFF, OFF, OFF, ON, OFF}; 
    ActionState Defs::mButtonTr5[]  = { OFF, OFF, OFF, OFF, OFF, ON};
  }
}