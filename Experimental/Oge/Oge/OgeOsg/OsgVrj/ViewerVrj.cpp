
#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h" 

#include "Oge/OgeBase/OgeDev/Gamepad.h"

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeVrj/VrjCore/LoadConfigFile.h"

#include "Oge/OgeBase/OgeController/DefaultInterfaceContext.h"

#include "boost/bind.hpp" 

#include <iostream>

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgVrj
    {
      ViewerVrj::ViewerVrj( int argc, char** argv, ViewerVrj::IViewer::Mode mode ) : 
        OsgCore::OsgViewer( argc, argv, mode ), 
        vrj::OsgApp()
      { 
        // Since we dont have the parser lets just assume that arg 2 
        // suppose to provide the config file.
        // Later this would be under readConfig.. 
        std::vector< std::string > configs;
        for( int i=2; i < argc; ++i )
        {
          configs.push_back( std::string( argv[ i ] ) );
        }

        this->loadConfigs( configs );
      }


      ViewerVrj::~ViewerVrj()
      {
      }


      void ViewerVrj::readConfig( const std::string& config )
      {
      }


      void ViewerVrj::loadConfigs( const std::vector< std::string >& configs )
      {
        if( configs.empty() )
        {
          //??
        }
        else
        {
          std::for_each( configs.begin(), configs.end(), OgeVrj::VrjCore::LoadConfigFile() );
        }
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
        return _osgModel->root();
      }


      // Called by the latePreFrame();
      void ViewerVrj::update()
      {
        // Now call vrjuggler osg update where update traversal of osg
        // is going to take place.
        //vrj::OsgApp::update();

        OsgCore::OsgViewer::update();
        vrj::OsgApp::latePreFrame();
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

        kernel->start();        

        kernel->setApplication( this ); 

        kernel->waitForKernelStop();
        
        return result;
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
        OgeBase::OgeDev::Gamepad::RefPtr gp( new OgeBase::OgeDev::Gamepad() );
                
        this->addInputDevice( "Gamepad01", gp.get() );
        this->addInterfaceContext( new OgeBase::InterfaceContext::DefaultInterfaceContext( this, gp.get() ) );
      }
    } 
  }
}

    