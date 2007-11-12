
#ifndef __ALPHA_OSG_VIEW_H__
#define __ALPHA_OSG_VIEW_H__

#include "IOsgView.h"

#include "osgUtil/SceneView"

struct AlphaOsgView : public IOsgView
{
  AlphaOsgView( IOsgModel* model ); 
 ~AlphaOsgView(); 

  virtual IUnknown*           queryInterface( unsigned long iid );

  virtual osgUtil::SceneView* sceneView();  

  virtual void                update();

  virtual void                draw();
  

  protected: 

    IOsgModel*                _model;

    osgUtil::SceneView*       _sceneView;
};

AlphaOsgView::AlphaOsgView( IOsgModel* model ) : 
  _model( model ), 
  _sceneView( new osgUtil::SceneView() )
{
  if( _model )
  {
    _model->attach( this );
    _sceneView->setDefaults();
    _sceneView->setSceneData( _model->root() );
  }
}

IUnknown* AlphaOsgView::queryInterface( unsigned long iid )
{
  switch( iid )
  {
    case IUnknown::IID :
    case IObserver::IID:
    {
      return static_cast< IObserver* >( this );
    }
    case IView::IID :
    {
      return static_cast< IView* >( this );
    }
    case IOsgView::IID :
    {
      return static_cast< IOsgView* >( this );
    }    
    default :
    {
      return 0x00;
    }
  };
}

osgUtil::SceneView* AlphaOsgView::sceneView()
{
  return _sceneView;
}

void AlphaOsgView::update()
{
  _sceneView->update();
}

void AlphaOsgView::draw()
{ 
  _sceneView->cull();
  _sceneView->draw();
}

#endif // __ALPHA_OSG_VIEW_H__
