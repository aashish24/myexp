
#ifndef __I_UNKNOWN_H__
#define __I_UNKNOWN_H__

struct IUnknown
{
  enum { IID = 0 };
  
  virtual IUnknown* queryInterface( unsigned long iid ) = 0;
};

#endif // __I_UNKNOWN_H__