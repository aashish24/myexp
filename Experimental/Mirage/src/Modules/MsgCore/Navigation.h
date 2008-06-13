
#ifndef __MSG_CORE_NAVIGATION_H__
#define __MSG_CORE_NAVIGATION_H__

#include <glMath/Vector"

using namespace glMath;

namespace glCore
{
	class Navigation
	{
		public:
			// Define navigation modes. 
			enum NavigationMode
			{
				TRACKBALL = 0,
				BIRDEYE	  = 1, 
				DRIVE	  = 2
			};

			// Ctor/Dtor.
			Navigation() :
				mTransVel( 0.0, 0.0, 0.0 ), 
				mTransSpd( 1.0 ), 
				mRotVel( 0.0, 0.0, 0.0, 0.0 ),  
				mRotSpd( 1.0 ), 
				mNavMode( DRIVE ), 
				mAccn( 0.1 ), 
				mMaxTransSpd( 10.0 ), 
				mMinTransSpd( 1.0 )
			{;}

			~Navigation()
			{;}
			
			void  setCurrPos( Vec3f pos );
			Vec3f getCurrPos();

			void  setCurrRot( Vec4f rot );
			Vec4f getCurRot();

			void setCurrTransVel( Vec3f );
			Vec3f getCurrTransVel();

			void setCurrRotVel( Vec4f );
			Vec4f getCurrRotVel();

			void  setNavSpd( float navSpeed );
			float getNavSpd();

			void  setRotSpd( float rotSpeed );
			float getRotSpd();

			void setNavMode( NavigationMode mode );
			NavigationMode getNavMode();

			void setMinMax( float minX, float minY, float maxX, float maxY );
			void setMinMaxSpd( float min, float max );
			void getMinMaxSpd( float& min, float& max );

			void  setAcceleration( float accn );
			float getAcceleration( float accn );

			void accelerate();
			void deaccelerate();

			void translate( Vec3f transVec );
			void rotate( Vec4f rotVec );

			void update();
		
		private:
			Vec3f mCurrPos;
			Vec4f mCurrRot;
			Vec3f mTransVel;
			float mTransSpd;
			Vec4f mRotVel;
			float mRotSpd;
			float mMaxTransSpd;
			float mMinTransSpd;
			float mAccn;

			float mMinX;
			float mMinY;
			float mMaxX;
			float mMaxY;

			NavigationMode mNavMode;
	};

	inline void Navigation::setCurrPos( Vec3f pos )
	{
		mCurrPos = pos;
	}

	inline Vec3f Navigation::getCurrPos()
	{
		return mCurrPos;
	}

	inline void Navigation::setCurrRot( Vec4f rot )
	{
		mCurrRot = rot;
	}

	inline Vec4f Navigation::getCurRot()
	{
		return mCurrRot;
	}

	inline void Navigation::setCurrTransVel( Vec3f transVel )
	{
		mTransVel = transVel;
	}

	inline Vec3f Navigation::getCurrTransVel()
	{
		return mTransVel;
	}

	inline void Navigation::setCurrRotVel( Vec4f rotVel )
	{
		mRotVel = rotVel;
	}

	inline Vec4f Navigation::getCurrRotVel()
	{
		return mRotVel;
	}

	inline void Navigation::setNavSpd( float navSpd )
	{
		mTransSpd = navSpd;
	}

	inline float Navigation::getNavSpd()
	{
		return mTransSpd;
	}

	inline void Navigation::setRotSpd( float rotSpd )
	{
		mRotSpd = rotSpd;
	}

	inline float Navigation::getRotSpd()
	{
		return mRotSpd;
	}

	inline void Navigation::setNavMode( Navigation::NavigationMode mode )
	{
		mNavMode = mode;
	}
	
	inline Navigation::NavigationMode Navigation::getNavMode()
	{
		return mNavMode;
	}

	inline void Navigation::setMinMax( float minX, float minY, float maxX, float maxY )
	{
		mMinX = minX;
		mMinY = minY;
		mMaxX = maxX;
		mMaxY = maxY;
	}

	inline void Navigation::setMinMaxSpd( float min, float max )
	{
		mMaxTransSpd = max;
		mMinTransSpd = min;
	}

	inline void Navigation::getMinMaxSpd( float& min, float& max )
	{
		max = mMaxTransSpd;
		min = mMinTransSpd;
	}

	inline void Navigation::setAcceleration( float accn )
	{
		mAccn = accn;
	}

	inline float Navigation::getAcceleration( float accn )
	{
		return mAccn;
	}

	inline void Navigation::accelerate()
	{
		mTransSpd = mTransSpd + mAccn;
		if( mTransSpd > mMaxTransSpd )
		{
			mTransSpd = mMaxTransSpd;	
		}
	}

	inline void Navigation::deaccelerate()
	{
		mTransSpd = mTransSpd - mAccn;
		if( mTransSpd < mMinTransSpd )
		{
			mTransSpd = mMinTransSpd;	
		}
	}	

	inline void Navigation::translate( Vec3f transVec )
	{
		mTransVel = transVec;
		mCurrPos = mTransVel * mTransSpd + mCurrPos;	

		// Try to make it move at the center line. 
		// It has some artifacts. 
		if( mTransVel[0] == 0 )
		{
			int diff = (int) mCurrPos[0] % 30;
			mCurrPos[0] = (int ) mCurrPos[0] - diff;
			if( diff >= 15 )
			{				
				if( ( (int)mCurrPos[0] % 60 ) == 0 )
				{
					mCurrPos[0] = mCurrPos[0] + 30;
				}
			}
			else
			{
				if( ( (int)mCurrPos[0] % 60 ) == 0 )
				{
					mCurrPos[0] = mCurrPos[0] - 30;
				}
			}
		}
		else if( mTransVel[1] == 0 )
		{
			int diff = (int) mCurrPos[1] % 30;
			mCurrPos[1] = (int ) mCurrPos[1] - diff;
			if( diff >= 15 )
			{				
				if( ( (int)mCurrPos[1] % 60 ) == 0 )
				{
					mCurrPos[1] = mCurrPos[1] + 30;
				}
			}
			else
			{
				if( ( (int)mCurrPos[1] % 60 ) == 0 )
				{
					mCurrPos[1] = mCurrPos[1] - 30;
				}
			}
		}

		if( mCurrPos[0] < mMinX )
		{	
			mCurrPos[0] = mMinX;
		}

		if( mCurrPos[1] < mMinY )
		{	
			mCurrPos[1] = mMinY;
		}

		if( mCurrPos[0] > mMaxX )
		{	
			mCurrPos[0] = mMaxX;
		}

		if( mCurrPos[1] > mMaxY )
		{	
			mCurrPos[1] = mMaxY;
		}
	}	

	inline void Navigation::rotate( Vec4f rotVec )
	{
		mRotVel = rotVec;
		mCurrRot = mRotVel;
	}

	inline void Navigation::update()
	{
		translate( mTransVel );
		rotate( mRotVel );
	}
}

#endif /// __MSG_CORE_NAVIGATION_H__
