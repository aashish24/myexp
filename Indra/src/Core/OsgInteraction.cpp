
#include "Core/OsgInteraction.h"
#include "Core/Defs.h"

#include "osg/StateAttribute"
#include "osg/Geometry"

#include "gmtl/MatrixOps.h"
#include "gmtl/Matrix.h"
#include "gmtl/Vec.h"
#include "gmtl/Generate.h"

#include "vrj/Draw/DrawManager.h"
#include "vrj/Display/DisplayManager.h"

#include <vector>

using namespace Core;

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
  mControlFunction =  new Math::ExpFunction( 2.0 );
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
  osg::ref_ptr< osg::Node > group = Util::OsgFind::findNodeByName( mSceneRootNode.get(), "mModelGroupNode" );
  
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
    mSceneTransformNode = dynamic_cast< osg::MatrixTransform* >( Util::OsgFind::findNodeByName
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
  mSceneWand = dynamic_cast< osg::Group* >( Util::OsgFind::findNodeByName( mSceneRootNode.get(), "WandGroup" ) );      
  mSceneWandTransform = dynamic_cast< osg::MatrixTransform* >( Util::OsgFind::findNodeByName( mSceneRootNode.get(), "WandTransform" ) );      

  if( !mSceneWand.valid() && !mSceneTransformNode.valid() )
  {
  }            
}

///////////////////////////////////////////////////////////////////////////////
//
// Get navigation mode.
//
///////////////////////////////////////////////////////////////////////////////

NavigationMode OsgInteraction::navigationMode()
{
  return mSceneNavigator.navigationMode();

}

///////////////////////////////////////////////////////////////////////////////
//
// Set navigation mode.
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::navigationMode( NavigationMode mode )
{
  mSceneNavigator.navigationMode( mode );
}


///////////////////////////////////////////////////////////////////////////////
//
// Get navigator. 
//
///////////////////////////////////////////////////////////////////////////////

