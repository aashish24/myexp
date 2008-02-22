
#ifndef __OSG_CORE_OSG_VIEWER_H__
#define __OSG_CORE_OSG_VIEWER_H__

#include "OgeOsg/Export.h"

#include "OgeBase/OgeInterfaces/IView.h"
#include "OgeBase/OgeInterfaces/IViewer.h"
#include "OgeBase/OgeInterfaces/IInputDevice.h"
#include "OgeBase/OgeInterfaces/IInterfaceContext.h"

#include "OgeBase/OgeCore/Referenced.h"
#include "OgeBase/OgeCore/BaseViewer.h"

#include "OgeOsg/OsgCore/OsgView.h"
#include "OgeOsg/OsgCore/OsgModel.h"
#include "OgeOsg/OsgCore/OsgCamera.h"

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
      class OGE_OSG_EXPORT OsgViewer :                 
        public Oge::OgeBase::OgeInterfaces::IViewer,
        public osgViewer::Viewer,
        public Oge::OgeBase::OgeCore::BaseViewer
      {

        public : 

          OGE_DELCARE_SMART_PTR( OsgViewer );     

          IMPLEMENT_IUNKNOWN_MEMBERS( OsgViewer, Oge::OgeBase::OgeCore::BaseViewer );

          typedef OgeBase::OgeInterfaces::IUnknown      IUnknown;
          typedef OgeBase::OgeInterfaces::IView         IView;
          typedef OgeBase::OgeInterfaces::IViewer       IViewer;
          typedef OgeBase::OgeInterfaces::ICamera       ICamera;

          typedef OgeBase::OgeCore::BaseViewer          BaseViewer;
          typedef OgeOsg::OsgCore::OsgModel             OsgModel;    
          
          OsgViewer( int argc = 0, char** argv = 0, Mode vMode = REGULAR );        
          
          virtual IUnknown*                             queryInterface( const unsigned long& iid );
          
          virtual void                                  readConfig( const std::string& config );
          
          virtual void                                  init();                
          
          virtual void                                  update();        
          
          virtual void                                  draw();
          
          virtual int                                   run(); 
          
          void                                          setSceneData( osg::Node* sceneRoot );

          virtual IView*                                getView() const;

          virtual ICamera*                              getActiveCamera() const;          
      
      protected: 
      
          virtual                                      ~OsgViewer();    


        protected: 

          IViewer::Mode                                 _mode;

          OsgModel::RefPtr                              _osgModel;
          OsgView::RefPtr                               _osgView;

          OsgCamera::RefPtr                             _osgCamera;
      };
    }
  } 
} 

#endif // __OSG_CORE_OSG_VIEWER_H__
