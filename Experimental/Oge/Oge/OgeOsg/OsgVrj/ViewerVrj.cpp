
#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h" 

#include "Oge/OgeBase/OgeDev/Gamepad.h"

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeBase/OgeCore/MakeFunctor.h"

#include "boost/bind.hpp" 

#include <iostream>

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgVrj
    {
      ViewerVrj::ViewerVrj( ViewerMode vm ) : 
        OsgCore::OsgViewer( vm ), 
        vrj::OsgApp()
      {
      }


      ViewerVrj::~ViewerVrj()
      {
      }


      void ViewerVrj::init()
      {
        vrj::OsgApp::init();
        OsgCore::OsgViewer::init();

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
        return this->root()->asGroup();
      }


      // Called by the latePreFrame();
      void ViewerVrj::update()
      {
        OsgCore::OsgViewer::update();
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
        return OgeBase::OgeCore::View::getCamera( index );
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
        //Print* print = new Print( this );
        //Print2*print2 = new Print2( this );  

        Oge::OgeBase::OgeDev::Gamepad* gp =  dynamic_cast< Oge::OgeBase::OgeDev::Gamepad* >( this->getInputDevice( "Gamepad01" ) );
        if( gp )
        { 

          // @Temp
          // This is an example. 
          //gp->getInput( 0 )->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyDown, print, false ); 
          //gp->getInput( 1 )->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyDown, print2, true ); 
          //gp->getInput( 1 )->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyDown, OgeBase::OgeCore::MakeMyFunctor( boost::bind( &Camera::move, this->getCamera(), _1 )( 1.0 ) ), true ); 
          
          //Oge::OgeBase::OgeInterfaces::IFunctor* functor = 
          //   new Oge::OgeBase::OgeCore::MakeFunctor( boost::bind( &Oge::OgeBase::OgeCore::Camera::move, 
          //  dynamic_cast< Oge::OgeBase::OgeCore::Camera* >( this->getCamera() ), _1 ) );

          //gp->getInput( 1 )->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyDown, functor, false );
                                                
        }
      }
    } 
  }
}

    