Navigation& OsgInteraction::navigator( InteractionMode mode )
{
  switch( mode )
  {
    case WORLD:
    {
      return mSceneNavigator;      
    }
    case OBJECT:
    {
      return mLocalNavigator;
    }
    case WAND:
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
  int numOfAxes    = Defs::mJoystickAnalogProxies.size();
  int numOfButtons = Defs::mJoystickDigitalProxies.size();

  setAnalogActionInputs  ( 0, Defs::mJoystickAnalogProxies );    
  setDigitalActionButtons( 0, Defs::mJoystickDigitalProxies );  

  mAnalogActionMap[ 0 ] = std::vector< ActionState >( Defs::mAxis0, Defs::mAxis0 + numOfAxes);
  mAnalogActionMap[ 1 ] = std::vector< ActionState >( Defs::mAxis1, Defs::mAxis1 + numOfAxes );
  mAnalogActionMap[ 2 ] = std::vector< ActionState >( Defs::mAxis2, Defs::mAxis2 + numOfAxes );
  mAnalogActionMap[ 3 ] = std::vector< ActionState >( Defs::mAxis3, Defs::mAxis3 + numOfAxes );
  mAnalogActionMap[ 4 ] = std::vector< ActionState >( Defs::mAxis4, Defs::mAxis4 + numOfAxes );
  mAnalogActionMap[ 5 ] = std::vector< ActionState >( Defs::mAxis5, Defs::mAxis5 + numOfAxes );  
 
  mDigitalActionMap[ 0 ]  = std::vector< ActionState >( Defs::mButton0,   Defs::mButton0   + numOfButtons );
  mDigitalActionMap[ 1 ]  = std::vector< ActionState >( Defs::mButton1,   Defs::mButton1   + numOfButtons );
  mDigitalActionMap[ 2 ]  = std::vector< ActionState >( Defs::mButton2,   Defs::mButton2   + numOfButtons );
  mDigitalActionMap[ 3 ]  = std::vector< ActionState >( Defs::mButton3,   Defs::mButton3   + numOfButtons );
  mDigitalActionMap[ 4 ]  = std::vector< ActionState >( Defs::mButton4,   Defs::mButton4   + numOfButtons );
  mDigitalActionMap[ 5 ]  = std::vector< ActionState >( Defs::mButton5,   Defs::mButton5   + numOfButtons );
  mDigitalActionMap[ 6 ]  = std::vector< ActionState >( Defs::mButton6,   Defs::mButton6   + numOfButtons );
  mDigitalActionMap[ 7 ]  = std::vector< ActionState >( Defs::mButton7,   Defs::mButton7   + numOfButtons );
  mDigitalActionMap[ 8 ]  = std::vector< ActionState >( Defs::mButton8,   Defs::mButton8   + numOfButtons );
  mDigitalActionMap[ 9 ]  = std::vector< ActionState >( Defs::mButton9,   Defs::mButton9   + numOfButtons );  
  mDigitalActionMap[ 10 ] = std::vector< ActionState >( Defs::mButtonSP0, Defs::mButtonSP0 + numOfButtons );
  mDigitalActionMap[ 11 ] = std::vector< ActionState >( Defs::mButtonSP1, Defs::mButtonSP1 + numOfButtons );
  mDigitalActionMap[ 12 ] = std::vector< ActionState >( Defs::mButtonSP2, Defs::mButtonSP2 + numOfButtons );
  mDigitalActionMap[ 13 ] = std::vector< ActionState >( Defs::mButtonSP3, Defs::mButtonSP3 + numOfButtons );
  mDigitalActionMap[ 14 ] = std::vector< ActionState >( Defs::mButtonSP4, Defs::mButtonSP4 + numOfButtons );
  mDigitalActionMap[ 15 ] = std::vector< ActionState >( Defs::mButtonSP5, Defs::mButtonSP5 + numOfButtons );
  mDigitalActionMap[ 16 ] = std::vector< ActionState >( Defs::mButtonSP6, Defs::mButtonSP6 + numOfButtons );
  mDigitalActionMap[ 17 ] = std::vector< ActionState >( Defs::mButtonSP7, Defs::mButtonSP7 + numOfButtons );

  // Now for trackers. 
  numOfAxes = Defs::mTrackerAnalogProxies.size();
  numOfButtons = Defs::mTrackerDigitalProxies.size();

  if(numOfAxes > 0)
  {
    setAnalogActionInputs( 1, Defs::mTrackerAnalogProxies );
  }

  mAnalogActionMap[ 6 ] = std::vector< ActionState >( Defs::mAxisTr0, Defs::mAxisTr0 +  numOfAxes );
  mAnalogActionMap[ 7 ] = std::vector< ActionState >( Defs::mAxisTr1, Defs::mAxisTr1 +  numOfAxes );

  mDigitalActionMap[ 18 ] = std::vector< ActionState >( Defs::mButtonTr0, Defs::mButtonTr0 + numOfButtons );
  mDigitalActionMap[ 19 ] = std::vector< ActionState >( Defs::mButtonTr1, Defs::mButtonTr1 + numOfButtons );
  mDigitalActionMap[ 20 ] = std::vector< ActionState >( Defs::mButtonTr2, Defs::mButtonTr2 + numOfButtons );
  mDigitalActionMap[ 21 ] =  std::vector< ActionState >( Defs::mButtonTr3, Defs::mButtonTr3 + numOfButtons );
  mDigitalActionMap[ 22 ] = std::vector< ActionState >( Defs::mButtonTr4, Defs::mButtonTr4 + numOfButtons );
  mDigitalActionMap[ 23 ] = std::vector< ActionState >( Defs::mButtonTr5, Defs::mButtonTr5 + numOfButtons );

  setDigitalActionButtons( 1, Defs::mTrackerDigitalProxies );    
}  

///////////////////////////////////////////////////////////////////////////////
//
// Take action for analog inputs. 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::takeActionAnalog( InteractionMode mode, int id, double value )
{
  switch( mode )
  {
    case WORLD:
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
    case OBJECT:
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
    case WAND:
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

void OsgInteraction::takeActionDigital( InteractionMode mode, int id, DeviceData value )
{
  switch( mode )
  {
    case WORLD:
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
    mSceneNavigator.translateInX( mControlFunction->f( value, value ) );
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
    mSceneNavigator.translateInZ( mControlFunction->f( value, value ) );
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

void OsgInteraction::joystickButton1GlobalAction( DeviceData value )
{  
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton2GlobalAction( DeviceData value )
{
  mSceneNavigator.translateInY( -1.0 );   
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton3GlobalAction( DeviceData value )
{  
}

void OsgInteraction::joystickButton4GlobalAction( DeviceData value )
{
  mSceneNavigator.translateInY( 1.0 );  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton5GlobalAction( DeviceData value )
{
  mSceneNavigator.deaccelerate();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton6GlobalAction( DeviceData value )
{
  mSceneNavigator.accelerate();  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton7GlobalAction( DeviceData value )
{
  mAllowPitch = !mAllowPitch; 

  mSceneNavigator.allowPitch( mAllowPitch ) ;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton8GlobalAction( DeviceData value )
{
  mAllowYaw = !mAllowYaw;  

  mSceneNavigator.allowYaw( mAllowYaw );
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton9GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton10GlobalAction( DeviceData value )
{
  reset();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton11GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton12GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton13GlobalAction( DeviceData value )
{
  return;  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton14GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton15GlobalAction( DeviceData value )
{
  mSceneNavigator.angulatDeaccelerate();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton16GlobalAction( DeviceData value )
{
  mSceneNavigator.angulatAccelerate();
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton17GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::joystickButton18GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton1GlobalAction( DeviceData value )
{
  return;  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton2GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton3GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton4GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton5GlobalAction( DeviceData value )
{  
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton6GlobalAction( DeviceData value )
{
  return;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void OsgInteraction::trackButton7GlobalAction( DeviceData value )
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
  DeviceData value = ZERO;   
  double data      = 0.0;

  Interaction::updateDeviceData();  
  
  std::map< int, std::vector< ActionState > >::const_iterator analogitr;
  std::map< int, std::vector< ActionState > >::const_iterator digitalitr;

  if( SharedData::mCommand.isLocal() )
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

         SharedData::mCommand->mAnalogInputs[ analogitr->first ] = data;        
        
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
      
      SharedData::mCommand->mDigitalInputs[ digitalitr->first ] = ( int )value;
      
      ++digitals;

      if( digitals == JOYSTICK_DIGITAL_INPUTS_COUNT )
      {
        ++dindex;
      }
    }          
    
    switch( mInteractionMode )
    {
      case OBJECT:
      {
        mLocalNavigator.update( mDeltaTime, GLOBAL );  
        SharedData::mCommand->mSharedTransformMatrix = mLocalNavigator.currentPosition();  
        break;
      }
      case WAND:
      {
        mWandNavigator.update( mDeltaTime, GLOBAL );
        SharedData::mCommand->mSharedTransformMatrix = mWandNavigator.currentPosition();

      }
      case WORLD: 
      {
        mSceneNavigator.update( 1.0, GLOBAL );
        SharedData::mCommand->mSharedTransformMatrix = mSceneNavigator.currentPosition();
        SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] = mSceneNavigator.pitchMatrix();      
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
  for( unsigned int i = 0; i < SharedData::mCommand->mAnalogInputs.size(); ++i )
  {    
    takeActionAnalog( mInteractionMode, i, SharedData::mCommand->mAnalogInputs[ i ] );        
  }

  for( unsigned int i = 0; i < SharedData::mCommand->mDigitalInputs.size(); ++i )
  {
    if( ( DeviceData )SharedData::mCommand->mDigitalInputs[ i ] != 0 )
    {
      takeActionDigital( mInteractionMode, i, ( DeviceData ) SharedData::mCommand->mDigitalInputs[ i ] );
    }    
  }

  mSceneNavigator.pitchMatrix( SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] );
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
    case WORLD:
    {     
      // Calculate the initial translation ( one time ). 
      static osg::Vec3f offset = ( ( osg::Matrix ) mSceneTransformNode->getMatrix() ).getTrans();    

      // Scene transform matrix.
      osg::Matrixf matrix =  osg::Matrix( SharedData::mCommand->mSharedTransformMatrix.mData );
      
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
  if( SharedData::mCommand.isLocal() )
  {
    gmtl::identity( SharedData::mCommand->mSharedMatrixTypeObjects[ "PitchMatrix" ] );
  }

  Interaction::reset();
}

