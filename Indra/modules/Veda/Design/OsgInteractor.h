
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// OSG specific implementation for Interactions. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DESIGN_OSGINTERACTION_H__
#define __DESIGN_OSGINTERACTION_H__

#include <iostream>
#include <vector>
#include <string>

#include "osg/Node"
#include "osg/Group"
#include "osg/LineSegment"
#include "osg/MatrixTransform"
#include "osgFX/Scribe"

#include "osgUtil/IntersectVisitor"

#include "Veda/Design/Interactor.h"

#include "Veda/Core/Globals.h"

#include "OsgTools/SG/OsgFind.h"

#ifdef HAVE_KEYBOARDMOUSE
#include "Dev/KeyboardMouse.h"
#endif

#include "Math/ExpFunction.h"

#include "Veda/Export.h"

namespace Veda
{
  namespace Design
  {
    class VEDA_EXPORT OsgInteractor : public Interactor
    {
      public:

        typedef Neiv::Pointer::SmartPtr< OsgInteractor >  RefPtr;

        OsgInteractor();

        virtual osg::Group*                               root();
        virtual void                                      root( void* node );

        virtual osg::MatrixTransform*                     transform();      

        virtual void                                      setSceneWand();        

        void                                              resetNavigation();

        virtual void                                      updateAll();        
        virtual void                                      updateStates();
        virtual void                                      updateTransforms();
        virtual void                                      updateInteractions();  

      protected:
        
        virtual ~OsgInteractor();

      protected:   

        osg::ref_ptr< osg::Group >                        mSceneRootNode;
        osg::ref_ptr< osg::MatrixTransform >              mSceneTransformNode;
        
        osg::ref_ptr< osg::Group >                        mSceneWand;      
        osg::ref_ptr<osg::MatrixTransform>                mSceneWandTransform;        
        
        osg::Vec3f                                        mScenePivot;        
    };
  }
}

#endif // __DESIGN_OSGINTERACTION_H__

