
#ifndef __OGE_INTERFACES_I_UNKNOWN_H__
#define __OGE_INTERFACES_I_UNKNOWN_H__

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IUnknown
      {
        enum { IID = 3197031617 };
        
        virtual IUnknown* queryInterface( const unsigned long& iid ) = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_UNKNOWN_H__
