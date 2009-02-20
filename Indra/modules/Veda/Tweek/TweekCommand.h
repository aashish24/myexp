
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TWEEK_COMMAND_H__
#define __TWEEK_COMMAND_H__
     
// This should be the first include. 
#include "Veda/VedaConfig.h"

#include "Veda/Export.h"

namespace Veda
{
  namespace Tweek
  {
	  class VEDA_EXPORT TweekCommand
	  {
	    public:
		  TweekCommand()
		  {
      }

		  ~TweekCommand()
		  {
      }

		  std::string			mKey;
		  std::string			mValue;
	  };
  }
}

#endif //  __TWEEK_COMMAND_H__
