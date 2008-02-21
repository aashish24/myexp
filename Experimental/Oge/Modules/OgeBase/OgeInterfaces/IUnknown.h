
#ifndef __OGE_INTERFACES_I_UNKNOWN_H__
#define __OGE_INTERFACES_I_UNKNOWN_H__

#include "Oge/OgeBase/OgeCore/Pointer.h"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IUnknown
      {
        OGE_DELCARE_SMART_PTR( IUnknown );

        enum              { IID = 3197031617 };
        
        virtual IUnknown* queryInterface( const unsigned long& iid ) = 0;

        virtual void      ref() = 0; 

        virtual void      unref() = 0; 

        virtual void      unrefDoNotDelete() = 0;


        protected:
        
          virtual        ~IUnknown() {;}
      };
    } 
  } 
} 


#define DECLARE_IUNKNOWN_MEMBERS \
  virtual Oge::OgeBase::OgeInterfaces::IUnknown *   queryInterface ( const unsigned long& iid ); \
  virtual void                                      ref(); \
  virtual void                                      unref(); \
  virtual void                                      unrefDoNotDelete(); \


#define IMPLEMENT_IUNKNOWN_MEMBERS( class_name, base_class ) \
  void class_name::ref()    { base_class::ref(); } \
  void class_name::unref() { base_class::unref (); } \
  void class_name::unrefDoNotDelete() { base_class::unrefDoNotDelete(); }


#endif // __OGE_INTERFACES_I_UNKNOWN_H__
