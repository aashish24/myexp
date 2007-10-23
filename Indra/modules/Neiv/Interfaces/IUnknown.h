
#ifndef __NEIV_INTERFCES_IUNKNOWN_H__
#define __NEIV_INTERFCES_IUNKNOWN_H__

#include "Neiv/Pointer/Pointer.h"

namespace Neiv
{ 
  namespace Interface
  {
    struct IUnknown
    {
      NEIV_DELCARE_SMART_PTR( IUnknown );

      enum{ IID = 1075271105 };

      virtual IUnknown* queryInterface( unsigned long iid ) = 0;

      virtual void      ref() = 0;

      virtual void      undef( bool allowDeletion = true ) = 0;
    };
  } // namespace Interface
} // namespace Neiv

#define NEIV_DECLARE_IUNKNOWN_MEMBERS \
  virtual Neiv::Interface::IUnknown* queryInterface( unsigned long iid ); \
  virtual void                       ref();                               \
  virtual void                       unref();                           

#define NEIV_IMPLEMENT_IUNKNOWN_MEMBERS( className, baseClass ) \
  void className::ref(){ baseClass::ref(); }                    \
  void className::unref( bool allowDeletion ){ baseClass::unref( allowDeletion ); }


#endif // __NEIV_INTERFCES_IUNKNOWN_H__