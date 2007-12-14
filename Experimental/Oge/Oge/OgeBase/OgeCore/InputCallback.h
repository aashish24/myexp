
#ifndef __INPUT_CALLBACK_H__
#define __INPUT_CALLBACK_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IInputCallback.h"
#include "Oge/OgeBase/OgeInterfaces/IInput.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

namespace Oge 
{
  namespace OgeBase 
  {  
    namespace OgeCore
    {
      struct OGE_EXPORT InputCallback : 
        public OgeBase::OgeInterfaces::IInputCallback, 
        public OgeBase::OgeCore::Referenced
      {
        
        OGE_DELCARE_SMART_PTR( InputCallback );

        IMPLEMENT_IUNKNOWN_MEMBERS( InputCallback, OgeBase::OgeCore::Referenced );      
        
        typedef OgeBase::OgeInterfaces::IUnknown  IUnknown;
        typedef OgeBase::OgeInterfaces::IInput    IInput;
     
        virtual void                              operator()( IInput* input ) = 0;

        IUnknown*                                 queryInterface( const unsigned long& iid );


        protected: 
          
          virtual ~InputCallback(){};
      };
    }
  }
}

#endif // __INPUT_CALLBACK_H__
