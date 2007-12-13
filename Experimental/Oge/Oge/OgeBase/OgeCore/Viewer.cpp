
#include "Oge/OgeBase/OgeCore/Viewer.h"
#include "Oge/OgeBase/OgeCore/View.h"

#include "oge/OgeBase/OgeInterfaces/IInputDevice.h"

namespace Oge
{
  namespace OgeBase
  { 
    namespace OgeCore
    {

      Viewer::Viewer( int argc, char** argv, ViewerMode mode, IView* view, IModel* model ) :         
        _viewportX                ( 0 ), 
        _viewportY                ( 0 ), 
        _viewportWidth            ( 400 ), 
        _viewportHeight           ( 400 ), 
        _isDisplayWindowSizeSet   ( false ),
        _viewerMode               ( mode ), 
        _view                     ( view ),
        _model                    ( model )
      { 
      }


      Viewer::~Viewer() 
      {
      }  


      void Viewer::readConfig( const std::string& config )
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
        switch( iid )
        {
          case IUnknown::IID:
          {
          }          
          default: 
          {
            return 0x00;
          }
        };
      }


      // update input devices and view. 
      void Viewer::update()
      {
        std::map< const std::string, IInputDevice::RefPtr >::iterator itr;
        for( itr = _inputDevices.begin(); itr != _inputDevices.end(); ++itr )
        {
          itr->second->update();
        }

        _model->update();
      }


      void Viewer::draw()
      {
      }


      int Viewer::run()
      {
        return 1;
      }


      Viewer::IView* Viewer::getView() const
      {
        return _view.get();
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
