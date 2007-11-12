
#ifndef __I_VIEW_H__
#define __I_VIEW_H__

#include "IObserver.h"

struct IView : public IObserver 
{
  enum { IID = 4 };

  virtual void draw() = 0;
};

#endif // __I_VIEW_H__