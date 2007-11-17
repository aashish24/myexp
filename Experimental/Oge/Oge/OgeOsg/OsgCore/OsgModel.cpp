
#include "OsgModel.h"

#include "Oge/OgeBase/OgeInterfaces/IObserver.h"
#include "Oge/OgeBase/OgeInterfaces/IOsgModel.h"
#include "Oge/OgeBase/OgeInterfaces/IOsgView.h"

#include "osg/Node"
#include "osg/Group"
#include "osg/MatrixTransform"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OsgModel::OsgModel() : 
        _root       ( new osg::Group() ), 
        _rootModel  ( new osg::Group() ),
        _rootNav    ( new osg::MatrixTransform() ), 
        _rootStatic ( new osg::Group() ), 
        _rootScreen ( new osg::Group() )
      {  
      }

      OsgModel::~OsgModel()
      {        
      }

      OsgModel::IUnknown* OsgModel::queryInterface( const unsigned long& iid )
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

      void OsgModel::attach( IObserver* observer )
      {
        IUnknown* view = observer->queryInterface( IOsgView::IID );  
        
        if( view )
        {
          _osgViews.push_back( static_cast< IOsgView* >( view ) );
        }
      }

      void OsgModel::update()
      {
        std::vector< IOsgView* >::const_iterator constItr; 
        for( constItr = _osgViews.begin(); constItr != _osgViews.end(); ++constItr )
        {
          (*constItr)->update();
        }
      }

      osg::Node* OsgModel::root()
      {
        return _root;
      }


      osg::Node* OsgModel::rootModel() 
      {
        return _rootModel;
      }

      osg::Node* OsgModel::rootNav()
      {
        return _rootNav;
      }

      osg::Node* OsgModel::rootStatic()
      {
        return _rootStatic;
      }

      osg::Node* OsgModel::rootScreen()
      {
        return _rootScreen;
      }

      void OsgModel::setSceneData( osg::Node* node )
      {
        _rootModel->addChild( node );
      }

      void OsgModel::build()
      {  
        _rootNav->addChild( _rootModel );  
        _rootStatic->addChild( _rootScreen );
          
        _root->addChild( _rootNav );
        _root->addChild( _rootStatic );
      } 
    } // namespace OsgCore
  } // namespace OgeOsg
} // namespace Oge
