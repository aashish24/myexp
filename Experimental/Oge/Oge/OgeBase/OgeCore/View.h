
#ifndef __OGE_CORE_VIEW_H__
#define __OGE_CORE_VIEW_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IView.h"
#include "Oge/OgeBase/OgeInterfaces/IModel.h"

#include "Oge/OgeBase/OgeCore/Camera.h" 
#include "Oge/OgeBase/OgeCore/Referenced.h" 
#include "Oge/OgeBase/OgeCore/Pointer.h" 

#include <vector>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgModel;
      struct ICamera;
    }
  }
}

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    { 
      struct OGE_EXPORT View : public Oge::OgeBase::OgeInterfaces::IView, public Oge::OgeBase::OgeCore::Referenced
      {
        OGE_DELCARE_SMART_PTR( View ); 

        IMPLEMENT_IUNKNOWN_MEMBERS( View, Oge::OgeBase::OgeCore::Referenced ); 

        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;  
        typedef Oge::OgeBase::OgeInterfaces::ICamera    ICamera;
        typedef Oge::OgeBase::OgeInterfaces::IModel     IModel;

        typedef Oge::OgeBase::OgeCore::Camera           Camera;

        
                                                        View( IModel* model ); 
       
        virtual IUnknown*                               queryInterface( const unsigned long& iid );

        virtual void                                    update();

#if 0
        virtual void                                    setCamera( ICamera* camera );
        virtual ICamera*                                getCamera( const unsigned int& index = 0 );

        virtual void                                    addCamera( ICamera* camera );
#endif 

        virtual void                                    draw();
       

        protected: 
      
          virtual                                      ~View();    


        protected: 

          IModel::RefPtr                              _model;

          ICamera::RefPtr                             _masterCamera;
          std::vector< ICamera::RefPtr >              _cameraLists;
      };
    } 
  } 
} 

#endif // __OGE_CORE_VIEW_H__
