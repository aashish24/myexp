
#ifdef USE_OSG

#include "Oge/OgeVrj/VrjOsg/VrjViewer.h" 

#include "Oge/OgeVrj/VrjDev/Gamepad.h"
#include "Oge/OgeVrj/VrjDev/Tracker.h"

#include "Oge/OgeBase/OgeInterfaces/IFunctor.h"

#include "Oge/OgeVrj/VrjCore/LoadConfigFile.h"

#include "Oge/OgeBase/OgeContexts/GamepadInterfaceContext.h"
#include "Oge/OgeBase/OgeContexts/TrackerInterfaceContext.h"

#include "boost/bind.hpp" 

#include <iostream>

namespace Oge
{
  namespace OgeVrj
  {
    namespace VrjOsg
    {
      VrjViewer::VrjViewer( int argc, char** argv, VrjViewer::IViewer::Mode mode ) : 
        OgeOsg::OsgCore::OsgViewer( argc, argv, mode ), 
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


      VrjViewer::~VrjViewer()
      {
      }


      void VrjViewer::readConfig( const std::string& config )
      {
      }


      void VrjViewer::loadConfigs( const std::vector< std::string >& configs )
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


      void VrjViewer::init()
      {
        vrj::OsgApp::init();
        
        OgeOsg::OsgCore::OsgViewer::init();

        this->configDevices();
      }


      void VrjViewer::contextInit()
      {
        vrj::OsgApp::contextInit();
      }


      void VrjViewer::initScene()
      {
      }


      osg::Group* VrjViewer::getScene()
      {
        return _osgModel->root();
      }


      // Called by the latePreFrame();
      void VrjViewer::update()
      { 
      }


      void VrjViewer::draw()
      {
        // Call vrj::OsgApp::draw() here? 
        // Or should we write our own draw. 
        vrj::OsgApp::draw();
      }


      int VrjViewer::run()
      {
        int result( 1 );          
        
        vrj::Kernel* kernel = vrj::Kernel::instance();

        kernel->start();        

        kernel->setApplication( this ); 

        kernel->waitForKernelStop();
        
        return result;
      }


      void VrjViewer::bufferPreDraw()
      {
        glClearColor( 0.5, 0.5, 0.5, 1.0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      }


      void VrjViewer::preFrame()
      {
      }


      void VrjViewer::latePreFrame()
      { 
        this->update();

        OgeOsg::OsgCore::OsgViewer::update();
        
        vrj::OsgApp::latePreFrame();        
      }


      void VrjViewer::intraFrame()
      {
      }


      void VrjViewer::postFrame()
      {
      }


      void VrjViewer::configDevices()
      {
        OgeVrj::VrjDev::Gamepad::RefPtr gamepad( new OgeVrj::VrjDev::Gamepad() );
        OgeVrj::VrjDev::Gamepad::RefPtr tracker( new OgeVrj::VrjDev::Gamepad() );
                
        this->addInputDevice( "Gamepad01", gamepad.get() );
        this->addInterfaceContext( new OgeBase::OgeContexts::GamepadInterfaceContext( this, gamepad.get() ) );

        this->addInputDevice( "Tracker01", tracker.get() );        
        this->addInterfaceContext( new OgeBase::OgeContexts::TrackerInterfaceContext( this, tracker.get() ) );
      }
    } 
  }
}

#endif // USE_OSG.

    
