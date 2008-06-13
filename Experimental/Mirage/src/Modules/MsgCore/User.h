#ifndef __USER_H__
#define __USER_H__

namespace glCore
{
	class User
	{
		public:
			User() :
				mPoints( 0.0 ), 
				mRank( 1 ), 
				mTime( 0.0 ), 
				mLock( false )
			{}

			~User()
			{}

			void setPoints( long int points )
			{
				mPoints = points;
			}

			double getPoints()
			{
				return mPoints;
			}

			void addPoints( long int points )
			{
				mPoints = mPoints + points;
			}
			
			void setTime( const double& time )
			{
				if( !mLock )
				{
					mTime = time;
					mLock = true;
				}	
			}

			double getTime()
			{
				return mTime;
			}

			void reset()
			{
				mPoints = 0.0;
				mRank   = 1;
				mTime   = 0.0;
				mLock   = false;
			}

		private:
			// How many points user has at a given time.  
			long int mPoints;			
			
			// User has a car. 
			int mCarColor;

			// Rank of the user. 
			int mRank;

			// Time user took to finish. 
			double mTime;

			// Lock the finish time. 
			bool mLock;
	};
}

#endif // __USER_H__