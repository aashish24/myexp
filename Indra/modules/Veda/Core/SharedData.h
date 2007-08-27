
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// This class VEDA_EXPORT provides the functionality of sharing data from the master to the 
// the slaves nodes. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VEDA_CORE_SHAREDATA_H__
#define __VEDA_CORE_SHAREDATA_H__

#include "Veda/Core/Command.h"

#include "Veda/Export.h"
#include "Veda/VedaDefines.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT SharedData
    {          
      public:  
        
        static cluster::UserData< Command > mCommand;
        static bool                         mActive;

        static void init()
        {
	        std::cout << "Initializing shared data object: " << std::endl;
	        vpr::GUID newGuid( "24658da0-4c3d-48fc-b892-2e8538e24811" );
          SharedData::mCommand.init( newGuid );
          mActive = true;
        }

        static bool active()
        {
          return mActive;
        }
    };
  }
}

#endif // __VEDA_CORE_SHAREDATA_H__

