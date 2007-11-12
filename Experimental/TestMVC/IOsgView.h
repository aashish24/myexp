
#ifndef __I_OSG_VIEW_H__
#define __I_OSG_VIEW_H__

#include "IView.h" 

namespace osgUtil
{
  class SceneView;
}

struct IOsgView : IView 
{
  enum{ IID = 5 };

  virtual osgUtil::SceneView* sceneView() = 0;
};

#endif // __I_OSG_VIEW_H__