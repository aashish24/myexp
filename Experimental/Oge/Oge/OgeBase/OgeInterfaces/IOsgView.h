
#ifndef __OGE_INTERFACES_I_OSG_VIEW_H__
#define __OGE_INTERFACES_I_OSG_VIEW_H__

#include "IView.h" 

#include "IOsgModel.h"

namespace osgUtil
{
    class SceneView;
}

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgView : IView 
      {
        typedef osgUtil::SceneView                      SceneView;
        
        enum                                            { IID = 1607842543 };

        virtual SceneView*                              sceneView() = 0;

        virtual IOsgModel*                              getModel() = 0;
        virtual void                                    setModel( IOsgModel* model ) = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __OGE_INTERFACES_I_VIEW_H__
