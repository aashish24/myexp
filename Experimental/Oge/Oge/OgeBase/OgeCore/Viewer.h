
#ifndef __OGE_CORE_VIEWER_H__
#define __OGE_CORE_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"
#include "Oge/OgeBase/OgeInterfaces/IFindNode.h"
#include "Oge/OgeBase/OgeInterfaces/IView.h"
#include "Oge/OgeBase/OgeInterfaces/IModel.h"
#include "Oge/OgeBase/OgeInterfaces/IViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"
#include "Oge/OgeBase/OgeCore/Pointer.h"

#include <map>
#include <vector>

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
        public Oge::OgeBase::OgeInterfaces::IViewer,         
        public Oge::OgeBase::OgeCore::Referenced
      {
          public: 

            OGE_DELCARE_SMART_PTR( Viewer ); 

            IMPLEMENT_IUNKNOWN_MEMBERS( Viewer, Oge::OgeBase::OgeCore::Referenced ); 

            typedef Oge::OgeBase::OgeInterfaces::IUnknown IUnknown;
            typedef Oge::OgeBase::OgeInterfaces::IModel   IModel;
            typedef Oge::OgeBase::OgeInterfaces::IView    IView;
            
                                                          Viewer( ViewerMode vMode = REGULAR );    
            
            virtual void                                  init(); 

            virtual void                                  contextInit();

            virtual void                                  update();
             
            virtual void                                  draw();

            virtual int                                   run(); 

            virtual void                                  setEmbeddedDisplaySize( int x, int y, int width, int height );

            virtual IUnknown*                             queryInterface( const unsigned long& iid );

            virtual IView*                                getView() const;

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

          IView::RefPtr                                       _view;
          IModel::RefPtr                                      _model;


          std::map< const std::string, IInputDevice::RefPtr > _inputDevices;
      };
    }
  }
}

#endif // __OGE_CORE_VIEWER_H__
