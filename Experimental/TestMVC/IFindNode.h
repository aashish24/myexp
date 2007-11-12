
#ifndef __OGE_OGE_BASE_OGE_INTERFACES_FIND_NODE_H__
#define __OGE_OGE_BASE_OGE_INTERFACES_FIND_NODE_H__

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      template< typename T > 
      struct IFindNode : public IUnknown
      {
        T* findNode( const std::string& id ) = 0;
      };
    }
  }
}

#endif // __OGE_OGE_BASE_OGE_INTERFACES_FIND_NODE_H__
