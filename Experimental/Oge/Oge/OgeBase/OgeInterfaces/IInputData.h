
#ifndef __I_INPUT_DATA_H__
#define __I_INPUT_DATA_H__

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      template< typename T >
      struct IInputData : public IUnknown
      {
        virtual T getData() const = 0;
      };
    }
  }
}

#endif // __I_INPUT_DATA_H__
