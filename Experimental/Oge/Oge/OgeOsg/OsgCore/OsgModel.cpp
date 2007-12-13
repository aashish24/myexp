
#include "Oge/OgeOsg/OsgCore/OsgModel.h" 

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OsgModel::OsgModel() : 
        _root       ( new osg::Group() ),   
        _rootStatic ( new osg::MatrixTransform() ), 
        _rootNav    ( new osg::MatrixTransform() ), 
        _rootScreen ( new osg::Group() ), 
        _rootModel  ( new osg::Group() )
      {
        this->build();
      }


      OsgModel::IUnknown* OsgModel::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case IUnknown::IID :
          {
          }
          case IModel::IID : 
          {
            return static_cast< IModel* >( this );
          }
          case IOsgImpl::IID : 
          {
            return static_cast< IOsgImpl* >( this );
          }
        };
      }


      void OsgModel::build()
      { 
        _rootNav->setMatrix( osg::Matrixf::translate( osg::Vec3f( 0.0, 0.0, 0.0 ) ) );
        _rootNav->addChild( _rootModel.get() );  
        _rootStatic->addChild( _rootScreen.get() );
          
        _root->addChild( _rootNav.get() );
        _root->addChild( _rootStatic.get() );
      }


      osg::Group* OsgModel::root()
      {
        return _root.get();
      }


      osg::Group* OsgModel::rootModel() 
      {
        return _rootModel.get();
      }


      osg::MatrixTransform* OsgModel::rootNav()
      {
        return _rootNav.get();
      }


      osg::MatrixTransform* OsgModel::rootStatic()
      {
        return _rootStatic.get();
      }


      osg::Group* OsgModel::rootScreen()
      {
        return _rootScreen.get();
      }


      void OsgModel::setSceneData( osg::Node* node )
      {
        _rootModel->addChild( node );
      }
    }
  }
}