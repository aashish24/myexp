
#ifndef __I_ALPHA_OSG_MODEL_H__
#define __I_ALPHA_OSG_MODEL_H__

#include "osg/Node"
#include "osg/Group"
#include "osg/MatrixTransform"

#include "IOsgModel.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IOsgView;
    }
  }
}

namespace Oge
{
  namespace OgeOsg
  {
    namespace OgeOsgCore
    {
      struct AlphaOsgModel : public Oge::OgeBase::OgeInterfaces::IOsgModel
      {
        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;
        typedef Oge::OgeBase::OgeInterfaces::IObserver  IObserver;
        typedef Oge::OgeBase::OgeInterfaces::IOsgView   IOsgView;
      
        AlphaOsgModel();

       ~AlphaOsgModel();

        virtual IUnknown*           queryInterface( unsigned long iid );

        virtual void                attach( IObserver* observer );
        
        virtual void                update();

        virtual osg::Node*          root();

        virtual osg::Node*          rootModel();   
          
        virtual osg::Node*          rootNav();
        
        virtual osg::Node*          rootStatic();
        
        virtual osg::Node*          rootScreen();    
        
        virtual void                build();
        
        virtual void                setSceneData( osg::Node* node ); 

        protected: 

          osg::Group*               _root;

          osg::Group*               _rootModel;
          
          osg::MatrixTransform*     _rootNav;

          osg::Group*               _rootStatic;
          
          osg::Group*               _rootScreen;

          std::vector< IOsgView* >  _osgViews;
      };
    } // namespace OgeOsgCore
  } // namespace OgeOsg
} // namespace Oge

#endif // __I_ALPHA_OSG_MODEL_H__
