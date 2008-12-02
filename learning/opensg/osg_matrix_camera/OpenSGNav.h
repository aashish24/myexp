
#ifndef _VRJ_OPENSG_NAV_H_
#define _VRJ_OPENSG_NAV_H_

#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>

#include <iostream>
#include <iomanip>

// VRJuggler includes.
#include "gadget/Type/Position/PositionUnitConversion.h"
#include "gadget/Type/PositionInterface.h"
#include "gadget/Type/AnalogInterface.h"
#include "gadget/Type/DigitalInterface.h"
#include "vrj/Draw/OGL/GlContextData.h"
#include <vrj/vrjConfig.h>
#include <vrj/Draw/OGL/GlApp.h>

// GMTL includes. 
#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Generate.h"

// Lime includes. 
#include "ILimeCamera.h"
#include "LimeVrjCamera.h"
#include "FlyNavigator.h"
#include "OpenSG2App.h"
#include "View.h"
#include "Setup.h"
#include "BG.h"

// For screeen capturing. 
extern "C"
{
  #include "tga.h"
} 


class OpenSGNav : public vrj::OpenSG2App
{
  public:
    
    struct AppContextData
    {
      AppContextData() :
        mLimeCamera(0x00)
      {
      }  

     ~AppContextData()
      {
        if(mLimeCamera){ delete mLimeCamera; mLimeCamera = 0x00; }
      }

      LimeVrjCamera* mLimeCamera;
    };
      
    

    OpenSGNav(vrj::Kernel* kern) : vrj::OpenSG2App(kern),
      mNavigator  (new FlyNavigator(gmtl::Vec3d(1.0, 0.0,  0.0),
                                    gmtl::Vec3d(0.0, 1.0,  0.0),
                                    gmtl::Vec3d(0.0, 0.0,  1.0), 
                                    gmtl::Vec3d(0.0, 0.0, 15.0))),   
      mFileToLoad (""),      
      mVelocity   (0.0f)
   {
      std::cout << "OpenSGNav::OpenSGNav() called\n";      
   }


   virtual ~OpenSGNav()
   {
      std::cout << "OpenSGNav::~OpenSGNav() called\n";
      delete mNavigator; mNavigator = 0x00;
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


protected: 

  virtual void setupCamera();
  


protected:  

     vrj::GlContextData<AppContextData>   mAppContextData;
     
     INavigator*                          mNavigator;

      View                                mView;
      Setup                               mSetup;
      BG                                  mBG; 

private:
   void initGLState();

   void draw_field_grid();   

   void draw_setup_guide(); 

   void draw_cutin( void );

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

   OSG::NodeRefPtr        mLightNode;       /**< Light node to use */
   OSG::NodeRefPtr        mLightBeacon;     /**< A beacon for the light */
   
    GLUquadricObj*        mQuadObj;

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

   gadget::PositionInterface  mHead;
   float                      mVelocity;
};


#endif
