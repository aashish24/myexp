
///////////////////////////////////////////////////////////////////////////////
//
// OSG specific implementation of Interaction. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_OSGINTERACTION_H__
#define	__CORE_OSGINTERACTION_H__

#include <iostream>
#include <vector>
#include <string>

#include "osg/Node"
#include "osg/Group"
#include "osg/LineSegment"
#include "osg/MatrixTransform"
#include "osgFX/Scribe"

#include "osgUtil/IntersectVisitor"

#include "Core/Interaction.h"
#include "Core/SharedData.h"
#include "Core/Globals.h"
#include "Util/OsgFind.h"

#ifdef HAVE_KEYBOARDMOUSE
#include "Dev/KeyboardMouse.h"
#endif

#include "Math/ExpFunction.h"

#include "Export.h"

namespace Core
{
	class CORE_EXPORT OsgInteraction : public Interaction
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
			
      virtual NavigationMode                            navigationMode();
			virtual void                                      navigationMode( NavigationMode mode );			
			
			virtual Navigation&                               navigator( InteractionMode mode );

			virtual void                                      defineControls();

			virtual void                                      takeActionAnalog ( InteractionMode mode, int id, double data );
			virtual void                                      takeActionDigital( InteractionMode mode, int id, DeviceData data );

			virtual void                                      joystickAxis1GlobalAction( double data);
			virtual void                                      joystickAxis2GlobalAction( double data );
			virtual void                                      joystickAxis3GlobalAction( double data );
			virtual void                                      joystickAxis4GlobalAction( double data );
      virtual void                                      joystickAxis5GlobalAction( double data );
			virtual void                                      joystickAxis6GlobalAction( double data );

			virtual void                                      trackerAxis1GlobalAction( double data);
			virtual void                                      trackerAxis2GlobalAction( double data);

			virtual void                                      joystickButton1GlobalAction ( DeviceData data );
			virtual void                                      joystickButton2GlobalAction ( DeviceData data );
			virtual void                                      joystickButton3GlobalAction ( DeviceData data );
			virtual void                                      joystickButton4GlobalAction ( DeviceData data );
			virtual void                                      joystickButton5GlobalAction ( DeviceData data );
			virtual void                                      joystickButton6GlobalAction ( DeviceData data );
			virtual void                                      joystickButton7GlobalAction ( DeviceData data );
			virtual void                                      joystickButton8GlobalAction ( DeviceData data );
			virtual void                                      joystickButton9GlobalAction ( DeviceData data );
			virtual void                                      joystickButton10GlobalAction( DeviceData data );
			virtual void                                      joystickButton11GlobalAction( DeviceData data );
			virtual void                                      joystickButton12GlobalAction( DeviceData data );
			virtual void                                      joystickButton13GlobalAction( DeviceData data );
			virtual void                                      joystickButton14GlobalAction( DeviceData data );
			virtual void                                      joystickButton15GlobalAction( DeviceData data );
			virtual void                                      joystickButton16GlobalAction( DeviceData data );
			virtual void                                      joystickButton17GlobalAction( DeviceData data );
			virtual void                                      joystickButton18GlobalAction( DeviceData data );
					
			virtual void                                      trackButton1GlobalAction( DeviceData data );
			virtual void                                      trackButton2GlobalAction( DeviceData data );
			virtual void                                      trackButton3GlobalAction( DeviceData data );
			virtual void                                      trackButton4GlobalAction( DeviceData data );
			virtual void                                      trackButton5GlobalAction( DeviceData data );
			virtual void                                      trackButton6GlobalAction( DeviceData data );
			virtual void                                      trackButton7GlobalAction( DeviceData data );
			
			virtual void                                      updateAll();
      virtual void                                      updateDeviceData();
			virtual void                                      updateInputs();			
			virtual void                                      updateStates();
			virtual void                                      updateTransforms();
			virtual void                                      updateInteractions();	

			virtual void                                      reset();
		
		protected:

			osg::ref_ptr< osg::Group >			                  mSceneRootNode;
			osg::ref_ptr< osg::MatrixTransform >              mSceneTransformNode;
			
      osg::ref_ptr< osg::Group >			                  mSceneWand;			
      osg::ref_ptr<osg::MatrixTransform>		            mSceneWandTransform;

			
			
      osg::Vec3f					                              mObjectPivot;		
			osg::Vec3f					                              mScenePivot;

			double						                                mSceneRadius;		
	};
}

#endif // __CORE_OSGINTERACTION_H__
