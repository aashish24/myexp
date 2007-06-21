
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/Design/Navigation.h"
#include "Veda/Core/SharedData.h"

#include "gmtl/Vec.h"
#include "gmtl/VecOps.h"

using namespace Design;

///////////////////////////////////////////////////////////////////////////////
//
// Constructor. 
//
///////////////////////////////////////////////////////////////////////////////

Navigation::Navigation() : 
  mNavigationSpeed      ( 10.0 ), 
  mRotationSpeed        ( gmtl::Math::deg2Rad( 0.1 ) ), 
  mMinNavigationSpeed   ( 0.0 ), 
  mMaxNavigationSpeed   ( 10000000000.0 ),     
  mMinRotationSpeed     ( gmtl::Math::deg2Rad( 0.001 ) ), 
  mMaxRotationSpeed     ( gmtl::Math::deg2Rad( 90.0 ) ), 
  mNavigationDelta      ( 1.0 ), 
  mRotationDelta        ( gmtl::Math::deg2Rad( 0.05 ) ), 
  mFrameRenderTime      ( 1.0 / 30.0 ), 
  mFramesPerSecond      ( 30.0 ), 
  mUseRange             ( false ),         
  mNavigationMode       ( Core::TRACKBALL ), 
  mAllowPitch           ( true ), 
  mAllowYaw             ( true ), 
  mAllowRoll            ( true )
{
  gmtl::identity( mCurrentPosition  ); gmtl::identity( mHomePosition );   gmtl::identity( mPitchMatrix  );
  mNavigationVel.set( 0.0, 0.0, 0.0 ); mRotationVel.set( 0.0, 0.0, 0.0 );       
}

///////////////////////////////////////////////////////////////////////////////
//
// Destructor. 
//
///////////////////////////////////////////////////////////////////////////////

Navigation::~Navigation()
{
}

///////////////////////////////////////////////////////////////////////////////
//
// Get current position matrix. 
//
///////////////////////////////////////////////////////////////////////////////

const gmtl::Matrix44f& Navigation::currentPosition() const
{
  return mCurrentPosition;
}

///////////////////////////////////////////////////////////////////////////////
//
// Set current positional matrix.
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::currentPosition( const gmtl::Matrix44f& position )
{
  mCurrentPosition = position;        
}

///////////////////////////////////////////////////////////////////////////////
//
// Get pitch matrix. 
//
///////////////////////////////////////////////////////////////////////////////

const gmtl::Matrix44f& Navigation::pitchMatrix() const
{
  return mPitchMatrix;
}

