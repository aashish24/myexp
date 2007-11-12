
#include "osg/Node"
#include "osg/Group"
#include "osg/MatrixTransform"


#include "IObserver.h"
#include "IOsgView.h"

#include "IOsgModel.h"


struct AlphaOsgModel : public IOsgModel
{
  AlphaOsgModel();

 ~AlphaOsgModel();

  virtual IUnknown*           queryInterface( unsigned long iid );

  virtual void                attach( IObserver* observer );
  
  virtual void                update();

  virtual osg::Node*          root();

  virtual osg::Node*          rootModel();   
    
  virtual osg::Node*          rootNav();
  
  virtual osg::Node*          rootStatic();
  
  virtual osg::Node*          rootScreen();    
  
  virtual void                buildScene();
  
  virtual void                setSceneData( osg::Node* node ); 

  protected: 

    osg::Group*               _root;

    osg::Group*               _rootModel;
    
    osg::MatrixTransform*     _rootNav;

    osg::Group*               _rootStatic;
    
    osg::Group*               _rootScreen;

    std::vector< IOsgView* >  _osgViews;
};



AlphaOsgModel::AlphaOsgModel() : 
  _root       ( new osg::Group() ), 
  _rootModel  ( new osg::Group() ),
  _rootNav    ( new osg::MatrixTransform() ), 
  _rootStatic ( new osg::Group() ), 
  _rootScreen ( new osg::Group() )
{ 
}

AlphaOsgModel::~AlphaOsgModel()
{
}

IUnknown* AlphaOsgModel::queryInterface( unsigned long iid )
{
  switch( iid )
  {
    case IUnknown::IID :
    case IModel::IID :
    {
      return static_cast< IModel* >( this );
    }
    case IOsgModel::IID :
    {
      return static_cast< IOsgModel* >( this );
    }    
    default:
    {
      return  0x00;
    }
  };
}

void AlphaOsgModel::attach( IObserver* observer )
{
  IUnknown* view = observer->queryInterface( IOsgView::IID );  
  
  if( view )
  {
    _osgViews.push_back( static_cast< IOsgView* >( view ) );
  }
}

void AlphaOsgModel::update()
{
  std::vector< IOsgView* >::const_iterator constItr; 
  for( constItr = _osgViews.begin(); constItr != _osgViews.end(); ++constItr )
  {
    (*constItr)->update();
  }
}

osg::Node* AlphaOsgModel::root()
{
  return _root;
}


osg::Node* AlphaOsgModel::rootModel() 
{
  return _rootModel;
}

osg::Node* AlphaOsgModel::rootNav()
{
  return _rootNav;
}

osg::Node* AlphaOsgModel::rootStatic()
{
  return _rootStatic;
}

osg::Node* AlphaOsgModel::rootScreen()
{
  return _rootScreen;
}

void AlphaOsgModel::setSceneData( osg::Node* node )
{
  _rootModel->addChild( node );
}

void AlphaOsgModel::buildScene()
{  
  _rootNav->addChild( _rootModel );  
  _rootStatic->addChild( _rootScreen );
    
  _root->addChild( _rootNav );
  _root->addChild( _rootStatic );
} 
