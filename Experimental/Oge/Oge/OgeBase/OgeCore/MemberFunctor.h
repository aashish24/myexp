

#ifndef __OGE_CORE_MEMBER_FUNCTOR_H__
#define __OGE_CORE_MEMBER_FUNCTOR_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeCore
    { 
      template< typename T >
      struct OGE_EXPORT MemberFunctor : 
        public Oge::OgeBase::OgeInterfaces::IFunctor, 
        public Oge::OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( MemberFunctor );
        
        // Not sure why this does not work. 
        //IMPLEMENT_IUNKNOWN_MEMBERS( MemberFunctor, Oge::OgeBase::OgeCore::Referenced );

        typedef void                ( T::*FPtr )( );

                                    MemberFunctor( T* obj, FPtr fPtr );
        

        virtual void                operator()( );


        virtual void                ref(){ Oge::OgeBase::OgeCore::Referenced::ref() };
        virtual void                unref(){ Oge::OgeBase::OgeCore::Referenced::unref() };
        virtual void                unrefDoNotDelete(){ Oge::OgeBase::OgeCore::Referenced::unrefDoNotDelete() };

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
