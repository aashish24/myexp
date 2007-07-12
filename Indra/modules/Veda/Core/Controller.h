
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class provides the functionality to acquire the device data. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_CONTROLLER_H__
#define __CORE_CONTROLLER_H__

#include <vector>

#include "gmtl/Matrix.h"
#include "gmtl/Vec.h"
#include "gmtl/MatrixOps.h"

#include "gadget/Type/DeviceInterface.h"
#include "gadget/Type/DigitalInterface.h"
#include "gadget/Type/AnalogInterface.h"

#include "Veda/Core/Types.h"

#include "Veda/Export.h"

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT Controller 
    {
      public:          
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Typedefs.
        //
        /////////////////////////////////////////////////////////////////////////

        typedef gadget::DigitalInterface                    Button;
        typedef std::vector< Button* >                      Buttons;  

        typedef gadget::AnalogInterface*                    Analog;
        typedef std::vector< Analog >                       Analogs;        

        typedef std::vector< ActionState >                  ActionStates;

        /////////////////////////////////////////////////////////////////////////
        //
        // Construcor. 
        //
        /////////////////////////////////////////////////////////////////////////

        Controller() : 
          mIsActive( true ),
          mMinValue( 0.45 ), 
          mMaxValue( 0.55 )              
        {
        }
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor.
        //
        /////////////////////////////////////////////////////////////////////////

        virtual ~Controller()
        {
        }
        
        virtual  Core::DeviceData    getDeviceInputData( Button btn );

        virtual Core::DeviceData    getDeviceInputData( std::vector< gadget::DigitalInterface* > btns, std::vector< ActionState > state );

        //virtual Core::DeviceData  getDeviceInputData( std::vector< gadget::AnalogInterface* > inputs, std::vector< ActionState > state );          
        
        virtual double        getDeviceInputData( std::vector< gadget::AnalogInterface* > inputs, std::vector< ActionState > state );      

      protected:    

        bool                  mIsActive;  

        double                mMinValue;
        double                mMaxValue;
    };
  }
}

#endif // __CORE_CONTROLLER_H__

