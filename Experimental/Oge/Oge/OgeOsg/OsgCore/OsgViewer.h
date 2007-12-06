
#ifndef __OSG_CORE_OSG_VIEWER_H__
#define __OSG_CORE_OSG_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IView.h"

#include "Oge/OgeBase/OgeCore/Viewer.h" 
#include "Oge/OgeBase/OgeCore/Camera.h" 

#include "Oge/OgeOsg/OsgCore/OsgView.h"
#include "Oge/OgeOsg/OsgCore/OsgModel.h"

#include "osgViewer/Viewer"
#include "osg/Node"
#include "osg/Group"
#include "osg/MatrixTransform"

#include <vector>

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
      struct ICamera;
      struct IView;
    }
  }
}

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    { 
      class OGE_EXPORT OsgViewer :                 
        public Oge::OgeBase::OgeCore::Viewer, 
        public osgViewer::Viewer
      {

        public : 

          OGE_DELCARE_SMART_PTR( OsgViewer );     

          IMPLEMENT_IUNKNOWN_MEMBERS( OsgViewer, Oge::OgeBase::OgeCore::Viewer );

          typedef OgeBase::OgeInterfaces::IUnknown      IUnknown;
          typedef OgeBase::OgeInterfaces::IView         IView;

          typedef OgeOsg::OsgCore::OsgModel             OsgModel;

                                                        OsgViewer( ViewerMode vMode = REGULAR ); 
       
          virtual IUnknown*                             queryInterface( const unsigned long& iid );

          virtual void                                  init();                

          virtual void                                  update();
        
          virtual void                                  draw();

          virtual int                                   run();  

          void                                          setSceneData( osg::Node* sceneRoot );


        protected: 
      
          virtual                                      ~OsgViewer();    


        protected: 

          OsgModel::RefPtr                              _osgModel;
          OsgView::RefPtr                               _osgView;
      };
    }
  } 
} 

#endif // __OSG_CORE_OSG_VIEWER_H__