///////////////////////////////////////////////////////////////////////////////
//
// Set pitch matrix. 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::pitchMatrix( const gmtl::Matrix44f& matrix )
{
  mPitchMatrix = matrix;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::currentRotation( const gmtl::Matrix44f& matrix )
{
  mCurrentPosition = matrix * mCurrentPosition;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const double& Navigation::navigationSpeed() const
{
  return mNavigationSpeed;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::navigationSpeed( const double& speed )
{
mNavigationSpeed = speed;    
}    

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const double& Navigation::navigationDelta() const
{
  return mNavigationDelta; 
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::navigationDelta( const double& delta )
{
  mNavigationDelta = delta;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::rotationSpeed( const double& speed )
{
  mRotationSpeed = speed;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const double& Navigation::rotationSpeed() const
{
  return mRotationSpeed;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const double& Navigation::rotationDelta() const
{
  return mRotationDelta;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::rotationDelta( const double& delta )
{
  mRotationDelta = delta;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::frameRenderTime( const double& time )
{
  mFrameRenderTime = time;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const double& Navigation::frameRenderTime() const
{
  return mFrameRenderTime;
}

///////////////////////////////////////////////////////////////////////////////
//
// Expected frame rate.
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::setFrameRate( const double& fps )
{
  mFramesPerSecond = fps;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const double& Navigation::getFrameRate() const
{
  return mFramesPerSecond;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::allowPitch( const bool& value )
{      
  mAllowPitch = value;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::allowYaw( const bool& value )
{
  mAllowYaw = value;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::allowRoll( const bool& value )
{
  mAllowRoll = value;  
}

///////////////////////////////////////////////////////////////////////////////
//
// Reset parameters and variables for navigation to their default.
//
////////////////////////////////////////////////////////////////////////////////

void Navigation::reset()
{
  mCurrentPosition  = mHomePosition;  
  
  //mNavigationSpeed  = mInitialNavigationSpeed;
  //mRotationSpeed    = mInitialRotationSpeed;  
  
  //mNavigationDelta  = mInitialNavigationDelta;  
  //mRotationDelta    = mInitialRotationDelta;

  gmtl::identity( mPitchMatrix );
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::navigationMode( const Core::NavigationMode& mode )
{
  mNavigationMode = mode;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

const Core::NavigationMode& Navigation::navigationMode() const
{
  return mNavigationMode;
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::accelerate()
{
  if(( mNavigationSpeed + mNavigationDelta ) < mMaxNavigationSpeed )
  {
    mNavigationSpeed = mNavigationSpeed + mNavigationDelta;    
  }        
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::deaccelerate()
{
  if(( mNavigationSpeed - mNavigationDelta ) > 0.0 )
  {
    mNavigationSpeed = mNavigationSpeed - mNavigationDelta;
  }  
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::angulatAccelerate()
{
  if( ( mRotationSpeed + mRotationDelta ) < mMaxRotationSpeed )
  {
    mRotationSpeed = mRotationSpeed + mRotationDelta;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::angulatDeaccelerate()
{
  if( ( mRotationSpeed - mRotationDelta ) > 0.0 )
  {
    mRotationSpeed = mRotationSpeed - mRotationDelta;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::translateInZ( const double& value )
{
  mNavigationVel[2] =  -( mNavigationSpeed * value );      
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::translateInX( const double& value )
{
  mNavigationVel[0] =  -( mNavigationSpeed * value );      
}  

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::translateInY( const double& value )
{
  mNavigationVel[1] = 0.1 * -( mNavigationSpeed * value ) ;      
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::translateInDir( const gmtl::Vec3f& direction )
{
  mNavigationVel = (float) mNavigationSpeed * direction;
}

//////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::rotateInX( const double& value )
{
  if( mAllowPitch )
  {
    mRotationVel[0] = mRotationSpeed * value;        
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::rotateInY( const double& value )
{
  if( mAllowYaw )
  {
    mRotationVel[1] =   mRotationSpeed * value;        
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::rotateInZ( const double& value )
{
  if( mAllowRoll )
  {
    mRotationVel[2] =  -( mRotationSpeed * value );                
  }
}    

///////////////////////////////////////////////////////////////////////////////
//
// Calculate translation matrix.  
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::translate( const gmtl::Vec3f& vec, Core::Scope scope )
{
  gmtl::Matrix44f transMatrix = gmtl::makeTrans< gmtl::Matrix44f >( vec );

  if( scope == Core::GLOBAL )
  {
    gmtl::Matrix44f invMatrix;

    switch( mNavigationMode )
    {
  	  case Core::HELICOPTER:
      {
        gmtl::invertFull( invMatrix, mPitchMatrix );

        gmtl::preMult   ( mCurrentPosition, invMatrix    );
        gmtl::preMult   ( mCurrentPosition, transMatrix  );
        gmtl::preMult   ( mCurrentPosition, mPitchMatrix );
        break;
      }
	  case Core::FLIGHT:
      {
        gmtl::preMult( mCurrentPosition, transMatrix );
        break;
      }
	  case Core::TRACKBALL:
      {
        gmtl::preMult( mCurrentPosition, transMatrix );
        break;
      }
      case Core::OSSIMNAV:
      {
        gmtl::preMult( mCurrentPosition, transMatrix );
        break;
      }
      default:
      {
        std::cerr << "Error 3062328389: Navigation mode " <<  mNavigationMode 
                  << " not handled. " << std::endl;
        break;
      }
    };
  } 
  else 
  {
    gmtl::postMult( mCurrentPosition, transMatrix );
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// Calculate rotation matrix. 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::rotate( gmtl::Matrix44f& rotationMatrix, Core::Scope scope )
{
  slerp( rotationMatrix, 0.4f );

  gmtl::Vec3f tempVector1, tempVector2; tempVector1.set( 0.0, 0.0, 0.0 );

  if( mNavigationMode == Core::TRACKBALL || mNavigationMode == Core::OSSIMNAV )
  {
    gmtl::setTrans( tempVector2, mCurrentPosition );
    gmtl::setTrans( mCurrentPosition, tempVector1 );
  }

  if( scope == Core::GLOBAL && mNavigationMode != Core::OSSIMNAV )
  {  
    float p = ( gmtl::makeRot< gmtl::EulerAngleXYZf >( rotationMatrix ) )[ 0 ];
    
    gmtl::Matrix44f pitchMatrix, invPitchMatrix; 
    gmtl::setRot( pitchMatrix, gmtl::EulerAngleXYZf( p, 0.0, 0.0 ) );
    gmtl::invertFull( invPitchMatrix, mPitchMatrix );

    gmtl::preMult( mCurrentPosition, invPitchMatrix );
    gmtl::preMult( mCurrentPosition, rotationMatrix );
    gmtl::preMult( mCurrentPosition, mPitchMatrix );
    
    mPitchMatrix = mPitchMatrix * pitchMatrix;
  }
  else if( mNavigationMode == Core::OSSIMNAV )
  {
    gmtl::preMult( mCurrentPosition, rotationMatrix );
  }
  else 
  {
    gmtl::postMult( mCurrentPosition, rotationMatrix   );
  }
  
  if( mNavigationMode == Core::TRACKBALL || mNavigationMode == Core::OSSIMNAV )
  {
    gmtl::setTrans( mCurrentPosition, tempVector2 );  
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// Quaternion interpolation. 
//
///////////////////////////////////////////////////////////////////////////////

gmtl::Matrix44f& Navigation::slerp( gmtl::Matrix44f& inputMatrix, const float& amount )
{
  gmtl::Matrix44f transform, identityMatrix;
  gmtl::Quatf     sourceQuat, goalQuat, slerpQuat;

  // Create an identity quaternion to rotate from.
  gmtl::identity( identityMatrix );

  // Create the goal rotation quaternion ( the goal is the input matrix ).
  gmtl::set( goalQuat, inputMatrix );

  // If we don't have two identity matrices, then interpolate between them.
  if( identityMatrix != inputMatrix )
  {
    // Transform part way there
    gmtl::slerp( slerpQuat, amount, sourceQuat, goalQuat );

    // Create the transform matrix to use.
    gmtl::set( inputMatrix, slerpQuat );     
  }
  else
  {
    gmtl::identity( inputMatrix );
  }

  return inputMatrix;
}


///////////////////////////////////////////////////////////////////////////////
//
// Update. 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::update( const float& delta, Core::Scope scope )
{  
  static const float fps = 30.0;
  
  if( delta > 2.0 )
  {
    std::cerr << "Warning 2471119497w: Delta too big, returning. " << std::endl;
    return;
  }  
  
  float fpsFact = mFramesPerSecond * mFrameRenderTime;

  if( mUseRange )
  {
    double        currentSpeed;
    gmtl::Vec3f   currentPosition;

    gmtl::setTrans( currentPosition, mCurrentPosition );

    if( currentPosition[2] < mMinDistance )
    {
      mNavigationVel = gmtl::Vec3f( mMinNavigationSpeed, mMinNavigationSpeed, mMinNavigationSpeed ) ;
    }
    else if( currentPosition[2] > mMaxDistance )
    {
      mNavigationVel = gmtl::Vec3f( mMaxNavigationSpeed, mMaxNavigationSpeed, mMaxNavigationSpeed ) ;
    }
    else 
    {
      currentSpeed =  ( currentPosition[2] / ( mMaxDistance - mMinDistance ) ) * mMaxNavigationSpeed;
      mNavigationVel = gmtl::Vec3f( currentSpeed, currentSpeed, currentSpeed );
    }
  }

  mNavigationVel  = fpsFact * mNavigationVel;
  mRotationVel    = fpsFact * mRotationVel; 

  translate( mNavigationVel, scope );

  gmtl::EulerAngleXYZf euler( mRotationVel[ 0 ], mRotationVel[ 1 ], mRotationVel[ 2 ] );
  
  gmtl::Matrix44f rotationMatrix = gmtl::makeRot<gmtl::Matrix44f>( euler );

  rotate( rotationMatrix, scope );

  // Do we still need to do this? 
  mNavigationVel[1] = 0.0;
}


///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Navigation::pitch( const double& value )
{
  mRotationVel[0] = mRotationSpeed * value;
  mRotationVel[1] = 0.0;
  mRotationVel[2] = 0.0;
  
  // Roation matrix calculation.
  gmtl::EulerAngleXYZf euler( mRotationVel[ 0 ], mRotationVel[ 1 ], mRotationVel[ 2 ] );  
  gmtl::Matrix44f rotationMatrix = gmtl::makeRot< gmtl::Matrix44f >( euler );
  
  slerp( rotationMatrix, 0.4f );

  gmtl::preMult( mCurrentPosition, rotationMatrix );
}
