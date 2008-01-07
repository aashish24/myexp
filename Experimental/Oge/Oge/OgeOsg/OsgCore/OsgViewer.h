
#ifndef __OSG_CORE_OSG_VIEWER_H__
#define __OSG_CORE_OSG_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IView.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"
#include "Oge/OgeBase/OgeInterfaces/IInterfaceContext.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

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
        public osgViewer::Viewer
      {

        public : 

          OGE_DELCARE_SMART_PTR( OsgViewer );     

          IMPLEMENT_IUNKNOWN_MEMBERS( OsgViewer, Oge::OgeBase::OgeCore::Referenced );

          typedef OgeBase::OgeInterfaces::IUnknown      IUnknown;
          typedef OgeBase::OgeInterfaces::IView         IView;
          typedef OgeBase::OgeInterfaces::IViewer       IViewer;
          typedef OgeBase::OgeInterfaces::IInputDevice  IInputDevice;
          typedef OgeBase::OgeInterfaces::IInterfaceContext  IInterfaceContext;
          typedef OgeBase::OgeInterfaces::ICamera       ICamera;

          typedef OgeOsg::OsgCore::OsgModel             OsgModel;    
          typedef std::map< const std::string, IInputDevice::RefPtr >   
                                                        InputDevices;
          typedef std::vector< IInterfaceContext::RefPtr >  OgeContexts;

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

          virtual void                                  addInputDevice( const std::string& deviceName, IInputDevice* inputDevice );

          virtual IInputDevice*                         getInputDevice( const std::string& deviceName ) const;

          virtual void                                  addInterfaceContext( IInterfaceContext* context );

          virtual IInterfaceContext*                    getInterfaceContext( const unsigned int& index ) const;        

      
      protected: 
      
          virtual                                      ~OsgViewer();    


        protected: 

          IViewer::Mode                                 _mode;

          OsgModel::RefPtr                              _osgModel;
          OsgView::RefPtr                               _osgView;

          OsgCamera::RefPtr                             _osgCamera;

          InputDevices                                  _inputDevices;
          OgeContexts                             _interfaceContexts;


      };
    }
  } 
} 

#endif // __OSG_CORE_OSG_VIEWER_H__
