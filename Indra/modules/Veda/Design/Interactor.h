
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Interface defined for an getInteractor system. 
// Todo:
// Separate the controller from the the logic. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VEDA_DESIGN_INTERACTION_H__
#define __VEDA_DESIGN_INTERACTION_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "gadget/Type/DigitalInterface.h"
#include "gadget/Type/AnalogInterface.h"
#include "gadget/Type/DeviceInterface.h"
#include "gadget/Type/PositionInterface.h"

#include "gmtl/Matrix.h"

#include "Veda/Core/Defs.h"
#include "Veda/Core/Types.h"
#include "Veda/Core/Controller.h"
#include "Veda/Core/SharedData.h"

#include "Veda/Design/Navigation.h"

#if HAVE_KEYBOARDMOUSE
  #include "Dev/VJKeyboardMouseCallback.h"
#endif

#include "Veda/Export.h"

namespace Core = Veda::Core;

namespace Veda
{
  namespace Design
  {
    const int JOYSTICK_ANALOG_INPUTS_COUNT  = 06 ;
    const int JOYSTICK_DIGITAL_INPUTS_COUNT = 18 ;

    class VEDA_EXPORT Interactor
    {
      public:
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Easy to remember names. 
        // 
        /////////////////////////////////////////////////////////////////////////

        typedef std::vector< gadget::DigitalInterface* >  DigitalInterfaces;
        typedef std::vector< gadget::AnalogInterface* >   AnalogInterfaces;
	      typedef std::vector< Core::ActionState >          ActionStates;

        /////////////////////////////////////////////////////////////////////////
        //
        // Constructor.
        // 
        /////////////////////////////////////////////////////////////////////////

