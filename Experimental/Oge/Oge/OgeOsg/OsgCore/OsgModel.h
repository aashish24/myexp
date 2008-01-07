
#ifndef __OSG_MODEL_H__
#define __OSG_MODEL_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/Model.h"

#include "Oge/OgeBase/OgeInterfaces/IOsgScene.h"

#include "osg/Node"
#include "osg/Group"
#include "osg/MatrixTransform"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      class OGE_EXPORT OsgModel : 
        public OgeBase::OgeCore::Model, 
        public OgeBase::OgeInterfaces::IOsgScene
      {
        public: 
          
          OGE_DELCARE_SMART_PTR( OsgModel ); 

          IMPLEMENT_IUNKNOWN_MEMBERS( OsgModel, OgeBase::OgeCore::Model );

          typedef OgeBase::OgeInterfaces::IUnknown  IUnknown;          

                                                    OsgModel();
       
          virtual IUnknown*                         queryInterface( const unsigned long& iid ); 
      
          virtual void                              build();

          virtual osg::Group*                       root();

          virtual osg::Group*                       rootModel();   
          
          virtual osg::MatrixTransform*             rootNav();
        
          virtual osg::MatrixTransform*             rootStatic();
        
          virtual osg::Group*                       rootScreen();            
           
          virtual void                              setSceneData( osg::Node* node );

       protected: 

          osg::ref_ptr< osg::Group >                _root;
          osg::ref_ptr< osg::MatrixTransform >      _rootNav;
          osg::ref_ptr< osg::MatrixTransform >      _rootStatic;
          osg::ref_ptr< osg::Group >                _rootModel;          
          osg::ref_ptr< osg::Group >                _rootScreen;
      };
    }
  }
}

#endif // __OSG_MODEL_H_

