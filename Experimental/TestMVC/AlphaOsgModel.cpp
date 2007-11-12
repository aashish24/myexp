
#include "AlphaOsgModel.h"

#include "IObserver.h"

#include "osg/Node"
#include "osg/Group"
#include "osg/MatrixTransform"

#include "IOsgModel.h"
#include "IOsgView.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OgeOsgCore
    {
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

      AlphaOsgModel::IUnknown* AlphaOsgModel::queryInterface( unsigned long iid )
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

      void AlphaOsgModel::build()
      {  
        _rootNav->addChild( _rootModel );  
        _rootStatic->addChild( _rootScreen );
          
        _root->addChild( _rootNav );
        _root->addChild( _rootStatic );
      } 
    } // namespace OgeOsgCore
  } // namespace OgeOsg
} // namespace Oge
