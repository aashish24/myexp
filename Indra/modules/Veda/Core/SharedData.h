
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
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

#ifndef __CORE_SHAREDDATA_H__
#define __CORE_SHAREDDATA_H__

#include "Veda/Core/Command.h"

#include "Veda/Export.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT SharedData
    {          
      public:  
        static cluster::UserData< Command > mCommand;
        static bool                          mActive;

        static void init()
        {
          vpr::GUID newGuid( "291B6290-1BD9-4844-B757-73D5C4BB1690" );
          SharedData::mCommand.init( newGuid);
          mActive = true;
        }

        static bool active()
        {
          return mActive;
        }
    };
  }
}

#endif // __CORE_SHAREDDATA_H__
