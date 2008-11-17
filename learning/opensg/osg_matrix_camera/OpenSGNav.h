
#ifndef _VRJ_OPENSG_NAV_H_
#define _VRJ_OPENSG_NAV_H_

#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>

#include <iostream>
#include <iomanip>

#include <vrj/vrjConfig.h>
#include <vrj/Draw/OGL/GlApp.h>
#include "OpenSG2App.h"

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>

#include <gadget/Type/Position/PositionUnitConversion.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>

#include <vrj/Draw/OGL/GlContextData.h>


class OpenSGNav : public vrj::OpenSG2App
{
public:
   OpenSGNav(vrj::Kernel* kern)
      : vrj::OpenSG2App(kern)
      , mFileToLoad("")
      , mVelocity(0.0f)
   {
      std::cout << "OpenSGNav::OpenSGNav() called\n";
   }

   virtual ~OpenSGNav()
   {
      std::cout << "OpenSGNav::~OpenSGNav() called\n";
   }

   /** Handles any initialization needed before API. */
   virtual void init();

   /** Initialize the scene graph. */
   virtual void initScene();

   /** Returns the scene root for this application. */
   virtual OSG::Node* getScene()
   {
      return mSceneRoot.get();
   }

   virtual void draw();

   virtual void contextInit();

   virtual void preFrame();

   virtual float getDrawScaleFactor()
   {
      return gadget::PositionUnitConversion::ConvertToFeet;
   }

   virtual void exit();

   void setModelFileName(std::string filename)
   {
      std::cout << "[OpenSGNav::setModelFileName()] Set filename '"
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
   OSG::NodeRefPtr        mSceneRoot;       /**< The root of the scene */
   OSG::TransformRefPtr   mSceneTransform;  /**< Transform core */
   OSG::NodeRefPtr        mModelRoot;       /**< Root of the loaded model */

   OSG::NodeRefPtr  mLightNode;       /**< Light node to use */
   OSG::NodeRefPtr  mLightBeacon;     /**< A beacon for the light */

public:
   gadget::DigitalInterface   mButton01; /**< Digital interface for button 1 */
   gadget::DigitalInterface   mButton02; /**< Digital interface for button 2 */
   gadget::DigitalInterface   mButton03; /**< Digital interface for button 3 */
   gadget::DigitalInterface   mButton04; /**< Digital interface for button 4 */
   gadget::DigitalInterface   mButton05; /**< Digital interface for button 5 */
   gadget::DigitalInterface   mButton06; /**< Digital interface for button 6 */
   gadget::DigitalInterface   mButton07; /**< Digital interface for button 7 */
   gadget::DigitalInterface   mButton08; /**< Digital interface for button 8 */
   gadget::DigitalInterface   mButton09; /**< Digital interface for button 9 */

   gadget::AnalogInterface    mAnalog01; /**< Analog interface for button 1 */
   gadget::AnalogInterface    mAnalog02; /**< Analog interface for button 2 */
   gadget::AnalogInterface    mAnalog03; /**< Analog interface for button 3 */
   gadget::AnalogInterface    mAnalog04; /**< Analog interface for button 4 */
   gadget::AnalogInterface    mAnalog05; /**< Analog interface for button 5 */
   gadget::AnalogInterface    mAnalog06; /**< Analog interface for button 6 */          

   float mVelocity;
};


#endif
