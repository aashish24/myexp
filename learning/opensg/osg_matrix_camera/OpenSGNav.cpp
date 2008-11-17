
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <vrj/vrjConfig.h>

#include <math.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/Coord.h>
#include <gmtl/Xforms.h>

#include <vrj/Display/Projection.h>
#include <vrj/Display/CameraProjection.h>

#include "OpenSGNav.h"

// Handle any initialization needed before API
void OpenSGNav::init()
{
   vrj::OpenSG2App::init();      // Call base class init
}

/** Called once per context at context creation */
void OpenSGNav::contextInit()
{
   vrj::OpenSG2App::contextInit();
   initGLState();
}

void OpenSGNav::draw()
{
   // Call parent class first to render the scene graph
   vrj::OpenSG2App::draw();
}

void OpenSGNav::preFrame()
{   
   vrj::OpenSG2App::preFrame();
}

void OpenSGNav::exit()
{
   // Ensure that we release all the OSG::RefPtr<T> objects that we hold so
   // that OpenSG can shut down cleanly.
   mSceneRoot      = 0x00;
   mSceneTransform = 0x00;
   mModelRoot      = 0x00;
   mLightNode      = 0x00;
   mLightBeacon    = 0x00;

   vrj::OpenSG2App::exit();
}

/** Initialize GL state. Hold over from regular OGL apps */
void OpenSGNav::initGLState()
{
   // OpenSG does not handle this yet, being smart about it is not
   // that trivial...
   glEnable(GL_NORMALIZE);
}

void OpenSGNav::initScene()
{
   vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_CRITICAL_LVL,
                        "OpenSGNav::initScene() called.\n",
                        "OpenSGNav::initScene() exiting.\n");

   // --- Initialize vrj devices --- //
    mButton01.init("VJButton01");
    mButton02.init("VJButton02");
    mButton03.init("VJButton03");
    mButton04.init("VJButton04");
    mButton05.init("VJButton05");
    mButton06.init("VJButton06");
    mButton07.init("VJButton07");
    mButton08.init("VJButton08");
    mButton09.init("VJButton09");

    mAnalog01.init("VJAnalog01");
    mAnalog02.init("VJAnalog02");
    mAnalog03.init("VJAnalog03");
    mAnalog04.init("VJAnalog04");
    mAnalog05.init("VJAnalog05");
    mAnalog06.init("VJAnalog06");           

   // Load the model to use
   if (mFileToLoad ==  std::string("none"))
   {
      vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
         << "[OpenSGNav::initScene()] No model specified; creating torus."
         << std::endl << vprDEBUG_FLUSH;
      mModelRoot = OSG::makeTorus(.5, 2, 16, 16);
   }
   else
   {
      vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
         << "[OpenSGNav::initScene()] Loading '" << mFileToLoad << "' ..."
         << std::endl << vprDEBUG_FLUSH;
      const OSG::Char8* file = mFileToLoad.c_str();
#if OSG_MAJOR_VERSION < 2
      mModelRoot = OSG::SceneFileHandler::the().read(file);
#else
      mModelRoot = OSG::SceneFileHandler::the()->read(file);
#endif
   }
   

   // create the root part of the scene
   mSceneRoot = OSG::Node::create();
   mSceneTransform = OSG::Transform::create();

   // Set up the root node
   mSceneRoot->setCore(mSceneTransform);
   mSceneRoot->addChild(mModelRoot);
}
