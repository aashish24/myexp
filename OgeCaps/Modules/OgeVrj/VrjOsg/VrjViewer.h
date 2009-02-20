
#include "Oge/Export.h"

#include "Oge/OgeOsg/OsgCore/OsgViewer.h"

#include "Oge/OgeBase/OgeInterfaces/IOsgScene.h"

#include "vrj/vrjConfig.h"
#include "vrj/Draw/OSG/OsgApp.h"

#include <vector>
#include <string>

namespace Oge
{
  namespace OgeVrj
  {
    namespace VrjOsg
    {
      // We could possibly add these functions for the Juggler interface. 
      // 1. loadConfig( const std::vector< std::string > configs )
      // 2. We need to develope 
      //    - List of devices and their internal config.. 
      //      - List of interface used. 
      //      - Name of controller used. ( Controller always needs access to view and device ). 
      // 
      //    - Viwer preferences file.       
      //    - and may be some other options. 
      // Add frame capture functionality ( better via a plugin )
      // How we add the devices? 
      // How we add functions that needs to be called? 

      class OGE_EXPORT VrjViewer : public OgeOsg::OsgCore::OsgViewer, 
                                   public vrj::OsgApp
      {
        public: 
          
          OGE_DELCARE_SMART_PTR( VrjViewer );     

          typedef OgeBase::OgeInterfaces::IOsgScene IOsgScene;
          typedef OgeBase::OgeInterfaces::IViewer   IViewer;

          VrjViewer( int argc = 0, char** argv = 0, IViewer::Mode mode =  IViewer::EMBEDDED );

          virtual void          readConfig( const std::string& config );

          virtual void          loadConfigs( const std::vector< std::string >& configs );

          virtual void          init();

          virtual void          contextInit(); 

          virtual void          initScene();

          virtual osg::Group*   getScene();

          virtual void          update(); 

          virtual void          draw(); 

          virtual int           run();
        
        protected: 
          
          virtual              ~VrjViewer();

          virtual void          bufferPreDraw();

          virtual void          preFrame(); 
          
          virtual void          latePreFrame(); 

          virtual void          intraFrame(); 

          virtual void          postFrame();               
          

        private:
        
          void                  configDevices(); 
      };
    }
  }
}

