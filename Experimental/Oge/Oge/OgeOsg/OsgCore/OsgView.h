
#ifndef __OSG_VIEWER_OSG_VIEW_H__
#define __OSG_VIEWER_OSG_VIEW_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IOsgView.h"

#include "Oge/OgeBase/OgeCore/Camera.h" 
#include "Oge/OgeBase/OgeCore/Referenced.h" 


#include <vector>

namespace osgUtil
{
  class SceneView;
}

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgModel;
      struct ICamera;
    }
  }
}

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    { 
      struct OGE_EXPORT OsgView : public Oge::OgeBase::OgeInterfaces::IOsgView
      {
                                                        OGE_DELCARE_SMART_PTR( OsgView );     

        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;  
        typedef Oge::OgeBase::OgeInterfaces::IOsgModel  IOsgModel;
        typedef Oge::OgeBase::OgeInterfaces::ICamera    ICamera;
        
        typedef Oge::OgeBase::OgeCore::Camera           Camera;

        typedef osgUtil::SceneView                      SceneView;  

                                                        OsgView( IOsgModel* model ); 
       
        virtual IUnknown*                               queryInterface( const unsigned long& iid );

        virtual SceneView*                              sceneView();  
        
        virtual IOsgModel*                              getModel();
        virtual void                                    setModel( IOsgModel* model );

        virtual void                                    update();

        virtual void                                    setCamera( ICamera* camera );
        virtual ICamera*                                getCamera( const unsigned int& index = 0 );

        virtual void                                    addCamera( ICamera* camera );

        virtual void                                    draw();
       

        protected: 
      
          virtual                                      ~OsgView();    


        protected: 

          IOsgModel*                                  _model;

          SceneView*                                  _sceneView;

          std::vector< ICamera::RefPtr >              _cameras;
      };
    } // namespace OsgCore
  } // namespace OgeOsg
} // namespace Oge

#endif // __OSG_VIEWER_OSG_VIEW_H__
