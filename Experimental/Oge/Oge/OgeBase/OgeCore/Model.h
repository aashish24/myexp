
#ifndef __OGE_CORE_MODEL_H__
#define __OGE_CORE_MODEL_H__

#include "Oge/OgeBase/OgeInterfaces/IModel.h"
#include "Oge/OgeBase/OgeInterfaces/IView.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      class Model : 
        public OgeBase::OgeInterfaces::IModel,
        public OgeBase::OgeCore::Referenced
      {
        public: 
          
          OGE_DELCARE_SMART_PTR( Model );

          IMPLEMENT_IUNKNOWN_MEMBERS( Model, OgeBase::OgeCore::Referenced );

          typedef OgeBase::OgeInterfaces::IView                 IView;
          typedef OgeBase::OgeInterfaces::IUnknown              IUnknown;

          typedef std::vector< IView::RefPtr >::const_iterator  ViewsItr;

          Model();
          
          virtual IUnknown*                                     queryInterface( const unsigned long& iid ) = 0;

          virtual void                                          build();

          virtual void                                          attach( IView* view );

          virtual void                                          update();


        protected: 
          
          virtual ~Model();


        protected: 
                    
          std::vector< IView::RefPtr >                          _views;                 

      };
    }
  }
}

#endif // __OGE_CORE_MODEL_H__
