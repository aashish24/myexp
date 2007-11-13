
#ifndef __OGE_OGE_OSG_OSG_VIEWER_VIWER_H__
#define __OGE_OGE_OSG_OSG_VIEWER_VIWER_H__

#include "IUnknown.h"
#include "IFindNode.h"
#include "IViewer.h"

#include "OsgView.h"

#include "osgViewer/Viewer"


namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgViewer
    {
      /////////////////////////////////////////////////////////////////////////
      //
      //
      //
      /////////////////////////////////////////////////////////////////////////

      typedef Oge::OgeBase::OgeInterfaces::IFindNode< osg::Node > IFindNode;
      
      /////////////////////////////////////////////////////////////////////////
      //
      // Viewer is a OsgViewer and contains one OgeOsg::View 
      //
      /////////////////////////////////////////////////////////////////////////

      class Viewer : 
        public osgViewer::Viewer,         
        public Oge::OgeBase::OgeInterfaces::IViewer, 
        public IFindNode
      {
        public:           

          typedef Oge::OgeBase::OgeInterfaces::IUnknown IUnknown;
                                                        Viewer();    
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
        
          Oge::OgeOsg::OsgCore::OsgModel*               _model;
          
          Oge::OgeOsg::OsgCore::OsgView*                _view; 
      };
    }
  }
}

Oge::OgeOsg::OsgViewer::Viewer::Viewer() : 
  osgViewer::Viewer(),
  _model( new Oge::OgeOsg::OsgCore::OsgModel() ) ,
  _view( new Oge::OgeOsg::OsgCore::OsgView( _model ) )
{ 
  _model->build();
  init();
}

Oge::OgeOsg::OsgViewer::Viewer::~Viewer() 
{
}  

void Oge::OgeOsg::OsgViewer::Viewer::init()
{
  this->setSceneData( _view->sceneView()->getSceneData() );
}

void Oge::OgeOsg::OsgViewer::Viewer::contextInit()
{
}

void Oge::OgeOsg::OsgViewer::Viewer::setModelData( osg::Node* node )
{
  ( _model->rootModel()->asGroup() )->addChild ( node );
}

osg::Node* Oge::OgeOsg::OsgViewer::Viewer::findNode( const std::string& id )
{
  return 0x00;
}

Oge::OgeOsg::OsgViewer::Viewer::IUnknown* Oge::OgeOsg::OsgViewer::Viewer::queryInterface( const unsigned long& iid )
{
  return 0x00;
}

void Oge::OgeOsg::OsgViewer::Viewer::update()
{
}

void Oge::OgeOsg::OsgViewer::Viewer::draw()
{
}

int Oge::OgeOsg::OsgViewer::Viewer::run()
{
  return osgViewer::Viewer::run();
}

#endif // __OGE_OGE_OSG_OSG_VIEWER_VIWER_H__
