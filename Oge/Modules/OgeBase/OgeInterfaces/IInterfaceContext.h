
#ifndef __OGE_INTERFACES_I_INTERFACE_CONTEXT_H__
#define __OGE_INTERFACES_I_INTERFACE_CONTEXT_H__

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IInterfaceContext : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInterfaceContext );
        
        enum                { IID = 4009246272 };

        virtual void        config() = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_INTERFACE_CONTEXT_H__
