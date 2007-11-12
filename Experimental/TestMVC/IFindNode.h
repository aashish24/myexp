
#ifndef __OGE_OGE_BASE_OGE_INTERFACES_FIND_NODE_H__
#define __OGE_OGE_BASE_OGE_INTERFACES_FIND_NODE_H__

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      enum{ IID = 2654034121 };

      template< typename T > 
      struct IFindNode : public IUnknown
      {
        virtual T* findNode( const std::string& id ) = 0;
      };
    }
  }
}

#endif // __OGE_OGE_BASE_OGE_INTERFACES_FIND_NODE_H__
