
#ifdef USE_OSG

#include "Oge/OgeOsg/OsgCore/OsgViewer.h"
#include "Oge/OgeOsg/OsgCore/OsgModel.h"
#include "Oge/OgeOsg/OsgCore/OsgView.h"

#include "osg/MatrixTransform"
#include "osgUtil/SceneView"

#include <algorithm>

using namespace Oge::OgeBase::OgeInterfaces;

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OsgViewer::OsgViewer( int argc, char** argv, IViewer::Mode mode ) :         
        osgViewer::Viewer       (), 
        _mode                   ( mode ),
        _osgModel               ( new OsgModel() ), 
        _osgView                ( new OsgView( _osgModel.get() ) ), 
        _osgCamera              ( new OsgCamera() )         
      {   
        //_osgCamera->assignTo( _osgModel->rootNav() );
        
        // Assuming that the units of model are in meters.
        // @Todo: Somehow write a method that determines the unit setup.
        _osgCamera->set( 0.0, 0.0, 2.0, 0.0, 1.0, 2.0, 0.0, 0.0, 1.0 );
      }


      OsgViewer::~OsgViewer()
      {
      }


      OsgViewer::IUnknown* OsgViewer::queryInterface( const unsigned long& iid )
      {
        switch( iid )
        {
          case IUnknown::IID :          
          case IViewer::IID: 
          {
            return static_cast< IViewer* >( this );
          }
          case IBaseViewer::IID :
          {
            return static_cast< IBaseViewer* >( this );
          }
          default :
          {
            return 0x00;
          }
        };
      }


      void OsgViewer::readConfig( const std::string& config ) 
      {
      }


      void OsgViewer::init()
      {
        BaseViewer::init();

        // Build the model first. 
        _osgModel->build();
      }


      void OsgViewer::update()
      {
        BaseViewer::update();

        // Update the scene with the new camera pos. 
        _osgModel->rootNav()->setMatrix( osg::Matrix( _osgCamera->getMatrix() ) );

        // This has to come after we update the devices. As when we update 
        // devices all the callbacks attached with the inputs will 
        // be called that may result in change in the scenegraph. 
        _osgModel->update();
      }


      void OsgViewer::draw()
      { 
      }


      int OsgViewer::run()
      {
        if( _mode = EMBEDDED )
        {
          this->frame();
        }
        {
          osgViewer::Viewer::run();
        }

        return 1;
      }


      void OsgViewer::setSceneData( osg::Node *sceneRoot )
      {        
        _osgModel->setSceneData( sceneRoot );
      }


      OsgViewer::IView* OsgViewer::getView() const 
      {
        return _osgView.get();
      }


      OsgViewer::ICamera* OsgViewer::getActiveCamera() const 
      {
        return _osgCamera.get();
      }
    } 
  } 
} 

#endif // USE_OSG
