
#ifndef __OSG_CORE_OSG_VIEWER_H__
#define __OSG_CORE_OSG_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IView.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"
#include "Oge/OgeBase/OgeInterfaces/IInterfaceContext.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/BaseViewer.h"

#include "Oge/OgeOsg/OsgCore/OsgView.h"
#include "Oge/OgeOsg/OsgCore/OsgModel.h"
#include "Oge/OgeOsg/OsgCore/OsgCamera.h"

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
        public Oge::OgeBase::OgeInterfaces::IViewer,
        public Oge::OgeBase::OgeCore::Referenced,
        public osgViewer::Viewer,
        public Oge::OgeBase::OgeCore::BaseViewer
      {

        public : 

          OGE_DELCARE_SMART_PTR( OsgViewer );     

          IMPLEMENT_IUNKNOWN_MEMBERS( OsgViewer, Oge::OgeBase::OgeCore::Referenced );

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
