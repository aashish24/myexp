
///////////////////////////////////////////////////////////////////////////////
//
// OSG specific implementation of Interaction. 
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

#include "Veda/Design/Interaction.h"

#include "Veda/Core/SharedData.h"
#include "Veda/Core/Globals.h"

#include "OsgTools/SG/OsgFind.h"

#ifdef HAVE_KEYBOARDMOUSE
#include "Dev/KeyboardMouse.h"
#endif

#include "Math/ExpFunction.h"

#include "Veda/Core/Export.h"

namespace Veda
{
  namespace Design
  {
    class VEDA_EXPORT OsgInteraction : public Interaction
    {
      public:

        OsgInteraction();

       ~OsgInteraction();

        virtual void                                      init();

        virtual osg::Group*                               root();
        virtual void                                      root( void* node );

        virtual osg::MatrixTransform*                     transform();      

        virtual void                                      setSceneWand();

        virtual void                                      resetNavigation();
        
        virtual Core::NavigationMode                      navigationMode();
        virtual void                                      navigationMode( Core::NavigationMode mode );      
        
        virtual Navigation&                               navigator( Core::InteractionMode mode );

        virtual void                                      defineControls();

        virtual void                                      takeActionAnalog ( Core::InteractionMode mode, int id, double data );
        virtual void                                      takeActionDigital( Core::InteractionMode mode, int id, Core::DeviceData data );

        virtual void                                      joystickAxis1GlobalAction( double data);
        virtual void                                      joystickAxis2GlobalAction( double data );
        virtual void                                      joystickAxis3GlobalAction( double data );
        virtual void                                      joystickAxis4GlobalAction( double data );
        virtual void                                      joystickAxis5GlobalAction( double data );
        virtual void                                      joystickAxis6GlobalAction( double data );

        virtual void                                      trackerAxis1GlobalAction( double data);
        virtual void                                      trackerAxis2GlobalAction( double data);

        virtual void                                      joystickButton1GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton2GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton3GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton4GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton5GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton6GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton7GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton8GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton9GlobalAction ( Core::DeviceData data );
        virtual void                                      joystickButton10GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton11GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton12GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton13GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton14GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton15GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton16GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton17GlobalAction( Core::DeviceData data );
        virtual void                                      joystickButton18GlobalAction( Core::DeviceData data );
            
        virtual void                                      trackButton1GlobalAction( Core::DeviceData data );
        virtual void                                      trackButton2GlobalAction( Core::DeviceData data );
        virtual void                                      trackButton3GlobalAction( Core::DeviceData data );
        virtual void                                      trackButton4GlobalAction( Core::DeviceData data );
        virtual void                                      trackButton5GlobalAction( Core::DeviceData data );
        virtual void                                      trackButton6GlobalAction( Core::DeviceData data );
        virtual void                                      trackButton7GlobalAction( Core::DeviceData data );
        
        virtual void                                      updateAll();
        virtual void                                      updateDeviceData();
        virtual void                                      updateInputs();      
        virtual void                                      updateStates();
        virtual void                                      updateTransforms();
        virtual void                                      updateInteractions();  

        virtual void                                      reset();
      
      protected:

        osg::ref_ptr< osg::Group >                        mSceneRootNode;
        osg::ref_ptr< osg::MatrixTransform >              mSceneTransformNode;
        
        osg::ref_ptr< osg::Group >                        mSceneWand;      
        osg::ref_ptr<osg::MatrixTransform>                mSceneWandTransform;

        
        
        osg::Vec3f                                        mObjectPivot;    
        osg::Vec3f                                        mScenePivot;

        double                                            mSceneRadius;    
    };
  }
}

#endif // __DESIGN_OSGINTERACTION_H__
