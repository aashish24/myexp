
#ifndef __OGE_CORE_VIEWER_H__
#define __OGE_CORE_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IFindNode.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"


#include "Oge/OgeBase/OgeCore/View.h"

#include <map>

namespace Oge
{
  namespace OgeBase
  {    
    namespace OgeCore
    {
      /////////////////////////////////////////////////////////////////////////
      //
      // Easy to remember names. 
      //
      /////////////////////////////////////////////////////////////////////////

      typedef Oge::OgeBase::OgeInterfaces::IInputDevice           IInputDevice;


      /////////////////////////////////////////////////////////////////////////
      //
      // Viewer is a OSG based viewer and contains one OsgView and one OsgModel
      // 
      // @Todo: We should be able to attach more views with the same model. 
      //  
      /////////////////////////////////////////////////////////////////////////

      class OGE_EXPORT Viewer : 
        public View,        
        public Oge::OgeBase::OgeInterfaces::IViewer         
      {
          public: 
                                                          OGE_DELCARE_SMART_PTR( Viewer ); 

            typedef Oge::OgeBase::OgeInterfaces::IUnknown IUnknown;
            typedef Oge::OgeBase::OgeInterfaces::IModel   IModel;
            
                                                          Viewer( OgeInterfaces::IModel* model, ViewerMode vMode = NORMAL );    
            
            virtual void                                  init(); 

            virtual void                                  contextInit();

            virtual void                                  update();
             
            virtual void                                  draw();

            virtual int                                   run(); 

            virtual void                                  setEmbeddedDisplaySize( int x, int y, int width, int height );

            virtual IUnknown*                             queryInterface( const unsigned long& iid );

            virtual void                                  addInputDevice( const std::string& deviceName, IInputDevice* inputDevice );

            virtual IInputDevice*                         getInputDevice( const std::string& deviceName );

        protected: 

          virtual                                        ~Viewer();  
        

        protected: 
        
          bool                                                _isDisplayWindowSizeSet;

          int                                                 _viewportX;
          int                                                 _viewportY;
          int                                                 _viewportWidth;
          int                                                 _viewportHeight;

          ViewerMode                                          _viewerMode;

          std::map< const std::string, IInputDevice::RefPtr > _inputDevices;
      };
    }
  }
}

#endif // __OGE_CORE_VIEWER_H__
