
#ifndef __ALPHA_OSG_VIEW_H__
#define __ALPHA_OSG_VIEW_H__

#include "IOsgView.h"

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
      struct OsgView : public Oge::OgeBase::OgeInterfaces::IOsgView
      {
        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;  
        typedef Oge::OgeBase::OgeInterfaces::IOsgModel  IOsgModel;

        OsgView( IOsgModel* model ); 
       ~OsgView(); 

        virtual IUnknown*             queryInterface( unsigned long iid );

        virtual osgUtil::SceneView*   sceneView();  

        virtual void                  update();

        virtual void                  draw();
        

        protected: 

          IOsgModel*                  _model;

          osgUtil::SceneView*         _sceneView;
      };
    } // namespace OsgCore
  } // namespace OgeOsg
} // namespace Oge

#endif // __ALPHA_OSG_VIEW_H__
