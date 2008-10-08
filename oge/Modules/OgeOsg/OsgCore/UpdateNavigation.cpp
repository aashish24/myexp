
#include "UpdateNavigation.h"
#include "OsgCamera.h"

#include "osg/Node"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      UpdateNavigation::UpdateNavigation( OsgCamera* camera ) : 
        _camera ( camera )
      {
      }

      UpdateNavigation::~UpdateNavigation()
      {
      }


      void UpdateNavigation::operator()( osg::Node* node, osg::NodeVisitor* nv )
      {
        node->asTransform()->asMatrixTransform()->setMatrix( osg::Matrix( _camera->getMatrix() ) );
        traverse( node, nv );
      }
    }
  }
}