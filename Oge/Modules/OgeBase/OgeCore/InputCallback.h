
#ifndef __OGE_CORE_INPUT_CALLBACK_H__
#define __OGE_CORE_INPUT_CALLBACK_H__

#include "OgeBase/Export.h"

#include "OgeBase/OgeInterfaces/IInputCallback.h"
#include "OgeBase/OgeInterfaces/IInput.h"

#include "OgeBase/OgeCore/Referenced.h"

namespace Oge 
{
  namespace OgeBase 
  {  
    namespace OgeCore
    {
      struct OGE_BASE_EXPORT InputCallback : 
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

#endif // __OGE_CORE_INPUT_CALLBACK_H__
