
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

#ifdef VRJUGGLER_MAJOR_VERSION >= 2 && VRJUGGLER_MINOR_VERSION > 0
          vpr::GUID newGuid( "291B6290-1BD9-4844-B757-73D5C4BB1690" );
#else
          vpr::GUID newGuid( "291B6290-1BD9-4844-B757-73D5C4BB1690", "ws6" );
#endif
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
