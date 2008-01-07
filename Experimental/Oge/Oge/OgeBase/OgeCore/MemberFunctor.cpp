
#include "Oge/OgeBase/OgeCore/MemberFunctor.h"

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeCore
    {   
      template< typename T >
      MemberFunctor< T >::MemberFunctor( T* obj, FPtr fPtr ) : 
        _obj( obj ), 
        _fPtr( fPtr )
      {
      }
      

      template< typename T >        
      MemberFunctor< T >::~MemberFunctor()
      {
      }


      template< typename T >
      void MemberFunctor< T >::operator()( )
      {
        ( _obj->*_fPtr )();
      }


      template< typename T >
      OgeBase::OgeInterfaces::IUnknown* MemberFunctor< T >::queryInterface( const unsigned long& iid )
      {
        switch( iid )
	{
		case OgeBase::OgeInterfaces::IUnknown::IID:
        	case OgeBase::OgeInterfaces::IFunctor::IID: 
        	{
          	return static_cast< OgeBase::OgeInterfaces::IFunctor* >( this );
        	}
        	default: 
        	{
          	return 0x00;
        	}
	};
      }
    }
  }
}

