
#ifndef __OSG_VIEWER_VIEWER_H__
#define __OSG_VIEWER_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IFindNode.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"

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


      /////////////////////////////////////////////////////////////////////////
      //
      // Viewer is a OSG based viewer and contains one OsgView and one OsgModel
      // 
      // @Todo: We should be able to attach more views with the same model. 
      //  
      /////////////////////////////////////////////////////////////////////////

      class OGE_EXPORT Viewer : 
        public osgViewer::Viewer,         
        public Oge::OgeBase::OgeInterfaces::IViewer, 
        public IFindNode
      {
        public:           

          typedef Oge::OgeBase::OgeInterfaces::IUnknown IUnknown;
          typedef Oge::OgeOsg::OsgCore::OsgModel        OsgModel;
          typedef Oge::OgeOsg::OsgCore::OsgView         OsgView;

                                                        Viewer( ViewerModel vMode = NORMAL );    
          virtual                                      ~Viewer();  
          
          virtual void                                  init(); 

          virtual void                                  contextInit();

          virtual void                                  setModelData( osg::Node* );

          virtual void                                  setEmbeddedDisplaySize( int x, int y, int width, int height );

          virtual osg::Node*                            findNode( const std::string& id );

          virtual IUnknown*                             queryInterface( const unsigned long& iid );

          virtual void                                  update();
           
          virtual void                                  draw();

          virtual int                                   run(); 

        protected: 

          virtual void                                  setSceneData( osg::Node* );


        protected: 
        
          bool                                          _isDisplayWindowSizeSet;

          int                                           _viewportX;
          int                                           _viewportY;
          int                                           _viewportWidth;
          int                                           _viewportHeight;
  

          OsgModel*                                     _model;
          
          OsgView*                                      _view; 

          ViewerModel                                   _viewerModel;
      };
    }
  }
}

#endif // __OSG_VIEWER_VIEWER_H__
