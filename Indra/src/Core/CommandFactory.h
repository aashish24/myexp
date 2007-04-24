
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
// Factory class CORE_EXPORT to create command objects. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_COMMANDFACTORY_H__
#define __CORE_COMMANDFACTORY_H__

#include "Core/TweekCommand.h"

namespace Core
{
  class CORE_EXPORT CommandFactory
  {

    public: 

      
      /////////////////////////////////////////////////////////////////////////
      //
      // Command type. 
      //
      /////////////////////////////////////////////////////////////////////////

      enum CommandType 
      {
        TWEEK_COMMAND = 0
      };

      /////////////////////////////////////////////////////////////////////////
      //
      // Constructor.
      //
      /////////////////////////////////////////////////////////////////////////

      CommandFactory()
      {
      }

      /////////////////////////////////////////////////////////////////////////
      //
      // Destructor.
      //
      /////////////////////////////////////////////////////////////////////////

      ~CommandFactory()
      {
      }

      /////////////////////////////////////////////////////////////////////////
      //
      // Create a new command. 
      //
      /////////////////////////////////////////////////////////////////////////

      static TweekCommand* create( CommandType type )
      {
        switch( type )
        {
          case TWEEK_COMMAND:
          {
            return new TweekCommand();            
          }
          default:
          {
            return 0x00;
          }
        }
        return 0;
      }
  };
}

#endif // __CORE_COMMANDFACTORY_H__
