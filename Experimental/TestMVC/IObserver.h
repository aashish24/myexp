
#ifndef __I_OBSERVER_H__
#define __I_OBSERVER_H__

#include "IUnknown.h"

struct IObserver : public IUnknown
{
  enum { IID = 1 };

  virtual void update() = 0;
};

#endif // __I_OBSERVER_H__