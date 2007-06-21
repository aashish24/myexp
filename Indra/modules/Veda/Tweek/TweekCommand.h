
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TWEEK_COMMAND_H__
#define __TWEEK_COMMAND_H__
     
#include "Export.h"

namespace Tweek
{
	class VEDA_EXPORT TweekCommand
	{
	  public:
		TweekCommand()
		{}

		~TweekCommand()
		{}

		std::string			mIdentifier;
		std::string			mEntity;
		std::string			mStateAttribute;
		std::string			mModifierString;
		bool						mModifierBoolean;
		long						mModifierLong;
	};
}

#endif //  __TWEEK_COMMAND_H__
