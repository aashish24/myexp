
#ifdef USE_OSG

#include "Oge/OgeOsg/OsgCore/OsgView.h"
#include "Oge/OgeBase/OgeInterfaces/IOsgScene.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OsgView::OsgView( OgeOsg::OsgCore::OsgModel* model ) : 
        View      ( model ),
        _sceneView( new osgUtil::SceneView() )
      {         
        _sceneView->setSceneData( model->root() );
      }


      OsgView::~OsgView()
      {
      }


      void OsgView::update()
      { 
        _sceneView->update();
      }
    

      void OsgView::draw()
      {
        // Apply camera transformation to the scene. 
        // Todo: Implement this. 

        // Now start cull and draw traversal. 
        _sceneView->cull();
        _sceneView->draw();
      }
    }
  }
}

#endif // USE_OSG