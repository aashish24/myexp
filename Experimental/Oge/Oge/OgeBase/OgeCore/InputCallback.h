
#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IInput.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

namespace Oge 
{
  namespace OgeBase 
  {  
    namespace OgeCore
    {
      struct OGE_EXPORT InputCallback : 
        public OgeBase::OgeInterfaces::IUnknown, 
        public OgeBase::OgeCore::Referenced
      {
        
        OGE_DELCARE_SMART_PTR( InputCallback );
        
        typedef OgeBase::OgeInterfaces::IUnknown  IUnknown;
        typedef OgeBase::OgeInterfaces::IInput    IInput;

        virtual void                              ref();

        virtual void                              unref();

        virtual void                              unrefDoNotDelete();

        virtual void                              operator()( IInput* input ) = 0;

        IUnknown*                                 queryInterface( const unsigned long& iid );


        protected: 
          
          virtual ~InputCallback(){};
      };

      void InputCallback::ref()
      {
        OgeBase::OgeCore::Referenced::ref();
      }


      void InputCallback::unref()
      {
        OgeBase::OgeCore::Referenced::unref();
      }


      void InputCallback::unrefDoNotDelete()
      {
        OgeBase::OgeCore::Referenced::unrefDoNotDelete();
      }

       
      InputCallback::IUnknown* InputCallback::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }
    }
  }
}
