
#ifndef __OGE_INTERFACES_I_FIND_NODE_H__
#define __OGE_INTERFACES_I_FIND_NODE_H__

#include <string>

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
        enum { IID = 4176415812 };

        virtual T* findNode( const std::string& id ) = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_FIND_NODE_H__
