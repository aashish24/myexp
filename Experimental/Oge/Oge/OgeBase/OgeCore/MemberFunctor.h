

#ifndef __OGE_CORE_MEMBER_FUNCTOR_H__
#define __OGE_CORE_MEMBER_FUNCTOR_H__

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeCore
    {
      template< typename T >
      struct MemberFunctor : public Oge::OgeBase::OgeInterfaces::IFunctor, public Referenced
      {
        typedef void ( T::*FPtr )( );

        MemberFunctor( T* obj, FPtr fPtr ) : 
          _obj( obj ), 
          _fPtr( fPtr )
        {
        }
          
        virtual void operator()( )
        {
          ( _obj->*_fPtr )();
        }

        IUnknown* queryInterface( const unsigned long& iid )
        {
          return 0x00;
        }

        T*    _obj;
        FPtr  _fPtr;

        protected:
          
          virtual ~MemberFunctor()
          {
          }
      };
    }
  }
}

#endif // __OGE_CORE_MEMBER_FUNCTOR_H__
