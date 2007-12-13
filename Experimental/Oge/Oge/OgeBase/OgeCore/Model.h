
#ifndef __MODEL_H__
#define __MODEL_H__

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

          typedef OgeBase::OgeInterfaces::IView IView;

                                                Model();
          
          virtual void                          build();

          virtual void                          attach( IView* view );

          virtual void                          update();


        protected: 
        
                                                ~Model();


        protected: 
                    
          std::vector< IView::RefPtr >          _views;                 

      };
    }
  }
}

#endif // __MODEL_H__