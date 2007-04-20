
///////////////////////////////////////////////////////////////////////////////
//
// Class to provide core navigation functionalities. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_NAVIGATION_H__
#define __CORE_NAVIGATION_H__

#include <iostream>
#include <string>

#include "gmtl/Matrix.h"
#include "gmtl/Vec.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Generate.h"
#include "gmtl/Math.h"

#include "Core/Types.h"

#include "Export.h"

namespace Core
{
	class CORE_EXPORT Navigation
	{
		public:

      Navigation();      
     ~Navigation();            

			const gmtl::Matrix44f&                        currentPosition() const;			
			void                                          currentPosition( const gmtl::Matrix44f& position );

      const gmtl::Matrix44f&                        pitchMatrix() const;
			void                                          pitchMatrix( const gmtl::Matrix44f& matrix );

			void                                          currentRotation( const gmtl::Matrix44f& matrix );
			
			const double&                                 navigationSpeed() const;
			void                                          navigationSpeed( const double& speed );

			const double&                                 navigationDelta() const;
			void                                          navigationDelta( const double& delta );

      const double&                                 rotationSpeed() const;
			void                                          rotationSpeed( const double& speed );


			const double&                                 rotationDelta() const;
			void                                          rotationDelta( const double& delta );

      const double&                                 frameRenderTime() const;
			void                                          frameRenderTime( const double& time );

      const double&                                 getFrameRate() const;			
			void                                          setFrameRate( const double& fps );

			void                                          allowPitch( const bool& value );
			void                                          allowYaw( const bool& value );
			void                                          allowRoll( const bool& value );
			
			void                                          reset();

      const NavigationMode&                         navigationMode() const;      
			void                                          navigationMode( const NavigationMode& navMode );

			void                                          accelerate();
			void                                          deaccelerate();

			void                                          angulatAccelerate();
			void                                          angulatDeaccelerate();

			void                                          translateInZ( const double& value );
			void                                          translateInX( const double& value );
			void                                          translateInY( const double& value );

			void                                          translateInDir( const gmtl::Vec3f& direction );			

			void                                          rotateInX( const double& value );
			void                                          rotateInY( const double& value );
			void                                          rotateInZ( const double& value );

      void                                          pitch( const double& value );

			void                                          translate( const gmtl::Vec3f& vector, Scope = GLOBAL );
			void                                          rotate   ( gmtl::Matrix44f& matrix, Scope = GLOBAL );

      gmtl::Matrix44f&                              slerp( gmtl::Matrix44f& matrix, const float& value );

			void                                          update( const float& delta, Scope = GLOBAL );
		
		private:

			gmtl::Matrix44f                               mCurrentPosition;			
			gmtl::Matrix44f                               mHomePosition;
			
      gmtl::Matrix44f                               mPitchMatrix;
			gmtl::Quatf                                   mPitchQuat;

			gmtl::Vec3f		                                mNavigationVel;
			gmtl::Vec3f		                                mRotationVel;
					
			double			                                  mNavigationSpeed;
			double			                                  mRotationSpeed;
			double			                                  mNavigationDelta;
			double			                                  mRotationDelta;	

			double			                                  mFrameRenderTime;
			double			                                  mFramesPerSecond;

      double                                        mMinNavigationSpeed;
      double                                        mMaxNavigationSpeed;
      double                                        mMinRotationSpeed;
      double                                        mMaxRotationSpeed;

      double                                        mMinDistance;
      double                                        mMaxDistance;

      bool                                          mUseRange;

			bool                                          mAllowPitch;
      bool                                          mAllowYaw;
      bool                                          mAllowRoll;

			NavigationMode                                mNavigationMode;

  };
}

#endif // __CORE_NAVIGATION_H__

