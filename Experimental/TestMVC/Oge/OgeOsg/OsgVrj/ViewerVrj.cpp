
#include "Oge/OgeOsg/OsgVrj/ViewerVrj.h" 

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgVrj
    {
      void ViewerVrj::init()
      {
      }


      void ViewerVrj::contextInit()
      {
      }


      void ViewerVrj::update()
      {
        // Called by the latePreFrame();
      }


      void ViewerVrj::draw()
      {
        // Call vrj::OsgApp::draw() here? 
        // Or should we write our own draw. 
      }


      int ViewerVrj::run()
      {
        int result( 1 );
          
        // Initialize the kernel here and hand off the application. 

        return result;
      }
    }
  }
}