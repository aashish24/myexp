
#ifndef __I_OSG_VIEW_H__
#define __I_OSG_VIEW_H__

#include "IView.h" 

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
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_OSG_VIEW_H__
