
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// This class VEDA_EXPORT defines the device interfaces. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_DEFS_H__
#define __CORE_DEFS_H__

#include <vector>
#include <string>
#include <iostream>

#include "Veda/Core/Types.h"

#include "OsgTools/Core/Export.h"

#include "Neiv/Pointer/Pointer.h"
#include "Neiv/Pointer/SmartPointer.h"
#include "Neiv/Base/Referenced.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT Defs : public Neiv::Base::Referenced
    {
      public:

        NEIV_DELCARE_SMART_PTR( Defs );

        static void init();

        // Wingman specific. 
        static const int mNumberOfAxes          = 6;
        static const int mNumberOfButtons       = 10;

        static std::vector< std::string >    mJoystickAnalogProxies;
        static std::vector< std::string >    mJoystickDigitalProxies;

        static ActionState                  mAxis0[ mNumberOfAxes ];
        static ActionState                  mAxis1[ mNumberOfAxes ];
        static ActionState                  mAxis2[ mNumberOfAxes ];
        static ActionState                  mAxis3[ mNumberOfAxes ];
        static ActionState                  mAxis4[ mNumberOfAxes ];
        static ActionState                  mAxis5[ mNumberOfAxes ];

        static ActionState                  mButton0  [ mNumberOfButtons ];
        static ActionState                  mButton1  [ mNumberOfButtons ];
        static ActionState                  mButton2  [ mNumberOfButtons ];
        static ActionState                  mButton3  [ mNumberOfButtons ];
        static ActionState                  mButton4  [ mNumberOfButtons ];
        static ActionState                  mButton5  [ mNumberOfButtons ];
        static ActionState                  mButton6  [ mNumberOfButtons ];
        static ActionState                  mButton7  [ mNumberOfButtons ];
        static ActionState                  mButton8  [ mNumberOfButtons ];
        static ActionState                  mButton9  [ mNumberOfButtons ];
        static ActionState                  mButtonSP0[ mNumberOfButtons ];
        static ActionState                  mButtonSP1[ mNumberOfButtons ];
        static ActionState                  mButtonSP2[ mNumberOfButtons ];
        static ActionState                  mButtonSP3[ mNumberOfButtons ];
        static ActionState                  mButtonSP4[ mNumberOfButtons ];
        static ActionState                  mButtonSP5[ mNumberOfButtons ];
        static ActionState                  mButtonSP6[ mNumberOfButtons ];
        static ActionState                  mButtonSP7[ mNumberOfButtons ];

        // Trackers specific. 
        static const int mNumberOfAxesTracker     = 2;
        static const int mNumberOfButtonsTracker  = 6;
        
        static std::vector< std::string >   mTrackerAnalogProxies;
        static std::vector< std::string >   mTrackerDigitalProxies;      

        static ActionState                  mAxisTr0[ mNumberOfAxesTracker ];
        static ActionState                  mAxisTr1[ mNumberOfAxesTracker ];
        
        static ActionState                  mButtonTr0[ mNumberOfButtonsTracker ];
        static ActionState                  mButtonTr1[ mNumberOfButtonsTracker ];
        static ActionState                  mButtonTr2[ mNumberOfButtonsTracker ];
        static ActionState                  mButtonTr3[ mNumberOfButtonsTracker ];
        static ActionState                  mButtonTr4[ mNumberOfButtonsTracker ];
        static ActionState                  mButtonTr5[ mNumberOfButtonsTracker ];
        static ActionState                  mButtonTr6[ mNumberOfButtonsTracker ];
    
      protected:
        
        Defs();

        ~Defs()
        {
        }

    };

    inline void Defs::init()
    {    
      mJoystickAnalogProxies.push_back( std::string( "VJAxis0" ) );
      mJoystickAnalogProxies.push_back( std::string( "VJAxis1" ) );
      mJoystickAnalogProxies.push_back( std::string( "VJAxis2" ) );
      mJoystickAnalogProxies.push_back( std::string( "VJAxis3" ) );    
      mJoystickAnalogProxies.push_back( std::string( "VJAxis4" ) );    
      mJoystickAnalogProxies.push_back( std::string( "VJAxis5" ) );   

      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS0" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS1" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS2" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS3" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS4" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS5" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS6" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS7" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS8" ) );
      mJoystickDigitalProxies.push_back( std::string( "VJButtonJS9" ) );
      
      mTrackerAnalogProxies.push_back( std::string( "VJTrackerAxis0" ) );
      mTrackerAnalogProxies.push_back( std::string( "VJTrackerAxis1" ) );
      
      mTrackerDigitalProxies.push_back( std::string( "VJTrackerButton0" ) );
      mTrackerDigitalProxies.push_back( std::string( "VJTrackerButton1" ) );
      mTrackerDigitalProxies.push_back( std::string( "VJTrackerButton2" ) );
      mTrackerDigitalProxies.push_back( std::string( "VJTrackerButton3" ) );
      mTrackerDigitalProxies.push_back( std::string( "VJTrackerButton4" ) );
      mTrackerDigitalProxies.push_back( std::string( "VJTrackerButton5" ) );
    }  
  }
}

#endif
