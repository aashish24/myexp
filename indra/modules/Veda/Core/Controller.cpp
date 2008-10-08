
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/Core/Controller.h"

namespace Veda
{
  namespace Core
  {
    /////////////////////////////////////////////////////////////////////////
    //
    // Get data from digital input device. 
    //
    /////////////////////////////////////////////////////////////////////////

    DeviceData Controller::getDeviceInputData( Button btn )
    {
      Buttons btns;
      
      btns.insert( btns.begin(), &btn );

      ActionState btn0[]  = { ON };  
      
      return getDeviceInputData( btns, std::vector< ActionState >( btn0, btn0 + 1 ) );
    }


    /////////////////////////////////////////////////////////////////////////
    //
    // Get data from combination of digital input devices.
    //
    /////////////////////////////////////////////////////////////////////////

    DeviceData Controller::getDeviceInputData( Buttons btns, ActionStates states )
    {
      Core::DeviceData data( POSITIVE );  
      
      for( unsigned int i = 0; i < states.size(); i++ )
      {
        if( states[ i ] == ON )
        {
          if( !( *btns[ i ] )->getData() )
          {  
            data = ZERO; 
          }
        }
        else if( states[ i ] == OFF )
        {
          if( ( *btns[ i ] )->getData() )
          { 
            data = ZERO; 
          }          
        }
        else if( states[ i ] == TOGGLE_ON )
        {
          if( !( ( ( *btns[ i ] )->getData()) == gadget::Digital::TOGGLE_ON ) ) 
          {         
            data = ZERO; 
          }          
        }
        else if( states[ i ] == TOGGLE_OFF )
        {
          if(( *btns[ i ] )->getData() != 3 )
          { 
            data = ZERO; 
          }          
        }
      }

      return data;
    }


    /////////////////////////////////////////////////////////////////////////
    //
    // Get data from combination of analog input devices.
    //
    /////////////////////////////////////////////////////////////////////////

    //Core::DeviceData Controller::getDeviceInputData( Analogs analogs, ActionStates states )
    //{
    //  Core::DeviceData data( ZERO );
    //  
    //  for ( unsigned int i = 0; i < states.size(); i++ )
    //  {
    //    if( states[i] == ON )
    //    {
    //      float value = ( *analogs[ i ] )->getData();
    //
    //      if( value > mMaxValue )
    //      {
    //        data = POSITIVE;
    //      }
    //      else if ( value < mMinValue )
    //      {
    //        data = NEGATIVE;
    //      }
    //      else 
    //      {  
    //        data = CENTER;
    //      }
    //    }
    //  }
    //
    //  return data;
    //}

    /////////////////////////////////////////////////////////////////////////
    //
    // Get data from combination of analog input devices.
    //
    /////////////////////////////////////////////////////////////////////////

    double Controller::getDeviceInputData( Analogs analogs, ActionStates states )
    {
      double data = 0.0;
      
      for ( unsigned int i = 0; i < states.size(); i++ )
      {
        if( states[ i ] == ON )
        {

          double value = ( *analogs[ i ] )->getData();
          
          if( value > mMaxValue )
          {
            data = 2 * ( value - 0.5 );
          }
          else if ( value < mMinValue )
          {
            data = 2 * ( value - 0.5 );
          }
          else 
          {  
            data = 0.0;
          }
        }
      }  

      return data;
    }
  }
}
