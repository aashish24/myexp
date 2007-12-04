
#include "Oge/OgeOsg/OsgViewer/Viewer.h"

#include "Oge/OgeOsg/OsgCore/OsgModel.h" 
#include "Oge/OgeOsg/OsgCore/OsgView.h" 

#include "oge/OgeBase/OgeInterfaces/IInputDevice.h"

namespace Oge
{
  namespace OgeBase
  { 
    namespace OgeCore
    {

      Viewer::Viewer( OgeBase::OgeInterfaces::IModel* model, ViewerMode mode ) : 
        View                      ( model ),         
        _viewportX                ( 0 ), 
        _viewportY                ( 0 ), 
        _viewportWidth            ( 400 ), 
        _viewportHeight           ( 400 ), 
        _isDisplayWindowSizeSet   ( false ),
        _viewerMode               ( mode )
      { 
      }


      Viewer::~Viewer() 
      {
      }  


      // Initialize model and input devices. 
      void Viewer::init()
      {
        _model->build();       

        // Now initialize the devices. 
        std::map< const std::string, IInputDevice::RefPtr >::iterator itr;
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
      }


      void Viewer::setEmbeddedDisplaySize( int x, int y, int width, int height )
      {
        _viewportX = x;
        _viewportY = y;

        _viewportWidth =  width;
        _viewportHeight = height;
      }


      // Need to implement this. 
      Viewer::IUnknown* Viewer::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }


      // update input devices and view. 
      void Viewer::update()
      {
        std::map< const std::string, IInputDevice::RefPtr >::iterator itr;
        for( itr = _inputDevices.begin(); itr != _inputDevices.end(); ++itr )
        {
          itr->second->update();
        }

        View::update();
      }


      void Viewer::draw()
      {
      }


      int Viewer::run()
      {
        return 1;
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
          return _inputDevices.find( deviceName )->second.get();
        }
        else
        {
          return 0x00;
        }
      }
    }
  }
}
