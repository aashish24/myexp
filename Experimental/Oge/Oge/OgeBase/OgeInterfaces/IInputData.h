
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
                  OGE_DELCARE_SMART_PTR( IInputData );

        virtual T getData() const = 0;
      };
    }
  }
}

#endif // __I_INPUT_DATA_H__
