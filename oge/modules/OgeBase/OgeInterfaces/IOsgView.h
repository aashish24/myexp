
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
      struct IOsgView : public IUnknown  
      {
        OGE_DECLARE_SMART_PTR( IOsgView );

        enum                                            { IID = 1607842543 };

        typedef osgUtil::SceneView                      SceneView;

        virtual SceneView*                              sceneView() = 0;        
      };
    } 
  } 
} 

#endif // __OGE_INTERFACES_I_VIEW_H__
