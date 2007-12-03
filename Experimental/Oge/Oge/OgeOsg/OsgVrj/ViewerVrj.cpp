
#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h" 

#include "Oge/OgeBase/OgeDev/Gamepad.h"

#include "boost/bind.hpp" 

#include <iostream>

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgVrj
    {

      struct Print : public Oge::OgeBase::OgeInterfaces::IFunctor 
      {
        virtual void operator()( )
        {
          std::cout << "Test: " << std::endl;
        }

        virtual IUnknown* queryInterface( const unsigned long& iid )
        {
          return 0x00;
        }
      };


      ViewerVrj::ViewerVrj( ViewerMode vm ) : 
        Viewer( vm ), 
        vrj::OsgApp()
      {
      }


      ViewerVrj::~ViewerVrj()
      {
      }


      void ViewerVrj::init()
      {
        vrj::OsgApp::init();
        Viewer::init();

        configDevices();
      }


      void ViewerVrj::contextInit()
      {
        vrj::OsgApp::contextInit();
      }


      void ViewerVrj::initScene()
      {
      }


      osg::Group* ViewerVrj::getScene()
      {
        return this->getModel()->root()->asGroup();
      }

      // Called by the latePreFrame();
      void ViewerVrj::update()
      {
        Viewer::update();
      }


      void ViewerVrj::draw()
      {
        // Call vrj::OsgApp::draw() here? 
        // Or should we write our own draw. 
        vrj::OsgApp::draw();
      }


      int ViewerVrj::run()
      {
        int result( 1 );          
        
        vrj::Kernel* kernel = vrj::Kernel::instance();

        // @Todo: This is hardcoded as of now. 
        kernel->loadConfigFile( "simstandalone.jconf" );

        kernel->start();        

        kernel->setApplication( this ); 

        kernel->waitForKernelStop();
        
        return result;
      }


      bi::ICamera* ViewerVrj::getCamera( const unsigned int& index ) 
      {
        return Oge::OgeOsg::OsgCore::OsgView::getCamera( index );
      }

      void ViewerVrj::bufferPreDraw()
      {
        glClearColor( 0.5, 0.5, 0.5, 1.0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      }


      void ViewerVrj::preFrame()
      {
      }


      void ViewerVrj::latePreFrame()
      {        
        update();
        vrj::OsgApp::latePreFrame();
      }


      void ViewerVrj::intraFrame()
      {
      }


      void ViewerVrj::postFrame()
      {
      }


      void ViewerVrj::configDevices()
      {
        this->addInputDevice( "Gamepad01", new Oge::OgeBase::OgeDev::Gamepad() );
        this->configGamepad();
      }


      void ViewerVrj::configGamepad()
      {
        Print* print = new Print();

        Oge::OgeBase::OgeDev::Gamepad* gp =  dynamic_cast< Oge::OgeBase::OgeDev::Gamepad* >( this->getInputDevice( "Gamepad01" ) );
        if( gp )
        { 
          // @Temp
          // This is an example. 
          gp->getInput( 0 )->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyPress, print, false ); 
          gp->getInput( 0 )->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyPress, print, true ); 
        }
      }
    } 
  }
}

    