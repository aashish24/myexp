
#ifndef __OSG_VIEWER_OSG_MODEL_H__
#define __OSG_VIEWER_OSG_MODEL_H__

#include "Oge/OgeBase/OgeInterfaces/IOsgModel.h"

#include <vector>

namespace osg
{
  class Group;
  class MatrixTransform;
}

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
    namespace OsgCore
    {
      struct OsgModel : public Oge::OgeBase::OgeInterfaces::IOsgModel
      {
        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;
        typedef Oge::OgeBase::OgeInterfaces::IObserver  IObserver;
        typedef Oge::OgeBase::OgeInterfaces::IOsgView   IOsgView;
      
        typedef osg::Group                              Group;
        typedef osg::MatrixTransform                    MatrixTransform;

        OsgModel();

       ~OsgModel();

        virtual IUnknown*           queryInterface( const unsigned long& iid );
        
        virtual Node*               root();

        virtual Node*               rootModel();   
          
        virtual Node*               rootNav();
        
        virtual Node*               rootStatic();
        
        virtual Node*               rootScreen();    
        
        virtual void                build();
        
        virtual void                attach( IObserver* observer );
        
        virtual void                update();

        virtual void                setSceneData( Node* node ); 

        protected: 

          Group*                    _root;

          Group*                    _rootModel;
          
          MatrixTransform*          _rootNav;

          Group*                    _rootStatic;
          
          Group*                    _rootScreen;

          std::vector< IOsgView* >  _osgViews;
      };
    } // namespace OsgCore
  } // namespace OgeOsg
} // namespace Oge

#endif // __OSG_VIEWER_OSG_MODEL_H__
