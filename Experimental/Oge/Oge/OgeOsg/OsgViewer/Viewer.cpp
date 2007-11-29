
#include "Oge/OgeOsg/OsgViewer/Viewer.h"

#include "Oge/OgeOsg/OsgCore/OsgModel.h" 
#include "Oge/OgeOsg/OsgCore/OsgView.h" 

#include "oge/OgeBase/OgeInterfaces/IInputDevice.h"

namespace Oge
{
  namespace OgeOsg
  { 
    namespace OsgViewer
    {

      Viewer::Viewer( ViewerMode vModel ) : 
        OgeOsg::OsgCore::OsgView  ( new OsgCore::OsgModel() ), 
        osgViewer::Viewer         (),        
        _viewportX                ( 0 ), 
        _viewportY                ( 0 ), 
        _viewportWidth            ( 400 ), 
        _viewportHeight           ( 400 ), 
        _isDisplayWindowSizeSet   ( false ),
        _viewerModel              ( vModel )
      {   
        //init();
      }


      Viewer::~Viewer() 
      {
      }  


      void Viewer::init()
      {
        _model->build();
        setSceneData( this->sceneView()->getSceneData() );       

        // Now initialize the devices. 
        std::map< const std::string, IInputDevice* >::iterator itr;
        for( itr = _inputDevices.begin(); itr != _inputDevices.end(); ++itr )
        {
          itr->second->init();
        }
      }

      
      /////////////////////////////////////////////////////////////////////////
      //
      // 
      // @Note: This function should be called by the external windowing system 
      // only when we have a valid context. 
      //
      /////////////////////////////////////////////////////////////////////////

      void Viewer::contextInit()
      {        
        if( _viewerModel == EMBEDDED )
        {
          this->setUpViewerAsEmbeddedInWindow
            ( _viewportX, _viewportY, _viewportWidth, _viewportHeight );
        }
      }


      void Viewer::addDataModel( osg::Node* node )
      {
        ( this->getModel()->rootModel()->asGroup() )->addChild ( node );
      }


      void Viewer::setEmbeddedDisplaySize( int x, int y, int width, int height )
      {
        _viewportX = x;
        _viewportY = y;

        _viewportWidth =  width;
        _viewportHeight = height;
      }


      osg::Node* Viewer::findNode( const std::string& id )
      {
        return 0x00;
      }


      Viewer::IUnknown* Viewer::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }


      void Viewer::update()
      {
        std::map< const std::string, IInputDevice* >::iterator itr;
        for( itr = _inputDevices.begin(); itr != _inputDevices.end(); ++itr )
        {
          itr->second->update();
        }
      }


      void Viewer::draw()
      {
      }


      int Viewer::run()
      {
        if( _viewerModel != EMBEDDED )
        {
          osgViewer::Viewer::run();
        }
        {
          frame();
        }

        return 1;
      }


      void Viewer::setSceneData( osg::Node* node )
      {
        osgViewer::Viewer::setSceneData( node );
      }


      void Viewer::addInputDevice( const std::string& deviceName, IInputDevice *inputDevice )
      {

        if( _inputDevices.find( deviceName ) == _inputDevices.end() )
        {
          _inputDevices[ deviceName ] = inputDevice;
        }
      }


      IInputDevice* Viewer::getInputDevice( const std::string& deviceName )
      {
        if( _inputDevices.find( deviceName ) != _inputDevices.end() )
        {
          return _inputDevices.find( deviceName )->second;
        }
        else
        {
          return 0x00;
        }
      }
    }
  }
}
