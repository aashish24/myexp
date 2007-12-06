
#include "Oge/OgeOsg/OsgCore/OsgView.h"
#include "Oge/OgeBase/OgeInterfaces/IOsgImpl.h"

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
        _sceneView->cull();
        _sceneView->draw();
      }
    }
  }
}
