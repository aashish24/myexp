
#ifndef __OSG_VIEWER_OSG_MODEL_H__
#define __OSG_VIEWER_OSG_MODEL_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IOsgModel.h"


#include <vector>

namespace osg
{
  class Node;
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
      struct OGE_EXPORT OsgModel : public Oge::OgeBase::OgeInterfaces::IOsgModel
      {
                                                        OGE_DELCARE_SMART_PTR( OsgModel );     

        typedef Oge::OgeBase::OgeInterfaces::IUnknown   IUnknown;
        typedef Oge::OgeBase::OgeInterfaces::IObserver  IObserver;
        typedef Oge::OgeBase::OgeInterfaces::IOsgView   IOsgView;
      
        typedef osg::Group                              Group;
        typedef osg::MatrixTransform                    MatrixTransform;

        OsgModel();       

        virtual IUnknown*           queryInterface( const unsigned long& iid );
        
        virtual osg::Node*          root();

        virtual osg::Node*          rootModel();   
          
        virtual osg::Node*          rootNav();
        
        virtual osg::Node*          rootStatic();
        
        virtual osg::Node*          rootScreen();    
        
        virtual void                build();
        
        virtual void                attach( IObserver* observer );
        
        virtual void                update();

        virtual void                setSceneData( osg::Node* node ); 


        protected: 
          
          virtual                   ~OsgModel();


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
