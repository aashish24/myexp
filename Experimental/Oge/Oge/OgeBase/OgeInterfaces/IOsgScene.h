
#ifndef __OGE_INTERFACES_I_OSG_MODEL_H__
#define __OGE_INTERFACES_I_OSG_MODEL_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace osg
{
  class Node;  
  class Group;
  class MatrixTransform;
}

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgScene : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IOsgScene );

        enum                            { IID = 1088960704 };

        virtual osg::Group*             root() = 0;  

        virtual osg::MatrixTransform*   rootNav() = 0;

        virtual osg::Group*             rootModel() = 0;  
        
        virtual osg::MatrixTransform*   rootStatic() = 0;
        
        virtual osg::Group*             rootScreen() = 0;
        
        virtual void                    setSceneData( osg::Node* node ) = 0;
      };
    } 
  } 
} 

#endif // __OGE_INTERFACES_I_OSG_MODEL_H__
