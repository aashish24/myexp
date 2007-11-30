

#ifndef __OGE_CORE_MEMBER_FUNCTOR_H__
#define __OGE_CORE_MEMBER_FUNCTOR_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/Pointer.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeCore
    { 
      template< typename T >
      struct OGE_EXPORT MemberFunctor : public Oge::OgeBase::OgeInterfaces::IFunctor, public Referenced
      {
        typedef void                ( T::*FPtr )( );

                                    OGE_DELCARE_SMART_PTR( MemberFunctor );


                                    MemberFunctor( T* obj, FPtr fPtr );
        

        virtual void                operator()( );


        OgeInterfaces::IUnknown*    queryInterface( const unsigned long& iid );


        T*                          _obj;
        FPtr                        _fPtr;

        protected:
          
          virtual                  ~MemberFunctor();
      };
    }
  }
}

#endif // __OGE_CORE_MEMBER_FUNCTOR_H__
