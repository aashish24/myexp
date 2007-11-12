
#ifndef __I_UNKNOWN_H__
#define __I_UNKNOWN_H__

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IUnknown
      {
        enum { IID = 3197031617 };
        
        virtual IUnknown* queryInterface( unsigned long iid ) = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_UNKNOWN_H__
