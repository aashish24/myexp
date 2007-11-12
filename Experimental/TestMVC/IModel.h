

#ifndef __I_MODEL_H__
#define __I_MODEL_H__

struct IObserver;

struct IModel : public IUnknown
{
  enum { IID = 2 };

  virtual void attach( IObserver* observer ) = 0;
  
  virtual void update() = 0;
};

#endif // __I_MODEL_H__