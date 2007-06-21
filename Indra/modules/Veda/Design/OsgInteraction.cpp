
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#ifdef HAVE_OSG

#include "Design/OsgInteraction.h"

#include "Core/Defs.h"

#include "osg/StateAttribute"
#include "osg/Geometry"

#include "gmtl/MatrixOps.h"
#include "gmtl/Matrix.h"
#include "gmtl/Vec.h"
#include "gmtl/Generate.h"

#include "vrj/Draw/DrawManager.h"
#include "vrj/Display/DisplayManager.h"

#include "OsgTools/SG/OsgFind.h"

#include <vector>

using namespace Design;

const int JOYSTICK_ANALOG_INPUTS_COUNT  = 06 ;
const int JOYSTICK_DIGITAL_INPUTS_COUNT = 18 ;

///////////////////////////////////////////////////////////////////////////////
//
// Constructor.
//
///////////////////////////////////////////////////////////////////////////////

OsgInteraction::OsgInteraction() :
  Interaction       (),
  mScenePivot       ( 0.0, 0.0, 0.0 ), 
  mObjectPivot      ( 0.0, 0.0, 0.0 ), 
  mSceneRadius      ( 0.0 )  
{
}

///////////////////////////////////////////////////////////////////////////////
//
// Destructor.
//
///////////////////////////////////////////////////////////////////////////////

OsgInteraction::~OsgInteraction()
{
}

///////////////////////////////////////////////////////////////////////////////
//
// Initialization.
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::init()
{
  Interaction::init();
  
  defineControls();      

  #ifdef HAVE_KEYBOARDMOUSE
  osg::ref_ptr< osg::Group > transform = dynamic_cast< osg::Group* >( Util::OsgFind::findNodeByName( mSceneRootNode.get(), "mModelTransformNode" ) );        
  if( transform.valid() )
  {
    if( KeyboardMouse::instance()->getCallBack() == NULL )
    {
      mKmCallBack = new VJKeyboadMouseCallback( group.get() );
      KeyboardMouse::instance()->setCallBack( mKmCallBack );
      KeyboardMouse::instance()->setInputArea( 
      RenderGlobals::mDisplay.width(), RenderGlobals::mDisplay.height() );        
    }
  }
  #endif
}    

