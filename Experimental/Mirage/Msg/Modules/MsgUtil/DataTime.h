#ifndef __TIMER_H__
#define __TIMER_H__

#include<time.h>

namespace glUtil
{
	class Timer
	{
		public:
			void tick();
			void reset() ;
			double getTimeInSecs();
			double getTimeInMins();
		
		private:
			clock_t mClockT;
	};

	void Timer::tick()
	{
		mClockT = clock();
	}

	void Timer::reset()
	{
		tick();
	}

	double Timer::getTimeInSecs()
	{
		return ( ( clock() - mClockT )/ CLOCKS_PER_SEC );
	}

	double Timer::getTimeInMins()
	{
		return ( getTimeInSecs() / 60.0 );
	}
}

#endif // __TIMER_H__
