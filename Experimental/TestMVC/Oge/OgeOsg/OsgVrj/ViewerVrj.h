
#include "Oge/OgeOsg/OsgViewer/Viewer.h"

#include "vrj/vrjConfig.h"
#include "vrj/Draw/OSG/OsgApp.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgVrj
    {
      // We could possibly add these functions for the Juggler interface. 
      // 1. loadConfig( const std::vector< std::string > configs )
      // 2. We need to develope 
      //    - device functor file 
      //    - viewer preferenced file
      //    - and may be some other options. 
      // Add frame capture functionality ( better via a plugin )

      namespace ov = Oge::OgeOsg::OsgViewer; 

      class ViewerVrj : public ov::Viewer, public vrj::OsgApp
      {
        public:     
          
          virtual void  init();

          virtual void  contextInit(); 

          virtual void  update(); 

          virtual void  draw(); 

          virtual int   run();

        protected: 
            
          virtual void  preFrame(); 
          
          virtual void  latePreFrame(); 

          virtual void  intraFrame(); 

          virtual void  postFrame();               
      };
    }
  }
}