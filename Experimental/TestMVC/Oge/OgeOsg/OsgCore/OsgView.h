
#ifndef __OSG_VIEWER_OSG_VIEW_H__
#define __OSG_VIEWER_OSG_VIEW_H__

#include "Oge/OgeBase/OgeInterfaces/IOsgView.h"

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

        typedef osgUtil::SceneView                      SceneView;  

        OsgView( IOsgModel* model ); 
       ~OsgView(); 

        virtual IUnknown*             queryInterface( const unsigned long& iid );

        virtual SceneView*            sceneView();  

        virtual void                  update();

        virtual void                  draw();
        

        protected: 

          IOsgModel*                  _model;

          SceneView*                  _sceneView;
      };
    } // namespace OsgCore
  } // namespace OgeOsg
} // namespace Oge

#endif // __OSG_VIEWER_OSG_VIEW_H__
