
#ifndef __OGE_CORE_MEMBER_FUNCTOR_H__
#define __OGE_CORE_MEMBER_FUNCTOR_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeInterfaces
    {
      struct IUnknown;
    }

    namespace OgeCore
    { 
      template< typename T >
      struct OGE_EXPORT MemberFunctor : 
        public OgeBase::OgeInterfaces::IFunctor, 
        public OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( MemberFunctor );

        typedef void                        ( T::*FPtr )( );

        MemberFunctor( T* obj, FPtr fPtr );        

        virtual void                        operator()( );

        virtual void                        ref(){ OgeBase::OgeCore::Referenced::ref() };
        virtual void                        unref(){ OgeBase::OgeCore::Referenced::unref() };
        virtual void                        unrefDoNotDelete(){ OgeBase::OgeCore::Referenced::unrefDoNotDelete() };

        OgeBase::OgeInterfaces::IUnknown*   queryInterface( const unsigned long& iid );
      

        protected: 

          T*                                _obj;
          FPtr                              _fPtr;

      
        protected:
          
          virtual ~MemberFunctor();
      };
    }
  }
}

#endif // __OGE_CORE_MEMBER_FUNCTOR_H__
