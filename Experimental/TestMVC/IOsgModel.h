
#ifndef __I_OSG_MODEL_H__
#define __I_OSG_MODEL_H__

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
        typedef osg::Node Node;

        enum{ IID = 1088960704 };

        virtual Node*         root() = 0;  

        virtual Node*         rootNav() = 0;

        virtual Node*         rootModel() = 0;  
        
        virtual Node*         rootStatic() = 0;
        
        virtual Node*         rootScreen() = 0;
        
        virtual void          setSceneData( Node* node ) = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_OSG_MODEL_H__