        Interactor():
          mUseAnalog        ( false ),
          mAllowPitch       ( true  ),
          mAllowYaw         ( true  ), 
          mDeltaTime        ( 0.0 ), 
          mNavigationSpeed  ( 0.0 ),
          mNavigationDelta  ( 0.0 ),
          mRotationSpeed    ( 0.0 ),
          mRotationDelta    ( 0.0 )
        {  
          gmtl::identity( mWandMatrix );           
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual ~Interactor()
        {
        }    

        /////////////////////////////////////////////////////////////////////////
        //
        // Initialization. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual void init()
        {
          mWand.init( "VJWand" );          
          mHead.init( "VJWand" );          

#if HAVE_KEYBOARDMOUSE
          KeyboardMouse::instance()->init();        
#endif // HAVE_KEYBOARDMOUSE

	  initDeviceProxies();
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Get getNavigator. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual Navigation* getNavigator()
        {
          return &mSceneNavigator;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Get current position. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual const gmtl::Matrix44f& currentPosition() const
        {
          return mSceneNavigator.currentPosition();      
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set current position. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void currentPosition( gmtl::Matrix44f& position )
        {
          mSceneNavigator.currentPosition( position );
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Get navigation speed. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual const double& navigationSpeed() const
        {
          return mNavigationSpeed;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set navigation speed. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void navigationSpeed( const double& speed )
        {
          mNavigationSpeed = speed;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Get delta for navigation. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual const double& navigationDelta() const
        {
          return mNavigationDelta;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set delta for navigation. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void navigationDelta( const double& delta )
        {
          mNavigationDelta = delta;        
        }      


        /////////////////////////////////////////////////////////////////////////
        //
        // Get rotation speed. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual const double& rotationSpeed() const
        {
          return mRotationSpeed;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set rotation speed.
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void rotationSpeed( const double& speed )
        {
          mRotationSpeed = speed;        
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Get rotation delta.
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual const double& rotationDelta() const
        {
          return mRotationDelta;

        }
        
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Set rotation delta
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void rotationDelta( const double& delta )
        {
          mRotationDelta = delta;
        }
        
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Get wand matrix. 
        //
        /////////////////////////////////////////////////////////////////////////      

        const gmtl::Matrix44f& wandMatrix() const
        {
          return mWandMatrix;
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Get head matrix. 
        //
        /////////////////////////////////////////////////////////////////////////      

        const gmtl::Matrix44f& headMatrix() const
        {
          return mHeadMatrix;
        }     
             

        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput0( double value )
        {
          if( value != -2.0)
          {
            mSceneNavigator.translateInX( value );
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput1( double value )
        {
          if( value != -2.0)
          {    
            mSceneNavigator.translateInZ( value );
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput2( double value )
        {
          if( value != -2.0)
          {
            mSceneNavigator.rotateInX( -value ); 
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput3( double value )
        {
          if( value != -2.0 )
          {
            mSceneNavigator.rotateInY( value ); 
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput4( double value ) 
        {
          if( value != -2.0 )
          {
            mSceneNavigator.rotateInZ( value ); 
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput5( double value )
        {
          if( value != -2.0 )
          {
            mSceneNavigator.pitch( value ); 
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput6( double value )
        {
          if( value != -2.0 )
          {
            mSceneNavigator.rotateInY( value ); 
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInput7( double value )
        {
          if( value != -2.0 )
          {
            mSceneNavigator.rotateInX( value ); 
          }
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput0( Core::DeviceData value )
        {           
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput1( Core::DeviceData value )
        {
          mSceneNavigator.translateInY( -1.0 );   
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput2( Core::DeviceData value )
        {  
        }


        void handleDigitalInput3( Core::DeviceData value )
        {
          mSceneNavigator.translateInY( 1.0 );  
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput4( Core::DeviceData value )
        {
          mSceneNavigator.deaccelerate();
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput5( Core::DeviceData value )
        {
          mSceneNavigator.accelerate();  
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput6( Core::DeviceData value )
        {
          mAllowPitch = !mAllowPitch; 

          mSceneNavigator.allowPitch( mAllowPitch ) ;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput7( Core::DeviceData value )
        {
          mAllowYaw = !mAllowYaw;  

          mSceneNavigator.allowYaw( mAllowYaw );
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput8( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput9( Core::DeviceData value )
        {
          reset();
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput10( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput11( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput12( Core::DeviceData value )
        {
          return;  
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput13( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput14( Core::DeviceData value )
        {
          mSceneNavigator.angulatDeaccelerate();
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput15( Core::DeviceData value )
        {
          mSceneNavigator.angulatAccelerate();
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput16( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput17( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput18( Core::DeviceData value )
        {
          return;  
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput19( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput20( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput21( Core::DeviceData value )
        {
          return;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput22( Core::DeviceData value )
        {  
          mUseTracker = true;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput23( Core::DeviceData value )
        {
          mUseTracker = true;
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInput24( Core::DeviceData value )
        {    
          return;
        }
  
         ///////////////////////////////////////////////////////////////////////////////
        //
        // Call handlers associated with given analog inputs. 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleAnalogInputs( const int& id, const double& value )
        {
          switch( id )
          {
            case 0: { handleAnalogInput0( value ); break; }
            case 1: { handleAnalogInput1( value ); break; }        
            case 2: { handleAnalogInput2( value ); break; }
            case 3: { handleAnalogInput3( value ); break; }
            case 4: { handleAnalogInput4( value ); break; }        
            case 5: { handleAnalogInput5( value ); break; }
            case 6: { break; }
            case 7: { break; }        
            default:{ break; }
          };
        }         


        ///////////////////////////////////////////////////////////////////////////////
        //
        // Call handlers associated with digital inputs. 
        //
        ///////////////////////////////////////////////////////////////////////////////

        void handleDigitalInputs( const int& id, const Core::DeviceData& value )
        { 
          switch( id )
          {
            case 0:  { handleDigitalInput0  ( value ); break; }
            case 1:  { handleDigitalInput1  ( value ); break; }        
            case 2:  { handleDigitalInput2  ( value ); break; }
            case 3:  { handleDigitalInput3  ( value ); break; }
            case 4:  { handleDigitalInput4  ( value ); break; }
            case 5:  { handleDigitalInput5  ( value ); break; }
            case 6:  { handleDigitalInput6  ( value ); break; }
            case 7:  { handleDigitalInput7  ( value ); break; }
            case 8:  { handleDigitalInput8  ( value ); break; }
            case 9:  { handleDigitalInput9  ( value ); break; }
            case 10: { handleDigitalInput10 ( value ); break; }  
            case 11: { handleDigitalInput11 ( value ); break; }  
            case 12: { handleDigitalInput12 ( value ); break; }  
            case 13: { handleDigitalInput13 ( value ); break; }  
            case 14: { handleDigitalInput14 ( value ); break; }  
            case 15: { handleDigitalInput15 ( value ); break; }  
            case 16: { handleDigitalInput16 ( value ); break; }  
            case 17: { handleDigitalInput17 ( value ); break; }  

            case 18: { handleDigitalInput18 ( value ); break; }
            case 19: { handleDigitalInput19 ( value ); break; }
            case 20: { handleDigitalInput20 ( value ); break; }
            case 21: { handleDigitalInput21 ( value ); break; }
            case 22: { handleDigitalInput22 ( value ); break; }
            case 23: { handleDigitalInput23 ( value ); break; }
            case 24: { handleDigitalInput24 ( value ); break; }

            default: { break; }      
          }        
        }

        ///////////////////////////////////////////////////////////////////////////////
        //
        // Read new data from the device proxies.
        //
        ///////////////////////////////////////////////////////////////////////////////

        void updateDeviceData()
        {
          Core::DeviceData value( Core::ZERO );   
          double data( 0.0 );

          vpr::Interval curTime = mWand->getTimeStamp();        

          mWandMatrix = mWand->getData();
          mHeadMatrix = mHead->getData();

          vpr::Interval diffTime = ( curTime - mPrevTime );
          
          mDeltaTime = diffTime.secf();        
          mPrevTime = curTime;      
          
          std::map< int, std::vector< Core::ActionState > >::const_iterator analogitr;
          std::map< int, std::vector< Core::ActionState > >::const_iterator digitalitr;

          if( Core::SharedData::mCommand.isLocal() )
          {  
            if( 1 )
            {
              static int firstTime = 1;

              int analogs = 0;
              int aindex  = 0;      
              
              for( analogitr = mAnalogActionMap.begin(); analogitr != mAnalogActionMap.end(); ++analogitr )
              {
                data = mController.getDeviceInputData( mAnalogInputMap[ aindex ], analogitr->second );        
        	
                // I had to do it as in gadageteer I couldnot find a way to check whether or not if a Analog
                // interface is present. The way it works that for the very first time if the value returned 
                // is -1.0 then it would be considered not active hence false then later we can assign value 
                // based on the fact that it is not active. I assigned -2.0 as an indiction that analog is not
                // present. 
                
                if( firstTime )
                {
                  if( data == -1.0 )
                  {
                    mAnalogInputStatusMap[ analogs ] = true;
                  }
                  else
                  {
                    mAnalogInputStatusMap[ analogs ] = true;
                  }
                }

                if( !mAnalogInputStatusMap[ analogs ] )
                {          
                  data = -2.0; 
                }

                Core::SharedData::mCommand->mAnalogInputs[ analogitr->first ] = data;        
                
                ++analogs;

                if( analogs == JOYSTICK_ANALOG_INPUTS_COUNT )
                {
                  ++aindex;
                }
              }
                      
              // We already gone thru the check.
              firstTime = 0;        
            }

            int digitals = 0;
            int dindex   = 0;

            for( digitalitr = mDigitalActionMap.begin(); digitalitr != mDigitalActionMap.end(); ++digitalitr )
            {
              value = mController.getDeviceInputData( mDigitalInputMap[ dindex ], digitalitr->second );      

              Core::SharedData::mCommand->mDigitalInputs[ digitalitr->first ] = ( int )value;
              
              ++digitals;

              if( digitals == JOYSTICK_DIGITAL_INPUTS_COUNT )
              {	      
                ++dindex;
              }
            }          
            
            // Update getNavigator. 
            mSceneNavigator.update( 1.0, Core::GLOBAL );

            // Update shared data. 
            Core::SharedData::mCommand->mSharedTransformMatrix = mSceneNavigator.currentPosition();
            Core::SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] = mSceneNavigator.pitchMatrix();      
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Update everything. Input, states etc. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void updateAll()
        {	        
          updateInputs();

          updateStates();  

#if HAVE_KEYBOARDMOUSE
            KeyboardMouse::instance()->update();
#endif // HAVE_KEYBOARDMOUSE
        }        

        /////////////////////////////////////////////////////////////////////////
        //
        // Reset.
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void reset()
        {
          if( Core::SharedData::mCommand.isLocal() )
          {
            gmtl::identity( Core::SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] );
          }
  
          if( !mUseAnalog )
          {
            mUseAnalog = !mUseAnalog;
          }         
          
          // Reset getNavigator.
          mSceneNavigator.reset(); 

          // Now reset navigation. 
        }

        virtual void resetNavigation()
        {
        }


      protected:

        /////////////////////////////////////////////////////////////////////////
        //
        // 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual void initDeviceProxies()
        {
          int numOfAxes    = Core::Defs::mJoystickAnalogProxies.size();
          int numOfButtons = Core::Defs::mJoystickDigitalProxies.size();

          setAnalogActionInputs  ( 0, Core::Defs::mJoystickAnalogProxies );    
          setDigitalActionButtons( 0, Core::Defs::mJoystickDigitalProxies );  

          mAnalogActionMap[ 0 ] = std::vector< Core::ActionState >( Core::Defs::mAxis0, Core::Defs::mAxis0 + numOfAxes);
          mAnalogActionMap[ 1 ] = std::vector< Core::ActionState >( Core::Defs::mAxis1, Core::Defs::mAxis1 + numOfAxes );
          mAnalogActionMap[ 2 ] = std::vector< Core::ActionState >( Core::Defs::mAxis2, Core::Defs::mAxis2 + numOfAxes );
          mAnalogActionMap[ 3 ] = std::vector< Core::ActionState >( Core::Defs::mAxis3, Core::Defs::mAxis3 + numOfAxes );
          mAnalogActionMap[ 4 ] = std::vector< Core::ActionState >( Core::Defs::mAxis4, Core::Defs::mAxis4 + numOfAxes );
          mAnalogActionMap[ 5 ] = std::vector< Core::ActionState >( Core::Defs::mAxis5, Core::Defs::mAxis5 + numOfAxes );  
         
          mDigitalActionMap[ 0 ]  = std::vector< Core::ActionState >( Core::Defs::mButton0,   Core::Defs::mButton0   + numOfButtons );
          mDigitalActionMap[ 1 ]  = std::vector< Core::ActionState >( Core::Defs::mButton1,   Core::Defs::mButton1   + numOfButtons );
          mDigitalActionMap[ 2 ]  = std::vector< Core::ActionState >( Core::Defs::mButton2,   Core::Defs::mButton2   + numOfButtons );
          mDigitalActionMap[ 3 ]  = std::vector< Core::ActionState >( Core::Defs::mButton3,   Core::Defs::mButton3   + numOfButtons );
          mDigitalActionMap[ 4 ]  = std::vector< Core::ActionState >( Core::Defs::mButton4,   Core::Defs::mButton4   + numOfButtons );
          mDigitalActionMap[ 5 ]  = std::vector< Core::ActionState >( Core::Defs::mButton5,   Core::Defs::mButton5   + numOfButtons );
          mDigitalActionMap[ 6 ]  = std::vector< Core::ActionState >( Core::Defs::mButton6,   Core::Defs::mButton6   + numOfButtons );
          mDigitalActionMap[ 7 ]  = std::vector< Core::ActionState >( Core::Defs::mButton7,   Core::Defs::mButton7   + numOfButtons );
          mDigitalActionMap[ 8 ]  = std::vector< Core::ActionState >( Core::Defs::mButton8,   Core::Defs::mButton8   + numOfButtons );
          mDigitalActionMap[ 9 ]  = std::vector< Core::ActionState >( Core::Defs::mButton9,   Core::Defs::mButton9   + numOfButtons );  
          mDigitalActionMap[ 10 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP0, Core::Defs::mButtonSP0 + numOfButtons );
          mDigitalActionMap[ 11 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP1, Core::Defs::mButtonSP1 + numOfButtons );
          mDigitalActionMap[ 12 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP2, Core::Defs::mButtonSP2 + numOfButtons );
          mDigitalActionMap[ 13 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP3, Core::Defs::mButtonSP3 + numOfButtons );
          mDigitalActionMap[ 14 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP4, Core::Defs::mButtonSP4 + numOfButtons );
          mDigitalActionMap[ 15 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP5, Core::Defs::mButtonSP5 + numOfButtons );
          mDigitalActionMap[ 16 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP6, Core::Defs::mButtonSP6 + numOfButtons );
          mDigitalActionMap[ 17 ] = std::vector< Core::ActionState >( Core::Defs::mButtonSP7, Core::Defs::mButtonSP7 + numOfButtons );

          // Now for trackers. 
          numOfAxes = Core::Defs::mTrackerAnalogProxies.size();
          numOfButtons = Core::Defs::mTrackerDigitalProxies.size();

          if(numOfAxes > 0)
          {
            setAnalogActionInputs( 1, Core::Defs::mTrackerAnalogProxies );
          }

          mAnalogActionMap[ 6 ] = std::vector< Core::ActionState >( Core::Defs::mAxisTr0, Core::Defs::mAxisTr0 +  numOfAxes );
          mAnalogActionMap[ 7 ] = std::vector< Core::ActionState >( Core::Defs::mAxisTr1, Core::Defs::mAxisTr1 +  numOfAxes );

          mDigitalActionMap[ 18 ] = std::vector< Core::ActionState >( Core::Defs::mButtonTr0, Core::Defs::mButtonTr0 + numOfButtons );
          mDigitalActionMap[ 19 ] = std::vector< Core::ActionState >( Core::Defs::mButtonTr1, Core::Defs::mButtonTr1 + numOfButtons );
          mDigitalActionMap[ 20 ] = std::vector< Core::ActionState >( Core::Defs::mButtonTr2, Core::Defs::mButtonTr2 + numOfButtons );
          mDigitalActionMap[ 21 ] =  std::vector< Core::ActionState >( Core::Defs::mButtonTr3, Core::Defs::mButtonTr3 + numOfButtons );
          mDigitalActionMap[ 22 ] = std::vector< Core::ActionState >( Core::Defs::mButtonTr4, Core::Defs::mButtonTr4 + numOfButtons );
          mDigitalActionMap[ 23 ] = std::vector< Core::ActionState >( Core::Defs::mButtonTr5, Core::Defs::mButtonTr5 + numOfButtons );

          setDigitalActionButtons( 1, Core::Defs::mTrackerDigitalProxies );        
        }


        /////////////////////////////////////////////////////////////////////////
        //      
        // Set analog input or analog inputs ( analog axes ).
        //
        /////////////////////////////////////////////////////////////////////////
        
        void setAnalogActionInputs( const int index, std::vector< std::string > inputs )
        {
          // Make sure list is long enough.
          while ( inputs.size() > mAnalogInputMap[ index ].size() )
          {
            mAnalogInputMap[ index ].push_back( new gadget::AnalogInterface() );
          }

          // Update all the entries.
          for ( unsigned int i = 0; i < inputs.size(); ++i )
          {
            mAnalogInputMap[ index ][ i ]->init( inputs[ i ] );
          }
        }


        /////////////////////////////////////////////////////////////////////////
        //
        // Set  digital or digital inputs ( buttons ) that can be used for
        // various actions. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        void setDigitalActionButtons( const int index, std::vector<std::string> inputs )
        {
          // Make sure list is long enough.
          while ( inputs.size() > mDigitalInputMap[ index ].size() )
          {
            mDigitalInputMap[ index ].push_back( new gadget::DigitalInterface() );
          }

          // Update all the entries.
          for ( unsigned int i = 0; i < inputs.size(); ++i )
          {
            mDigitalInputMap[ index ][ i ]->init( inputs[ i ] );
          }
        }       


        /////////////////////////////////////////////////////////////////////////
        //
        // Update inputs. 
        //
        /////////////////////////////////////////////////////////////////////////      
        
        virtual void updateInputs()
        {
          for( unsigned int i = 0; i < Core::SharedData::mCommand->mAnalogInputs.size(); ++i )
          { 
            handleAnalogInputs( i, Core::SharedData::mCommand->mAnalogInputs[ i ] );        
          }

          for( unsigned int i = 0; i < Core::SharedData::mCommand->mDigitalInputs.size(); ++i )
          {    
            if( ( Core::DeviceData )Core::SharedData::mCommand->mDigitalInputs[ i ] != 0 )
            {
              handleDigitalInputs( i, ( Core::DeviceData ) Core::SharedData::mCommand->mDigitalInputs[ i ] );
            }    
          }

          mSceneNavigator.pitchMatrix( Core::SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] );
        }


        ///////////////////////////////////////////////////////////////////////////////
        //
        // 
        //
        ///////////////////////////////////////////////////////////////////////////////

        virtual void updateStates()
        {
        }       

      protected:  

        std::map< int, DigitalInterfaces >            mDigitalInputMap;
        std::map< int, AnalogInterfaces  >            mAnalogInputMap;
        std::map< int, bool >                         mAnalogInputStatusMap;
        std::map< int , ActionStates >                mAnalogActionMap;
        std::map< int , ActionStates >                mDigitalActionMap;

        bool                                          mUseAnalog;
        bool                                          mAllowPitch;
        bool                                          mAllowYaw;
        bool                                          mUseTracker;
        
        vpr::Interval                                 mPrevTime;    

        float                                         mDeltaTime;

        double                                        mNavigationSpeed; 
        double                                        mNavigationDelta;
        double                                        mRotationSpeed;        
        double                                        mRotationDelta;

        gmtl::Matrix44f                               mWandMatrix;
        gmtl::Matrix44f                               mHeadMatrix;

        gadget::PositionInterface                     mWand;
        gadget::PositionInterface                     mHead;

        Navigation                                    mSceneNavigator;

	      Core::Controller                              mController;  

        
#if HAVE_KEYBOARDMOUSE      
        VJKeyboadMouseCallback*                       mKmCallBack;      
#endif // HAVE_KEYBOARDMOUSE

    };
  }
}

#endif // __VEDA_DESIGN_INTERACTION_H__

