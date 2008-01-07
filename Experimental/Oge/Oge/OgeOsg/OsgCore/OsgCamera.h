
#ifndef __OSG_CAMERA_H__
#define __OSG_CAMERA_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/Camera.h"

#include "Oge/OgeOsg/OsgCore/UpdateNavigation.h"

#include "osg/NodeCallback"
#include "osg/Node"
#include "osg/Group"
#include "osg/Matrix"
#include "osg/MatrixTransform"
namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      struct UpdataAccumulateMatrix : osg::NodeCallback
      {
        virtual void operator()( osg::Node* node, osg::NodeVisitor* nv )
        {
          _matrix = osg::computeWorldToLocal( nv->getNodePath() );
          traverse( node, nv );
        }

        osg::Matrixf _matrix;
      };


      class OGE_EXPORT OsgCamera : public OgeBase::OgeCore::Camera 
      {
        public: 
          
          OsgCamera() :
              _node             ( 0x00 ),
              _parent           ( 0x00 ),
              _worldCoordOfNode ( 0x00 ),
              _nav              ( 0x00 )
          {
            //_node->setUpdateCallback( _worldCoordOfNode );
          }

          
          void assignTo( osg::MatrixTransform* transform )
          {
            if( transform )
            {
              _transform = transform;
              _transform->setUpdateCallback( _nav );
            }
          }


          void attachTo( osg::MatrixTransform* parent )
          {
            if( _parent != 0x00 )
            {
              int n = _parent->getNumChildren();
              for( int i = 0; i < n; ++i )
              {
                if( _node.get() == _parent->getChild( i ) )
                {
                  _parent->removeChild( i, 1 );
                }
              }
            }

            _parent = parent;
            _parent->addChild( _node.get() );
          }


          virtual const float* getMatrix()
          {            
            return  OgeBase::OgeCore::Camera::getMatrix();
          }
    
        protected: 
         
          osg::ref_ptr< osg::Node >             _node;
          osg::ref_ptr< osg::Group >            _parent;
          osg::ref_ptr< osg::MatrixTransform >  _transform;

          UpdataAccumulateMatrix*     _worldCoordOfNode;
          UpdateNavigation*           _nav;
      };
    }
  }
}


#endif // __OSG_CAMERA_H__



