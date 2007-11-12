
#ifndef __I_OSG_VIEW_H__
#define __I_OSG_VIEW_H__

#include "IView.h" 

#include "osgUtil/SceneView"

namespace Oge
{ 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgView : IView 
      {
        enum{ IID = 1607842543 };

        virtual osgUtil::SceneView* sceneView() = 0;
      };
    } // namespace OgeInterfaces
  } // namespace OgeBase
} // namespace Oge

#endif // __I_OSG_VIEW_H__
