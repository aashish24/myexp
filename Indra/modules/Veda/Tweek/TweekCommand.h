
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
     
#include "Veda/Export.h"

namespace Veda
{
  namespace Tweek
  {
	  class VEDA_EXPORT TweekCommand
	  {
	    public:
		  TweekCommand()
		  {}

		  ~TweekCommand()
		  {}

		  std::string			mKey;
		  std::string			mValue;
	  };
  }
}

#endif //  __TWEEK_COMMAND_H__
