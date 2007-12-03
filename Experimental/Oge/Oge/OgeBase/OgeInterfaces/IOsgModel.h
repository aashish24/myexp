
#ifndef __OGE_INTERFACES_I_OSG_MODEL_H__
#define __OGE_INTERFACES_I_OSG_MODEL_H__

#include "IModel.h" 

namespace osg
{
  class Node;  
}

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgModel : public IModel
      {
        enum                  { IID = 1088960704 };

                              OGE_DELCARE_SMART_PTR( IOsgModel );

        virtual osg::Node*    root() = 0;  

        virtual osg::Node*    rootNav() = 0;

        virtual osg::Node*    rootModel() = 0;  
        
        virtual osg::Node*    rootStatic() = 0;
        
        virtual osg::Node*    rootScreen() = 0;
        
        virtual void          setSceneData( osg::Node* node ) = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_OSG_MODEL_H__
