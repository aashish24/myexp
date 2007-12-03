
#ifndef __OSG_VIEWER_VIEWER_H__
#define __OSG_VIEWER_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IFindNode.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeOsg/OsgCore/OsgView.h"

#include "osgViewer/Viewer"


///////////////////////////////////////////////////////////////////////////
//
// Forward declarations. 
//
///////////////////////////////////////////////////////////////////////////

namespace osg
{
  class Node;
}

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IModel;      
    }
  }

  namespace OgeOsg
  {
    namespace OsgCore
    {
      struct OsgModel;      
      struct OsgView;
    }
  }
}


namespace Oge
{
  namespace OgeOsg
  {    
    namespace OsgViewer
    {
      /////////////////////////////////////////////////////////////////////////
      //
      // Easy to remember names. 
      //
      /////////////////////////////////////////////////////////////////////////

      typedef Oge::OgeBase::OgeInterfaces::IFindNode< osg::Node > IFindNode;      
      typedef Oge::OgeBase::OgeInterfaces::IInputDevice           IInputDevice;


      /////////////////////////////////////////////////////////////////////////
      //
      // Viewer is a OSG based viewer and contains one OsgView and one OsgModel
      // 
      // @Todo: We should be able to attach more views with the same model. 
      //  
      /////////////////////////////////////////////////////////////////////////

      class OGE_EXPORT Viewer : 
        public Oge::OgeOsg::OsgCore::OsgView,
        public osgViewer::Viewer,         
        public Oge::OgeBase::OgeInterfaces::IViewer, 
        public IFindNode
      {
          public: 
                                                          OGE_DELCARE_SMART_PTR( Viewer ); 

            typedef Oge::OgeBase::OgeInterfaces::IUnknown IUnknown;
            typedef Oge::OgeBase::OgeInterfaces::IModel   IModel;
            
                                                          Viewer( ViewerMode vMode = NORMAL );    
            
            virtual void                                  init(); 

            virtual void                                  contextInit();

            virtual void                                  addDataModel( osg::Node* );
            
            virtual void                                  update();
             
            virtual void                                  draw();

            virtual int                                   run(); 

            virtual void                                  setEmbeddedDisplaySize( int x, int y, int width, int height );

            virtual osg::Node*                            findNode( const std::string& id );

            virtual IUnknown*                             queryInterface( const unsigned long& iid );

            virtual void                                  addInputDevice( const std::string& deviceName, IInputDevice* inputDevice );

            virtual IInputDevice*                         getInputDevice( const std::string& deviceName );

        protected: 

          virtual                                        ~Viewer();  
          virtual void                                    setSceneData( osg::Node* );


        protected: 
        
          bool                                                _isDisplayWindowSizeSet;

          int                                                 _viewportX;
          int                                                 _viewportY;
          int                                                 _viewportWidth;
          int                                                 _viewportHeight;

          ViewerMode                                          _viewerMode;

          std::map< const std::string, IInputDevice::RefPtr > _inputDevices;
      };
    }
  }
}

#endif // __OSG_VIEWER_VIEWER_H__
