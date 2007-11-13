
#ifndef __OGE_OGE_OSG_OSG_VIEWER_VIWER_H__
#define __OGE_OGE_OSG_OSG_VIEWER_VIWER_H__

#include "IUnknown.h"
#include "IFindNode.h"
#include "IViewer.h"

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

      class Viewer : 
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

          virtual osg::Node*                            findNode( const std::string& id );

          virtual IUnknown*                             queryInterface( const unsigned long& iid );

          virtual void                                  update();
           
          virtual void                                  draw();

          virtual int                                   run(); 

        protected: 

          virtual void                                  setSceneData( osg::Node* );


        protected: 
        
          OsgModel*                                     _model;
          
          OsgView*                                      _view; 

          ViewerModel                                   _viewerModel;
      };
    }
  }
}

#endif // __OGE_OGE_OSG_OSG_VIEWER_VIWER_H__
