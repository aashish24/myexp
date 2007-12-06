
#ifndef __OSG_VIEW_H__
#define __OSG_VIEW_H__

#include "Oge/OgeBase/OgeCore/View.h"

#include "Oge/OgeOsg/OsgCore/OsgModel.h"

#include "osgUtil/SceneView"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      class OGE_EXPORT OsgView : public OgeBase::OgeCore::View
      {
        public: 
        
          OGE_DELCARE_SMART_PTR( OsgView );

                                                OsgView( OgeOsg::OsgCore::OsgModel* model );

          virtual void                          update(); 

          virtual void                          draw();


        protected: 

           virtual                              ~OsgView();

        protected: 
        
          osg::ref_ptr< osgUtil::SceneView >    _sceneView;
      };
    }
  }
}

#endif // __OSG_VIEW_H__
