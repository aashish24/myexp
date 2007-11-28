
#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h" 

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgVrj
    {
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
    }
  }
}