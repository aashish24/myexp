#ifndef __TIMER_H__
#define __TIMER_H__

#include "Msg/MsgCore/Referenced.h"

#include <time.h>

namespace Msg
{ 
  namespace MsgUtil
  {
    class Timer : public Msg::MsgCore::Referenced
	  {
		  public:

			  void tick();

			  void reset() ;

			  double timeInSecs();

			  double timeInMins();
  		
		  private:

			  clock_t _clockT;
	  };


	  void Timer::tick()
	  {
		  _clockT = clock();
	  }


	  void Timer::reset()
	  {
		  tick();
	  }


	  double Timer::timeInSecs()
	  {
		  return ( ( clock() - _clockT )/ CLOCKS_PER_SEC );
	  }


	  double Timer::timeInMins()
	  {
		  return ( timeInSecs() / 60.0 );
	  }
  }

#endif // __TIMER_H__
