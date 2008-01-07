
#ifndef __A__
#define __A__

#include "osg/NodeCallback"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      class OsgCamera;

      struct UpdateNavigation : osg::NodeCallback
      {
        UpdateNavigation( OsgCamera* camera );

        virtual ~UpdateNavigation();


        virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

        OsgCamera* _camera;
      };
    }
  }
}

#endif 