///////////////////////////////////////////////////////////////////////////////
//
// Set navigation parameters to their default.
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::resetNavigation()
{
  osg::ref_ptr< osg::Node > group = OsgTools::SG::OsgFind::findNodeByName( mSceneRootNode.get(), "mModelGroupNode" );
  
  if( mNavigationSpeed != 0.0 )
  {
    mSceneNavigator.rotationSpeed( mNavigationSpeed );
  }
  else
  {        
    if( group.valid() )
    {
      osg::BoundingSphere bs = group->getBound();

      mScenePivot  = bs.center();
      mSceneRadius = bs.radius();      
  
      // Based off some approximation.      
      mSceneNavigator.navigationSpeed( mSceneRadius / 100.0f );
    }
    else 
    { 
      std::cerr << "Error 1267807201e : Node not found. " << std::endl;
    }
  }

  if( mNavigationDelta != 0.0 )
  {
    mSceneNavigator.navigationDelta( mNavigationDelta );          
  }
  else  
  {
    mSceneNavigator.navigationDelta( mSceneNavigator.navigationSpeed() / 50.0 );                        
  }

  if( mRotationSpeed != 0.0 )
  {
    mSceneNavigator.rotationSpeed( mRotationSpeed );          
  }

  if( mRotationDelta != 0.0 )
  {
    mSceneNavigator.rotationDelta( mRotationDelta );
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// Get scene root. 
//
///////////////////////////////////////////////////////////////////////////////

osg::Group* OsgInteraction::root()
{
  return mSceneRootNode.get();
}

///////////////////////////////////////////////////////////////////////////////
//
// Set scene root. 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::root( void* node )
{
  mSceneRootNode = static_cast< osg::Group* >( node );
  
  if( mSceneRootNode.valid() )
  {
    mSceneTransformNode = dynamic_cast< osg::MatrixTransform* >( OsgTools::SG::OsgFind::findNodeByName
                          ( mSceneRootNode.get(), "mSceneTransformNode" ) );                    
    
    if( !mSceneTransformNode.valid() )
    {
    }
    
    setSceneWand();         
  }
  else
  {  
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// Get scene transform.
//
///////////////////////////////////////////////////////////////////////////////

osg::MatrixTransform* OsgInteraction::transform()
{
  return mSceneTransformNode.get();
}

///////////////////////////////////////////////////////////////////////////////
//
// Set wand in the scene. 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::setSceneWand()
{
  mSceneWand = dynamic_cast< osg::Group* >( OsgTools::SG::OsgFind::findNodeByName( mSceneRootNode.get(), "WandGroup" ) );      
  mSceneWandTransform = dynamic_cast< osg::MatrixTransform* >( OsgTools::SG::OsgFind::findNodeByName( mSceneRootNode.get(), "WandTransform" ) );      

  if( !mSceneWand.valid() && !mSceneTransformNode.valid() )
  {
  }            
}

///////////////////////////////////////////////////////////////////////////////
//
// Get navigation mode.
//
///////////////////////////////////////////////////////////////////////////////

Core::NavigationMode OsgInteraction::navigationMode()
{
  return mSceneNavigator.navigationMode();

}

///////////////////////////////////////////////////////////////////////////////
//
// Set navigation mode.
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::navigationMode( Core::NavigationMode mode )
{
  mSceneNavigator.navigationMode( mode );
}


///////////////////////////////////////////////////////////////////////////////
//
// Get navigator. 
//
///////////////////////////////////////////////////////////////////////////////

Navigation& OsgInteraction::navigator( Core::InteractionMode mode )
{
  switch( mode )
  {
    case Core::WORLD:
    {
      return mSceneNavigator;      
    }
    case Core::OBJECT:
    {
      return mLocalNavigator;
    }
    case Core::WAND:
    {
      return mWandNavigator;
    }
    default:
    {
      throw "Error 3213354398e: Undefined mode. ";
    }
  };
}

///////////////////////////////////////////////////////////////////////////////
//
// Define mapping for analog and digital inputs. 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::defineControls()
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

///////////////////////////////////////////////////////////////////////////////
//
// Take action for analog inputs. 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::takeActionAnalog( Core::InteractionMode mode, int id, double value )
{
  switch( mode )
  {
    case Core::WORLD:
    {
      switch( id )
      {
        case 0: { joystickAxis1GlobalAction( value ); break; }
        case 1: { joystickAxis2GlobalAction( value ); break; }        
        case 2: { joystickAxis3GlobalAction( value ); break; }
        case 3: { joystickAxis4GlobalAction( value ); break; }
        case 4: { joystickAxis5GlobalAction( value ); break; }        
        case 5: { joystickAxis6GlobalAction( value ); break; }
        case 6: { break; }
        case 7: { break; }        
        default:{ break; }
      }
      break;
    }
    case Core::OBJECT:
    {  
      switch( id )
      {
        case 0: { mLocalNavigator.translateInX  ( value ); break; }
        case 1: { mLocalNavigator.translateInZ  ( value ); break; }        
        case 2: { mLocalNavigator.rotateInX     ( value ); break; }
        case 3: { mLocalNavigator.rotateInY     ( value ); break; }
        case 4: { break; }
        default:{ break; }
      }    
      break;
    }
    case Core::WAND:
    {       
      value = -value;
      switch( id )
      {
        case 0: { mWandNavigator.translateInX ( value );  break; }
        case 1: { mWandNavigator.translateInY ( value );  break; }        
        case 2: { mWandNavigator.rotateInX    ( -value ); break; }
        case 3: { mWandNavigator.rotateInY    ( value );  break; }
        case 4: { break; }
        default:{ break; }
      }      
      break;
    }
    default:
    {
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// Take action for digital inputs. 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::takeActionDigital( Core::InteractionMode mode, int id, Core::DeviceData value )
{
  switch( mode )
  {
    case Core::WORLD:
    {
      switch( id )
      {
        case 0:  { joystickButton1GlobalAction  ( value ); break; }
        case 1:  { joystickButton2GlobalAction  ( value ); break; }        
        case 2:  { joystickButton3GlobalAction  ( value ); break; }
        case 3:  { joystickButton4GlobalAction  ( value ); break; }
        case 4:  { joystickButton5GlobalAction  ( value ); break; }
        case 5:  { joystickButton6GlobalAction  ( value ); break; }
        case 6:  { joystickButton7GlobalAction  ( value ); break; }
        case 7:  { joystickButton8GlobalAction  ( value ); break; }
        case 8:  { joystickButton9GlobalAction  ( value ); break; }
        case 9:  { joystickButton10GlobalAction ( value ); break; }
        case 10: { joystickButton11GlobalAction ( value ); break; }  
        case 11: { joystickButton12GlobalAction ( value ); break; }  
        case 12: { joystickButton13GlobalAction ( value ); break; }  
        case 13: { joystickButton14GlobalAction ( value ); break; }  
        case 14: { joystickButton15GlobalAction ( value ); break; }  
        case 15: { joystickButton16GlobalAction ( value ); break; }  
        case 16: { joystickButton17GlobalAction ( value ); break; }  
        case 17: { joystickButton18GlobalAction ( value ); break; }  

        case 18: { trackButton1GlobalAction ( value ); break; }
        case 19: { trackButton2GlobalAction ( value ); break; }
        case 20: { trackButton3GlobalAction ( value ); break; }
        case 21: { trackButton4GlobalAction ( value ); break; }
        case 22: { trackButton5GlobalAction ( value ); break; }
        case 23: { trackButton6GlobalAction ( value ); break; }
        case 24: { trackButton7GlobalAction ( value ); break; }

        default: { break; }      
      }
      break;
    }    
    default:
    {
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickAxis1GlobalAction( double value )
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

void OsgInteraction::joystickAxis2GlobalAction( double value )
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

void OsgInteraction::joystickAxis3GlobalAction( double value )
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

void OsgInteraction::joystickAxis4GlobalAction( double value )
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

void OsgInteraction::joystickAxis5GlobalAction( double value ) 
{
  if( value != 0.0 )
  {
    mSceneNavigator.rotateInZ( value ); 
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickAxis6GlobalAction( double value )
{
  if( value !=0.0 )
  {
    mSceneNavigator.pitch( value ); 
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackerAxis1GlobalAction( double value )
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

void OsgInteraction::trackerAxis2GlobalAction( double value )
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

void OsgInteraction::joystickButton1GlobalAction( Core::DeviceData value )
{  
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton2GlobalAction( Core::DeviceData value )
{
  mSceneNavigator.translateInY( -1.0 );   
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton3GlobalAction( Core::DeviceData value )
{  
}

void OsgInteraction::joystickButton4GlobalAction( Core::DeviceData value )
{
  mSceneNavigator.translateInY( 1.0 );  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton5GlobalAction( Core::DeviceData value )
{
  mSceneNavigator.deaccelerate();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton6GlobalAction( Core::DeviceData value )
{
  mSceneNavigator.accelerate();  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton7GlobalAction( Core::DeviceData value )
{
  mAllowPitch = !mAllowPitch; 

  mSceneNavigator.allowPitch( mAllowPitch ) ;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton8GlobalAction( Core::DeviceData value )
{
  mAllowYaw = !mAllowYaw;  

  mSceneNavigator.allowYaw( mAllowYaw );
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton9GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton10GlobalAction( Core::DeviceData value )
{
  reset();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton11GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton12GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton13GlobalAction( Core::DeviceData value )
{
  return;  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton14GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton15GlobalAction( Core::DeviceData value )
{
  mSceneNavigator.angulatDeaccelerate();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton16GlobalAction( Core::DeviceData value )
{
  mSceneNavigator.angulatAccelerate();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton17GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton18GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton1GlobalAction( Core::DeviceData value )
{
  return;  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton2GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton3GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton4GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton5GlobalAction( Core::DeviceData value )
{  
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton6GlobalAction( Core::DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton7GlobalAction( Core::DeviceData value )
{    
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::updateDeviceData()
{
  Core::DeviceData value = Core::ZERO;   
  double data      = 0.0;

  Interaction::updateDeviceData();  
  
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
            mAnalogInputStatusMap[ analogs ] = false;
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
    
    switch( mInteractionMode )
    {
      case Core::OBJECT:
      {
        mLocalNavigator.update( mDeltaTime, Core::GLOBAL );  
        Core::SharedData::mCommand->mSharedTransformMatrix = mLocalNavigator.currentPosition();  
        break;
      }
      case Core::WAND:
      {
        mWandNavigator.update( mDeltaTime, Core::GLOBAL );
        Core::SharedData::mCommand->mSharedTransformMatrix = mWandNavigator.currentPosition();
      }
      case Core::WORLD: 
      {
        mSceneNavigator.update( 1.0, Core::GLOBAL );
        Core::SharedData::mCommand->mSharedTransformMatrix = mSceneNavigator.currentPosition();
        Core::SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] = mSceneNavigator.pitchMatrix();      
        break;
      }
    };      
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::updateAll()
{
  updateInputs();

  updateStates();  

  #ifdef HAVE_KEYBOARDMOUSE
  KeyboardMouse::instance()->update();
  #endif
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::updateInputs()
{
  for( unsigned int i = 0; i < Core::SharedData::mCommand->mAnalogInputs.size(); ++i )
  {    
    takeActionAnalog( mInteractionMode, i, Core::SharedData::mCommand->mAnalogInputs[ i ] );        
  }

  for( unsigned int i = 0; i < Core::SharedData::mCommand->mDigitalInputs.size(); ++i )
  {
    if( ( Core::DeviceData )Core::SharedData::mCommand->mDigitalInputs[ i ] != 0 )
    {
      takeActionDigital( mInteractionMode, i, ( Core::DeviceData ) Core::SharedData::mCommand->mDigitalInputs[ i ] );
    }    
  }

  mSceneNavigator.pitchMatrix( Core::SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] );
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::updateStates()
{
  updateTransforms();  

  updateInteractions();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::updateTransforms()
{   
  switch( mInteractionMode )
  {  
    case Core::WORLD:
    {     
      // Calculate the initial translation ( one time ). 
      static osg::Vec3f offset = ( ( osg::Matrix ) mSceneTransformNode->getMatrix() ).getTrans();    

      // Scene transform matrix.
      osg::Matrixf matrix =  osg::Matrix( Core::SharedData::mCommand->mSharedTransformMatrix.mData );
      
      // Find resultant translation vector. 
      matrix.setTrans( offset + matrix.getTrans() );    

      mSceneTransformNode->setMatrix( matrix );
      
      #ifdef HAVE_KEYBOARDMOUSE
      sceneTransformNode->preMult( mKmCallBack->getViewMatrix() );
      #endif
      
      break;
    }
    default:
    {      
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::updateInteractions()
{  
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::reset()
{
  if( Core::SharedData::mCommand.isLocal() )
  {
    gmtl::identity( Core::SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] );
  }

  Interaction::reset();
}

#endif 
