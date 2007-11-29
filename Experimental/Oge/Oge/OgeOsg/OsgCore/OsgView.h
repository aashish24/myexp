
#ifndef __OSG_VIEWER_OSG_VIEW_H__
#define __OSG_VIEWER_OSG_VIEW_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IOsgView.h"

#include "Oge/OgeBase/OgeCore/Referenced.h" 

namespace osgUtil
{
  class SceneView;
}

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgModel;
    }
  }
}

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    { 
      struct OGE_EXPORT OsgView : public Oge::OgeBase::OgeInterfaces::IOsgView, public OgeBase::OgeCore::Referenced
      {
        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;  
        typedef Oge::OgeBase::OgeInterfaces::IOsgModel  IOsgModel;

        typedef osgUtil::SceneView                      SceneView;  

        OsgView( IOsgModel* model ); 
       
        virtual IUnknown*             queryInterface( const unsigned long& iid );

        virtual SceneView*            sceneView();  
        
        virtual IOsgModel*            getModel();
        virtual void                  setModel( IOsgModel* model );

        virtual void                  update();

        virtual void                  draw();
       

        protected: 
      
          virtual                     ~OsgView();    

        protected: 

          IOsgModel*                  _model;

          SceneView*                  _sceneView;
      };
    } // namespace OsgCore
  } // namespace OgeOsg
} // namespace Oge

#endif // __OSG_VIEWER_OSG_VIEW_H__
