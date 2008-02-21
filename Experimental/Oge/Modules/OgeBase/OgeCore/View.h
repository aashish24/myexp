
#ifndef __OGE_CORE_VIEW_H__
#define __OGE_CORE_VIEW_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IView.h"
#include "Oge/OgeBase/OgeInterfaces/IModel.h"

#include "Oge/OgeBase/OgeCore/Referenced.h" 

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    { 
      struct OGE_EXPORT View : 
        public OgeBase::OgeInterfaces::IView, 
        public OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( View ); 

        IMPLEMENT_IUNKNOWN_MEMBERS( View, OgeBase::OgeCore::Referenced ); 

        typedef OgeBase::OgeInterfaces::IUnknown            IUnknown;          
        typedef OgeBase::OgeInterfaces::IModel              IModel;
        
        View( IModel* model ); 
       
        virtual IUnknown*               queryInterface( const unsigned long& iid );

        virtual void                    update();

        virtual void                    draw();
       

        protected: 
      
          virtual ~View();    


        protected: 

          IModel::RefPtr                _model;
      };
    }
  }
}

#endif // __OGE_CORE_VIEW_H__
