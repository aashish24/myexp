
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
// Interface defined for an interaction system. 
// Todo:
// Separate the controller from the the logic. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DESIGN_INTERACTION_H__
#define __DESIGN_INTERACTION_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "gadget/Type/DigitalInterface.h"
#include "gadget/Type/AnalogInterface.h"
#include "gadget/Type/DeviceInterface.h"
#include "gadget/Type/PositionInterface.h"

#include "gmtl/Matrix.h"

#include "Veda/Core/Types.h"
#include "Veda/Core/Controller.h"

#include "Veda/Design/Navigation.h"

#if HAVE_KEYBOARDMOUSE
#include "Dev/VJKeyboardMouseCallback.h"
#endif

#include "Veda/Export.h"

namespace Veda
{
  namespace Design
  {
    class VEDA_EXPORT Interaction
    {
      public:
        
        /////////////////////////////////////////////////////////////////////////
        //
        // Easy to remember names. 
        // 
        /////////////////////////////////////////////////////////////////////////

        typedef std::vector< gadget::DigitalInterface* >  DigitalInterfaces;
        typedef std::vector< gadget::AnalogInterface* >   AnalogInterfaces;
	typedef std::vector< Core::ActionState >                ActionStates;

        /////////////////////////////////////////////////////////////////////////
        //
        // Constructor.
        // 
        /////////////////////////////////////////////////////////////////////////

        Interaction()  : 
          mUseAnalog        ( false ),
          mAllowPitch       ( true  ),
          mAllowYaw         ( true  ), 
          mDeltaTime        ( 0.0 ), 
          mNavigationSpeed  ( 0.0 ),
          mNavigationDelta  ( 0.0 ),
          mRotationSpeed    ( 0.0 ),
          mRotationDelta    ( 0.0 ),    
	  mInteractionMode  ( Core::WORLD )        
        {  
          gmtl::identity( mWandMatrix );           
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Destructor. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual ~Interaction()
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

          #ifdef HAVE_KEYBOARDMOUSE
          KeyboardMouse::instance()->init();        
          #endif
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Derived class VEDA_EXPORT has to provide definition for controls. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual void defineControls()
        {
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Get navigator. 
        // 
        /////////////////////////////////////////////////////////////////////////

        virtual Navigation* navigator()
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
        // Reset.
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void reset()
        {
          if( !mUseAnalog )
          {
            mUseAnalog = !mUseAnalog;
          }
          
          // Reset all three navigations. 
          mSceneNavigator.reset(); mLocalNavigator.reset(); mWandNavigator.reset();
          
          resetNavigation();
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Derived class VEDA_EXPORT has to implement this. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void resetNavigation()
        {
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Derived class VEDA_EXPORT has to implement this. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void updateAll()
        {
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Update data from devices. 
        //
        /////////////////////////////////////////////////////////////////////////      

        virtual void updateDeviceData()
        {        
          vpr::Interval curTime   = mWand->getTimeStamp();        

          mWandMatrix             = mWand->getData();

          vpr::Interval diffTime  = curTime -  mPrevTime;
          
          mDeltaTime              = diffTime.secf();        
          mPrevTime                = curTime;      
        }
      
        /////////////////////////////////////////////////////////////////////////
        //
        // Get current interaction mode.  
        //
        /////////////////////////////////////////////////////////////////////////      

	      const Core::InteractionMode& getInteactionMode() const
        {
          return mInteractionMode;
        }

        /////////////////////////////////////////////////////////////////////////
        //
        // Set current interaction mode. 
        //
        /////////////////////////////////////////////////////////////////////////      

        void setInteractionMode( const Core::InteractionMode& mode )
        {
            mInteractionMode = mode;
        }      

        /////////////////////////////////////////////////////////////////////////
        //
        // Set control function that will define how the device data transformed 
        // to the data used for navigation. 
        //
        /////////////////////////////////////////////////////////////////////////      

	    /*virtual void  controlFunction( Math::Function* func )
        {
          mControlFunction = func;
        }*/

      protected:

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

      protected:  

        std::map< int, DigitalInterfaces >            mDigitalInputMap;
        std::map< int, AnalogInterfaces  >            mAnalogInputMap;
        std::map< int, bool >                         mAnalogInputStatusMap;
        std::map< int , ActionStates >                mAnalogActionMap;
        std::map< int , ActionStates >                mDigitalActionMap;

        bool                                          mUseAnalog;
        bool                                          mAllowPitch;
        bool                                          mAllowYaw;
        
        gadget::PositionInterface                     mWand;

        vpr::Interval                                 mPrevTime;    

        float                                         mDeltaTime;

        Navigation                                    mSceneNavigator;
        Navigation                                    mLocalNavigator;
        Navigation                                    mWandNavigator;

        double                                        mNavigationSpeed; 
        double                                        mNavigationDelta;
        double                                        mRotationSpeed;
        double                                        mRotationDelta;

        Core::InteractionMode                         mInteractionMode;

	Core::Controller                              mController;  

        gmtl::Matrix44f                               mWandMatrix;

        #if HAVE_KEYBOARDMOUSE      
        VJKeyboadMouseCallback*                       mKmCallBack;      
        #endif

        //osg::ref_ptr< Math::Function >              mControlFunction;
    };
  }
}

#endif // __DESIGN_INTERACTION_H__

