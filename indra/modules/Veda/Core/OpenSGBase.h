
#ifdef HAVE_OPENSG
#	define WIN32
#	define _WINDOWS
#	define WINVER 0x0400
#	define _WIN32_WINDOWS 0x0410
#	define _WIN32_WINNT 0x0400
#	define _OSG_HAVE_CONFIGURED_H_
#	define OSG_BUILD_DLL
#	define _DEBUG
#	define OSG_DEBUG
#	define OSG_WITH_GLUT
#	define OSG_WITH_GIF
#	define OSG_WITH_TIF
#	define OSG_WITH_JPG
#endif 

#ifndef __VEDA_CORE_OPENSGBASE_H__
#define __VEDA_CORE_OPENSGBASE_H__

// This should be the first include. 
#include "Veda/VedaConfig.h"

#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>

#include <iostream>
#include <iomanip>

#include <vrj/vrjConfig.h>
#include <vrj/Draw/OGL/GlApp.h>
#include <vrj/Draw/OpenSG/OpenSGApp.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>

#include <gadget/Type/Position/PositionUnitConversion.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>

#include <vrj/Draw/OGL/GlContextData.h>

#include "Veda/Core/AppBase.h"
#include "Veda/Core/SharedData.h"
#include "Veda/Export.h"

namespace Veda
{
  namespace Core
  {

		class VEDA_EXPORT OpenSGBase : public AppBase, public vrj::OpenSGApp
		{
		  public:
				OpenSGBase(vrj::Kernel* kern)
					: vrj::OpenSGApp(kern)
					, mFileToLoad("")
					, mVelocity(0.0f)
				{
					std::cout << "OpenSGNav::OpenSGNav() called\n";
				}

				virtual ~OpenSGBase()
				{
					std::cout << "OpenSGBase::~OpenSGBase() called\n";
				}

				/** Handles any initialization needed before API. */
				virtual void init();

				/** Initialize the scene graph. */
				virtual void initScene();

				/** Returns the scene root for this application. */
				virtual OSG::NodePtr getScene()
				{
					return mSceneRoot;
				}

				virtual void draw();

				virtual void contextInit();

				virtual void preFrame();

				virtual float getDrawScaleFactor()
				{
					return gadget::PositionUnitConversion::ConvertToFeet;
				}

				void setModelFileName(std::string filename)
				{
						std::cout << "[OpenSGBase::setModelFileName()] Set filename '"
                << filename << "'\n";
						mFileToLoad = filename;
				}

		private:
			void initGLState();

		private:
			std::string mFileToLoad;      /**< Filename of the file to load */

			//   mSceneRoot:[mSceneTransform]
			//         |
			//   mLightNode:[DirectionalLight]
			//         |
			//   mLightBeacon:[Transform]
			//         |
			//     mModelRoot
			OSG::NodePtr        mSceneRoot;       /**< The root of the scene */
			OSG::TransformPtr   mSceneTransform;  /**< Transform core */
			OSG::NodePtr        mModelRoot;       /**< Root of the loaded model */

			OSG::NodePtr  mLightNode;       /**< Light node to use */
			OSG::NodePtr  mLightBeacon;     /**< A beacon for the light */

		public:
			gadget::PositionInterface  mWandPos;     /**< The position of the wand */
			gadget::DigitalInterface   mButton0;     /**< Wand button 0 */
			gadget::DigitalInterface   mButton1;     /**< Wand button 1 */
			gadget::DigitalInterface   mButton2;     /**< Wand button 2 */

			float mVelocity;
		};
	}
}

#endif // __VEDA_CORE_OPENSGBASE_H__
