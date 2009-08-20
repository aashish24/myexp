/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2005 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          MultiLoadAppBase.cpp,v
 * Date modified: 2005/08/11 02:38:32
 * Version:       1.19.2.1
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include "MultiLoadAppBase.h"

//#include "OpenSGVectorInput.h"
#include "GamepadNavigator.h"
#include "WandNavigator.h"
#include "WandFlyNavigator.h"

/*==========================================================================*/
/* SceneOptionsBase                                                         */
/*==========================================================================*/
    MultiLoadAppBase::SceneOptionsBase::SceneOptionsBase(void)
    : mBindFiles(),
      mCamFiles ()
{
    // nothing to do
}

    MultiLoadAppBase::SceneOptionsBase::~SceneOptionsBase(void)
{
    // nothing to do
}

/*==========================================================================*/
/* SceneDataBase                                                            */
/*==========================================================================*/

    MultiLoadAppBase::SceneDataBase::SceneDataBase(MaterialManager const *pMatManager)
    
    : pRootN           (),
      pSceneTransN     (),
      pSceneTrans      (),
      pModelTransN     (),
      pModelTrans      (),
      pModelN          (),
      pLFile           (NULL),
      pBridge          (NULL),
      pNavigator       (NULL),
      mNavigatorAdapter(),
      pObjCache        (new NamedObjectCache()),
      pMatBinder       (new MaterialBinder  ()),
      pCamManager      (new CameraManager   ()),
      mFreeCam         (false                 ),
      mAnimStartTime   (),
      mAnimTime        (),
      mAnimPlaying     (false),
      mAnimPaused      (false),
      mAnimLoop        (true)
{
        pMatBinder  ->setObjCache  (pObjCache  );
        pMatBinder  ->setMatManager(pMatManager);
}

    MultiLoadAppBase::SceneDataBase::~SceneDataBase(void)
{
    lib3ds_file_free(pLFile);
    if (pBridge)    delete pBridge;
    if (pNavigator) delete pNavigator;    
    if (pMatBinder) delete pMatBinder;
    if (pObjCache)  delete pObjCache;
    if (pCamManager)delete pCamManager;
    
    pLFile      = NULL;
    pBridge     = NULL;
    pNavigator  = NULL;
    pMatBinder  = NULL;
    pObjCache   = NULL;
    pCamManager = NULL;
}

/*==========================================================================*/
/* MultiLoadAppBase                                                            */
/*==========================================================================*/

MultiLoadAppBase::MultiLoadAppBase(vrj::Kernel* kern)
    : Inherited          (kern),
      mConfigFileNames   (),
      mVJConfigFileNames (),
      mPathHandler       (),
      pShaderManager     (NULL),
      pTexManager        (NULL),
      mMatFiles          (),
      pMatManager        (NULL),
      mSceneOptions      (),
      mSceneData         (),
      mCurrTime          (),
      mActiveScene       (-1),
      mActiveSceneOptions(NULL),
      mActiveSceneData   (NULL),
      pConsole           (NULL)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "MultiLoadAppBase::MultiLoadAppBase() called.\n",
                         "MultiLoadAppBase::MultiLoadAppBase() exiting.\n");
    
	char *d_dir = getenv("LFW_DATA_DIR");
	std::string data_dir;
	
	if (!d_dir){
		vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
		            << "MultiLoadApp::MultiLoadApp: LFW_DATA_DIR environment variable not set; using './data' \n"
		            << vprDEBUG_FLUSH;	
		data_dir = "./data";
	}
	else {
		data_dir = d_dir;
		vprDEBUG(vprDBG_ALL, vprDBG_CONFIG_STATUS_LVL) 
		            << "MultiLoadApp::MultiLoadApp: found LFW_DATA_DIR == " << data_dir << std::endl
		            << vprDEBUG_FLUSH;		
	}
	
    mPathHandler.addPath(data_dir + "/models"   );
    mPathHandler.addPath(data_dir + "/cameras"  );
    mPathHandler.addPath(data_dir + "/materials");
    mPathHandler.addPath(data_dir + "/shaders"  );
    mPathHandler.addPath(data_dir + "/textures" );
    
    
}
    
MultiLoadAppBase::~MultiLoadAppBase()
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "MultiLoadAppBase::~MultiLoadAppBase() called.\n",
                         "MultiLoadAppBase::~MultiLoadAppBase() exiting.\n");
}

// Handle any initialization needed before API
void
MultiLoadAppBase::init(void)
{
    Inherited::init();      // Call base class init
    
    //Managers
    pShaderManager = new ShaderManager   (&mPathHandler              );
    pTexManager    = new TextureManager  (&mPathHandler              );
    pMatManager    = new MaterialManager (pShaderManager, pTexManager);

    //console, for remote editing
    pConsole	   = new Console         (this                       );
    
    //input
    mButtonNextScene       .init("ButtonNextScene");
    mButtonPrevScene       .init("ButtonPrevScene");
    
    mButtonToggleSceneAnim .init("ButtonToggleSceneAnim");
    mButtonRewindSceneAnim .init("ButtonRewindSceneAnim");
    
    mButtonToggleFreeCamera.init("ButtonToggleFreeCamera");
    mButtonToggleCameraAnim.init("ButtonToggleCameraAnim");
    mButtonRewindCameraAnim.init("ButtonRewindCameraAnim");
    
    //mHead.init("VJHead");   
    
}

/** Called once per context at context creation */
void
MultiLoadAppBase::contextInit(void)
{
   Inherited::contextInit();
   initGLState();
}

void
MultiLoadAppBase::bufferPreDraw(void)
{
    if(mActiveSceneOptions != NULL)
    {
        glClearColor(mActiveSceneOptions->mBackgroundColor[0],
                     mActiveSceneOptions->mBackgroundColor[1],
                     mActiveSceneOptions->mBackgroundColor[2],
                     1.0f                                     );
    
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void
MultiLoadAppBase::draw(void)
{
    if(mActiveSceneOptions != NULL)
    {
        if(mActiveSceneOptions->mRunPreCache == true)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
                << "MultiLoadAppBase::draw: PreCaching scene...\n"
                << vprDEBUG_FLUSH;
                        
            mContextData->mRenderAction->setFrustumCulling(false);
        }
        
        Inherited::draw();
        
        if(mActiveSceneOptions->mRunPreCache == true)
        {
            mActiveSceneOptions->mRunPreCache = false;
            
            mContextData->mRenderAction->setFrustumCulling   (true);
        
            vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
                << "MultiLoadAppBase::draw: PreCaching scene complete.\n"
                << vprDEBUG_FLUSH;
        }
    }
}

void
MultiLoadAppBase::preFrame(void)
{  
	Inherited::preFrame();
	
	// **************************** Cluster ********************************** /
    // This is needed on the cluster, because it is not fully in sync during
    // the first few frames.
    // If any navigation happens during that time, the nodes show misaligned
    // images
    
    //std::cout << " preFrame 1: " << std::endl;
    static unsigned int frameCount = 0;
    if(frameCount < 10)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
            << "MultiLoadAppBase::preFrame: Skipping frame [" << frameCount << "]."
            << std::endl << vprDEBUG_FLUSH;
    
        ++frameCount;
        
        return;
    }
    // *************************************************************************** /
    
    //std::cout << " preFrame 2: " << std::endl;
    mCurrTime.setNow();                                     // LOCAL TIME
//     mCurrTime = mButtonNextScene->getTimeStamp();           // CLUSTER TIME
    
    //std::cout << " preFrame 3: " << std::endl;
    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
                << "MultiLoadAppBase::preFrame: current time is " << mCurrTime.secf()
                << std::endl << vprDEBUG_FLUSH;
    updateTime(mCurrTime);
    
    //std::cout << " preFrame 5: " << std::endl;
    //*************************************************************************** /
    // switch to next scene
    if(mButtonNextScene->getData() == gadget::Digital::TOGGLE_OFF)
    {
        int nextScene = mActiveScene + 1;        
        if(static_cast<unsigned int>(nextScene) >= mSceneData.size())
            nextScene = 0;                    
        switchScene(nextScene);
    }
    
    // switch to previous scene
    if(mButtonPrevScene->getData() == gadget::Digital::TOGGLE_OFF)
    {
        int nextScene = mActiveScene - 1;    
        if(nextScene < 0)
            nextScene = mSceneData.size() - 1;            
        switchScene(nextScene);
    }
    
    // play/pause scene animation
    if(mButtonToggleSceneAnim->getData() == gadget::Digital::TOGGLE_OFF)
    {
        toggleAnimation();
    }
    
    // rewind scene animation
    if(mButtonRewindSceneAnim->getData() == gadget::Digital::TOGGLE_OFF)
    {
        rewindAnimation();
    }    
    
    // switch to/from free camera
    if(mButtonToggleFreeCamera->getData() == gadget::Digital::TOGGLE_ON)
    {     
        if(mActiveSceneData->mFreeCam == true)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
                << "MultiLoadApp::preFrame: Toggle free camera. ON TRACK\n"
                << vprDEBUG_FLUSH;
                
            mActiveSceneData->mFreeCam = false;
            mActiveSceneData->pCamManager->load(0);

            // clear the model transform - animated camera is in correct coord sys
            //OSG::beginEditCP(mActiveSceneData->pModelTrans, OSG::Transform::MatrixFieldMask);
                mActiveSceneData->pModelTrans->editMatrix().setIdentity();
            //OSG::beginEditCP(mActiveSceneData->pModelTrans, OSG::Transform::MatrixFieldMask);
             OSG::commitChanges();            
        }
        else
        {
            vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
                << "MultiLoadApp::preFrame: Toggle free camera. OFF TRACK\n"
                << vprDEBUG_FLUSH;
                
            mActiveSceneData->mFreeCam = true;
            mActiveSceneData->pCamManager->eject();

            OSG::Matrix lookAtMat;
            OSG::Matrix lookAtMatInv;
            OSG::MatrixLookAt(lookAtMat, mActiveSceneOptions->mStartPos,
            					mActiveSceneOptions->mStartPos + mActiveSceneOptions->mViewDir,
            					mActiveSceneOptions->mUpDir                                  );
            lookAtMatInv.invertFrom(lookAtMat);

            // clear the model transform - animated camera is in correct coord sys
            //OSG::beginEditCP(mActiveSceneData->pModelTrans, OSG::Transform::MatrixFieldMask);
                mActiveSceneData->pModelTrans->setMatrix(lookAtMatInv);
            //OSG::beginEditCP(mActiveSceneData->pModelTrans, OSG::Transform::MatrixFieldMask);

            OSG::commitChanges();

            OSG::Matrix adjustViewMat;
            adjustViewMat.setRotate(OSG::Quaternion(OSG::Vec3f(1.0, 0.0, 0.0), gmtl::Math::PI_OVER_2));

            //OSG::beginEditCP(mActiveSceneData->pSceneTrans, OSG::Transform::MatrixFieldMask);
                mActiveSceneData->pSceneTrans->editMatrix().multLeft(lookAtMatInv);
                mActiveSceneData->pSceneTrans->editMatrix().mult    (lookAtMat   );
                mActiveSceneData->pSceneTrans->editMatrix().multLeft(adjustViewMat);
            //OSG::endEditCP  (mActiveSceneData->pSceneTrans, OSG::Transform::MatrixFieldMask);
             OSG::commitChanges();
        }       
    }
    
    // play/pause camera animation
    if(mButtonToggleCameraAnim->getData() == gadget::Digital::TOGGLE_OFF)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
            << "MultiLoadApp::preFrame: Toggle camera anim.\n"
            << vprDEBUG_FLUSH;

        mActiveSceneData->pCamManager->play_pause(mCurrTime);
    }
    
    // rewind camera animation
    if(mButtonRewindCameraAnim->getData() == gadget::Digital::TOGGLE_OFF)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
            << "MultiLoadApp::preFrame: Rewind camera anim.\n"
            << vprDEBUG_FLUSH;
            
        mActiveSceneData->pCamManager->rewind();
    }

    /************************************************************************/
    if(mActiveSceneData != NULL)
    {
        mActiveSceneData->pBridge->update();    
        mActiveSceneData->mNavigatorAdapter.navigate();
    }

    //pConsole->processCommands();
}

void
    MultiLoadAppBase::exit(void)
{
    // delete scene options
    SceneOptionsListIt soIt  = mSceneOptions.begin();
    SceneOptionsListIt soEnd = mSceneOptions.end  ();
    
    for(; soIt != soEnd; ++soIt)
    {
        destroySceneOptions(*soIt);
    }
    
    mSceneOptions.clear();
    
    // delete scene data
    SceneDataListIt sdIt  = mSceneData.begin();
    SceneDataListIt sdEnd = mSceneData.end  ();
    
    for(; sdIt != sdEnd; ++sdIt)
    {
        destroySceneData(*sdIt);
    }
    
    mSceneData.clear();
    
    if (pShaderManager) delete pShaderManager;
    if (pTexManager   ) delete pTexManager;
    if (pMatManager   ) delete pMatManager;
    if (pConsole      ) delete pConsole;   
    pShaderManager = NULL;
    pTexManager    = NULL;
    pMatManager    = NULL;
    pConsole       = NULL;
    
    Inherited::exit();
}

void
MultiLoadAppBase::loadMaterialFiles(void)
{   
    std::vector<std::string>::const_iterator mfIt  = mMatFiles.begin();
    std::vector<std::string>::const_iterator mfEnd = mMatFiles.end  ();
    
    for(; mfIt != mfEnd; ++mfIt)
    {
        pMatManager->readFile(*mfIt);
    }
}

void
MultiLoadAppBase::loadBindingFiles(
        MaterialBinder *pMatBinder, SceneOptionsBase const *pSO)
{
    std::vector<std::string>::const_iterator bfIt  = pSO->mBindFiles.begin();
    std::vector<std::string>::const_iterator bfEnd = pSO->mBindFiles.end  ();
    
    for(; bfIt != bfEnd; ++bfIt)
    {
        pMatBinder->readFile(*bfIt);
    }
}


void 
MultiLoadAppBase::initMaterials(void){
	loadMaterialFiles();
}

void
MultiLoadAppBase::initBindings (SceneOptionsBase const *pSO, SceneDataBase *pSD){
    loadBindingFiles  (pSD->pMatBinder,  pSO);
    pSD->pObjCache->refresh();
    pSD->pMatBinder->apply(); 
}

void
MultiLoadAppBase::initCamera   (SceneOptionsBase const *pSO, SceneDataBase *pSD)
{
	loadCameraFiles   (pSD->pCamManager, pSO);
	pSD->pCamManager->init(&pSD->mNavigatorAdapter);
	pSD->pCamManager->load(0);
}

void
MultiLoadAppBase::initScene(void)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                            "MultiLoadAppBase::initScene() called.\n",
                            "MultiLoadAppBase::initScene() exiting.\n");


    /***  Init materials ***/
    initMaterials();
    
    
    SceneOptionsListConstIt soIt  = mSceneOptions.begin();
    SceneOptionsListConstIt soEnd = mSceneOptions.end  ();
    
    for(; soIt != soEnd; ++soIt)
    {
    	/***  Init Geometry and Object Cache ***/
        SceneDataBase *pSD = initScene(*soIt); //mSceneData.back();   
       
        /***  Init material Bindings ***/
        initBindings(*soIt, pSD);
        
        /***  Init scripted Camera ***/
        initCamera(*soIt, pSD);
    }
    
    /***  Init Console ***/
    //pConsole->init(); 
    
    /***  Go to first scene ***/
    switchScene(0);
}

void
    MultiLoadAppBase::switchScene(int index)
{
    // DISABLE current scene

    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "MultiLoadAppBase::switchScene: Disabling scene ["
        << mActiveScene << "].\n"
        << vprDEBUG_FLUSH;
    
    pauseAnimation();
    
    // ENABLE new scene
    
    if(index >= 0 && static_cast<unsigned int>(index) < mSceneData.size())
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadAppBase::switchScene: Enabling scene ["
            << index << "].\n"
            << vprDEBUG_FLUSH;
            
        mActiveSceneOptions = mSceneOptions.at(index);
        mActiveSceneData    = mSceneData   .at(index);
                
        mActiveScene        = index;
	
	vrj::Projection::setNearFar(
	    mActiveSceneOptions->mDepthNear, mActiveSceneOptions->mDepthFar);
	        
    }
    else
    {
        mActiveSceneOptions = NULL;
        mActiveSceneData    = NULL;
        
        mActiveScene        = -1;
    }
}

void
    MultiLoadAppBase::startAnimation(void)
{
    if(mActiveSceneData == NULL)
        return;
        
    if(mActiveSceneData->mAnimPlaying == false)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadAppBase::startAnimation: PLAY\n"
            << vprDEBUG_FLUSH;
    
        // not playing -> play
        mActiveSceneData->mAnimPlaying   = true;
        mActiveSceneData->mAnimPaused    = false;
        
        mActiveSceneData->mAnimStartTime = mCurrTime;
    }
    else if(mActiveSceneData->mAnimPaused == true)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadAppBase::startAnimation: UNPAUSE\n"
            << vprDEBUG_FLUSH;
    
        // playing but paused  -> unpause
        mActiveSceneData->mAnimPaused    =  false;
        mActiveSceneData->mAnimStartTime += 
            (mCurrTime - mActiveSceneData->mAnimTime);
    }
}

void
    MultiLoadAppBase::pauseAnimation(void)
{
    if(mActiveSceneData == NULL)
        return;
        
    if(mActiveSceneData->mAnimPlaying == true)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadAppBase::pauseAnimation: PAUSE\n"
            << vprDEBUG_FLUSH;
    
        mActiveSceneData->mAnimPaused = true;
    }
}

void
    MultiLoadAppBase::toggleAnimation(void)
{
    if(mActiveSceneData == NULL)
        return;
        
    if(mActiveSceneData->mAnimPlaying == true)
    {
        if(mActiveSceneData->mAnimPaused == true)
        {
            startAnimation();
        }
        else
        {
            pauseAnimation();
        }
    }
    else
    {
        startAnimation();
    }
}

void
    MultiLoadAppBase::stopAnimation(void)
{
    if(mActiveSceneData == NULL)
        return;
        
    if(mActiveSceneData->mAnimPlaying == true)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadAppBase::stopAnimation: STOP\n"
            << vprDEBUG_FLUSH;
    
        mActiveSceneData->mAnimPlaying = false;
        mActiveSceneData->mAnimPaused  = false;
    }
}

void
    MultiLoadAppBase::rewindAnimation(void)
{
    if(mActiveSceneData == NULL)
        return;
        
    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "MultiLoadAppBase::rewindAnimation: REWIND\n"
        << vprDEBUG_FLUSH;
        
    mActiveSceneData->mAnimStartTime = mCurrTime;
    mActiveSceneData->mAnimTime      = mCurrTime;
}

/*! Process command line arguments, calls setupArguments and handleArguments,
    which can be used to extend the set of recognized arguments.
 */
void
MultiLoadAppBase::processArguments(int argc, char *argv[])
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "MultiLoadAppBase::processArguments() called.\n",
                         "MultiLoadAppBase::processArguments() exiting.\n");

    bpo::options_description commonDesc ("common options");
    bpo::options_description cmdLineDesc("cmd line only options");
    bpo::options_description fileDesc   ("scene config file only options");
    bpo::options_description hiddenDesc ("hidden options");
   
    setupArguments(commonDesc, cmdLineDesc, fileDesc, hiddenDesc);
    
    // command line handles all options
    bpo::options_description cmdLineOpts;
    cmdLineOpts.add(commonDesc );
    cmdLineOpts.add(cmdLineDesc);
    cmdLineOpts.add(hiddenDesc );
    
    // config file handles only common and hidden options
    bpo::options_description fileOpts;
    fileOpts.add(commonDesc);
    fileOpts.add(fileDesc  );
    fileOpts.add(hiddenDesc);
        
    // description used to print the usage message - does not show hidden opts
    bpo::options_description visibleOpts;
    visibleOpts.add(commonDesc );
    visibleOpts.add(cmdLineDesc);
    visibleOpts.add(fileDesc   );
    
    // parse commandline
    bpo::variables_map vmGlobal;
    bpo::store(
        bpo::command_line_parser(argc, argv).options(cmdLineOpts).run(), vmGlobal);
    bpo::notify(vmGlobal);
        
    // special handling for help option
    if(vmGlobal.count("help"))
    {
        std::cout << visibleOpts << std::endl;
        exit();
    }
    
    // special handling for version option
    if(vmGlobal.count("version"))
    {
        std::cout << "LITE framework v1.1" << std::endl;
        exit();
    }
    
    // special handling for setup-file option
    if(vmGlobal.count("config-file"))
    {   
        std::vector<std::string> const &configFiles =
            vmGlobal["config-file"].as<std::vector<std::string> >();
            
        std::vector<std::string>::const_iterator cfIt  = configFiles.begin();
        std::vector<std::string>::const_iterator cfEnd = configFiles.end  ();
        
        for(; cfIt != cfEnd; ++cfIt)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
                << "MultiLoadAppBase::processArguments: "
                << "Reading scene configuration from ["
                << *cfIt << "].\n"
                << vprDEBUG_FLUSH;
        
            bpo::variables_map vmLocal;
            std::ifstream      setupFileStream(cfIt->c_str());
            bpo::store(bpo::parse_config_file(setupFileStream, fileOpts),
                       vmLocal                                            );
            bpo::notify(vmLocal);
            
            if(handleSceneArguments(vmLocal))
            {
                vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
                    << "MultiLoadAppBase::processArguments: "
                    << "Successfully evaluated scene configuration from ["
                    << *cfIt << "].\n"
                    << vprDEBUG_FLUSH;
            }
            else
            {
                vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
                    << "MultiLoadAppBase::processArguments: "
                    << "FAILED to evaluate scene configuration from ["
                    << *cfIt << "].\n"
                    << vprDEBUG_FLUSH;
            }
        }
    }
    
    handleGlobalArguments(vmGlobal);
}

/*! Setup the command line argument parser.
    Make sure to call the base class function when overriding.
 */
void
MultiLoadAppBase::setupArguments(
    bpo::options_description &commonDesc, bpo::options_description &cmdLineDesc,
    bpo::options_description &fileDesc,   bpo::options_description &hiddenDesc  )
{
    commonDesc.add_options()
        ("vjconfig-file", bpo::value(&mVJConfigFileNames)->composing(),
         "VRJuggler configuration file(s)");

    cmdLineDesc.add_options()
        ("help,h",     "display this help message")
        ("version,v",  "print the version string")
        ("config-file", bpo::value(&mConfigFileNames)->composing(),
         "scene configuration file(s) - one per scene");
         
    fileDesc.add_options()
        ("model-file", bpo::value<std::string>(),
         "Model file for the scene")
        ("mapping-file", bpo::value<std::string>(),
         "Mapping file to rename objects")
        ("camera-file", bpo::value<std::vector<std::string> >()->composing(),
         "Camera animation file(s)")
		("binding-file", bpo::value<std::vector<std::string> >()->composing(),
		 "Object -> Material binding file(s)")
		("material-file", bpo::value<std::vector<std::string> >()->composing(),
		 "Material description file(s)")         
        ("background-color,b",  bpo::value<OSG::Color3f>(),
         "background color")
        ("up-dir,u",      bpo::value<OSG::Vec3f>(),
         "up direction for initial camera orientation")
        ("start-pos,p",   bpo::value<OSG::Pnt3f>(),
         "initial position of the camera")
        ("view-dir",      bpo::value<OSG::Vec3f>(),
         "view direction for initial camera orientation")
        ("navigator,n",   bpo::value<std::string>(),
         "type of navigator to use")
        ("trans-scale",   bpo::value<float>(),
         "scale translations by this value to adjust movement speed.")
        ("rot-scale",     bpo::value<float>(),
         "scale rotation angles by this value to adjust movement speed.")
        ("depth-near",    bpo::value<float>(),
         "near clipping plane distance.")
        ("depth-far",     bpo::value<float>(),
         "far clipping plane distance.")
        ("pre-cache",     bpo::value<bool>(),
         "run a pre caching pass on the scene.");
}

/*! Evaluate the command line arguments that where present.
    Make sure to call the base class function when overriding.
 */
bool
    MultiLoadAppBase::handleGlobalArguments(bpo::variables_map const &vm)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "MultiLoadAppBase::handleGlobalArguments() called.\n",
                         "MultiLoadAppBase::handleGlobalArguments() exiting.\n");

    std::vector<std::string>::const_iterator vjIt  = mVJConfigFileNames.begin();   
    std::vector<std::string>::const_iterator vjEnd = mVJConfigFileNames.end  ();

    for(; vjIt != vjEnd; ++vjIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadAppBase::handleGlobalArguments: "
            << "Loading VRJuggler config file [" << *vjIt << "]\n"
            << vprDEBUG_FLUSH;
            
        vrj::Kernel::instance()->loadConfigFile(vjIt->c_str());
    }
    
    return true;
}

/*! Evaluate scene configuration file options.
    Make sure to call the base class function when overriding.
 */
bool
    MultiLoadAppBase::handleSceneArguments(bpo::variables_map const &vm)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "MultiLoadAppBase::handleSceneArguments() called.\n",
                         "MultiLoadAppBase::handleSceneArguments() exiting.\n");

    SceneOptionsBase *pSO = createSceneOptions();
    mSceneOptions.push_back(pSO);
    
    if(vm.count("model-file"))
    {
        std::string file = vm["model-file"].as<std::string>();
        std::string fullFile; 
    
        if(mPathHandler.findFile(file, fullFile))
        {
            pSO->mModelFile = fullFile;
        }
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: "
            << "No model file specified, skipping scene.\n"
            << vprDEBUG_FLUSH;
            
        mSceneOptions.pop_back();
        return false;
    }
    
    if(vm.count("mapping-file"))
    {
        std::string file = vm["mapping-file"].as<std::string>();
        std::string fullFile;
        
        if(mPathHandler.findFile(file, fullFile))
        {
            pSO->mMapFile = fullFile;
        }
    }

    if(vm.count("binding-file"))
    {
        std::vector<std::string> const &files =
            vm["binding-file"].as<std::vector<std::string> >();
            
        std::vector<std::string>::const_iterator fIt  = files.begin();
        std::vector<std::string>::const_iterator fEnd = files.end  ();
    
        for(; fIt != fEnd; ++fIt)
        {
            std::string fullFile;
            
            if(mPathHandler.findFile(*fIt, fullFile))
            {
                pSO->mBindFiles.push_back(fullFile);
            }
            else
            {
                vprDEBUG(vprDBG_ERROR, vprDBG_CRITICAL_LVL) 
                    << "MultiLoadApp::handleSceneArguments: "
                    << "Could not find binding file [" << *fIt << "]\n"
                    << vprDEBUG_FLUSH;
            }
        }
    }

    if(vm.count("material-file"))
    {
        std::vector<std::string> const &files =
            vm["material-file"].as<std::vector<std::string> >();
            
        std::vector<std::string>::const_iterator fIt  = files.begin();
        std::vector<std::string>::const_iterator fEnd = files.end  ();
    
        for(; fIt != fEnd; ++fIt)
        {
            std::string fullFile;
            
            if(mPathHandler.findFile(*fIt, fullFile))
            {
                mMatFiles.push_back(fullFile);
            }
            else
            {
                vprDEBUG(vprDBG_ERROR, vprDBG_CRITICAL_LVL) 
                    << "MultiLoadApp::handleGlobalArguments: "
                    << "Could not find material file [" << *fIt << "]\n"
                    << vprDEBUG_FLUSH;
            }
        }
    }   
       
    if(vm.count("camera-file"))
    {
        std::vector<std::string> const &files =
            vm["camera-file"].as<std::vector<std::string> >();
            
        std::vector<std::string>::const_iterator fIt  = files.begin();
        std::vector<std::string>::const_iterator fEnd = files.end  ();
        
        for(; fIt != fEnd; ++fIt)
        {
            std::string fullFile;
            
            if(mPathHandler.findFile(*fIt, fullFile))
            {
                pSO->mCamFiles.push_back(fullFile);
            }
            else
            {
                vprDEBUG(vprDBG_ERROR, vprDBG_CRITICAL_LVL) 
                    << "MultiLoadApp::handleSceneArguments: "
                    << "Could not find camera file [" << *fIt << "]\n"
                    << vprDEBUG_FLUSH;
            }
        }
    }    
    
    
    if(vm.count("background-color"))
    {
        pSO->mBackgroundColor = vm["background-color"].as<OSG::Color3f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Background color ["
            << pSO->mBackgroundColor << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("up-dir"))
    {
        pSO->mUpDir = vm["up-dir"].as<OSG::Vec3f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Up vector ["
            << pSO->mUpDir << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("start-pos"))
    {
        pSO->mStartPos = vm["start-pos"].as<OSG::Pnt3f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Start position ["
            << pSO->mStartPos << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("view-dir"))
    {
        pSO->mViewDir = vm["view-dir"].as<OSG::Vec3f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: View vector ["
            << pSO->mViewDir << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("navigator"))
    {
        pSO->mNavigatorType = vm["navigator"].as<std::string>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Navigator ["
            << pSO->mNavigatorType << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("trans-scale"))
    {
        pSO->mTransScale = vm["trans-scale"].as<float>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Translation scale ["
            << pSO->mTransScale << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("rot-scale"))
    {
        pSO->mRotScale = vm["rot-scale"].as<float>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Rotation scale ["
            << pSO->mRotScale << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("depth-near"))
    {
        pSO->mDepthNear = vm["depth-near"].as<float>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Depth near ["
            << pSO->mDepthNear << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("depth-far"))
    {
        pSO->mDepthFar = vm["depth-far"].as<float>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Depth far ["
            << pSO->mDepthFar << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("pre-cache"))
    {
        pSO->mRunPreCache = vm["pre-cache"].as<bool>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadAppBase::handleSceneArguments: Pre-cache ["
            << pSO->mRunPreCache << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    return true;
}

/*! Update time dependent aspects of the scene, e.g. animations.
 */
void
    MultiLoadAppBase::updateTime(vpr::Interval const &newTime)
{
    if(mActiveSceneData == NULL)
    	return;

    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "MultiLoadAppBase::udpateTime: newTime " << newTime.msec() << "\n"
        << vprDEBUG_FLUSH;
    
    // Navigator
    mActiveSceneData->mNavigatorAdapter.updateTime(newTime);

    // update scene animation time, if the anim is running
    if((mActiveSceneData->mAnimPlaying == true ) &&
       (mActiveSceneData->mAnimPaused  == false)   )
    {
        mActiveSceneData->mAnimTime = newTime;
    }

    // convert time elapsed time since animation started into frames
    vpr::Interval elapsedTime = 
        mActiveSceneData->mAnimTime - mActiveSceneData->mAnimStartTime;

    // @note: Assumption of 30 FPS?? 
    // @todo: May need to fix this. 
    float         frame       = 30.0f * elapsedTime.secf();
    float         numFrames   =         mActiveSceneData->pLFile->frames;
    
    if(frame >= numFrames)
    {
        if(mActiveSceneData->mAnimLoop == true)
            frame = std::fmod(frame, numFrames) + 1.0f;
        else    
            frame = numFrames;
    }
    
    // evaluate the scene status for the frame
    lib3ds_file_eval(mActiveSceneData->pLFile, frame);
    
    // Scripted camera
    mActiveSceneData->pCamManager->update(mCurrTime);
}

/** Initialize GL state. Hold over from regular OGL apps */
void
    MultiLoadAppBase::initGLState(void)
{
}

MultiLoadAppBase::SceneDataBase * 
    MultiLoadAppBase::initScene(SceneOptionsBase const *pSO)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "MultiLoadAppBase::initScene called.\n",
                         "MultiLoadAppBase::initScene exiting.\n");
                            
    SceneDataBase *pSD = createSceneData();
    mSceneData.push_back(pSD);
    
    // BEGIN SCENE CONSTRUCTION
                                                  
    // create and init scene info    
    pSD->pRootN       = OSG::Node     ::create();
    pSD->pSceneTransN = OSG::Node     ::create();
    pSD->pSceneTrans  = OSG::Transform::create();
    
    pSD->pModelTransN = OSG::Node     ::create();
    pSD->pModelTrans  = OSG::Transform::create();
    
    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "[MultiLoadAppBase::loadScene()] Loading model file [" 
        << pSO->mModelFile << "] ...\n"
        << vprDEBUG_FLUSH;
    
    // load model
    pSD->pLFile  = lib3ds_file_load(pSO->mModelFile.c_str());
    pSD->pBridge = new Lib3dsBridge();
        
    if(pSD->pLFile != NULL)         
    {
        lib3ds_file_eval(pSD->pLFile, 1.0);
    
        pSD->pBridge->setLib3dsFile  (pSD->pLFile  );
        pSD->pBridge->readNameMapFile(pSO->mMapFile);
        pSD->pBridge->construct      (             );
        pSD->pBridge->update         (             );
        
        pSD->pModelN      = pSD->pBridge->getRoot();
            
        pSD->pModelTransN = OSG::Node     ::create();
        pSD->pModelTrans  = OSG::Transform::create();
        
        //OSG::beginEditCP(pSD->pModelTransN);
            pSD->pModelTransN->setCore (pSD->pModelTrans);
            pSD->pModelTransN->addChild(pSD->pModelN    );
        //OSG::endEditCP  (pSD->pModelTransN);
        
         OSG::commitChanges();
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "[MultiLoadAppBase::loadScene()] Loading [" << pSO->mModelFile 
            << "] complete.\n" << vprDEBUG_FLUSH;
    }
    else
    {
       vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "[MultiLoadAppBase::loadScene()] Loading [" << pSO->mModelFile
            << "] failed.\n" << vprDEBUG_FLUSH;
    }
    
    OSG::setName(pSD->pModelN,      "_internal_mModelN"     );
    OSG::setName(pSD->pModelTransN, "_internal_mModelTransN");
    
    // create a OpenGL light
    
    // BEGIN Light 0
    OSG::NodeRefPtr             pLight0N      (OSG::Node::create()            );
    OSG::DirectionalLightRefPtr pLight0       (OSG::DirectionalLight::create());
    //OSG::NodeRefPtr             pLight0BeaconN(OSG::Node::create()            );
    //OSG::TransformRefPtr        pLight0Beacon (OSG::Transform::create()       );

    pSD->pLight0BeaconN = OSG::NodeRefPtr( OSG::Node::create() );
    pSD->pLight0Beacon  = OSG::TransformRefPtr( OSG::Transform::create() );
  
    OSG::Matrix light0Pos;
    light0Pos.setTranslate(OSG::Vec3f(0.0f, 10.0f, 0.0f));
    
    //OSG::beginEditCP(pLight0Beacon, OSG::Transform::MatrixFieldMask);
        pSD->pLight0Beacon->setMatrix(light0Pos);
    //OSG::endEditCP(pLight0Beacon, OSG::Transform::MatrixFieldMask);
    OSG::commitChanges();
    //OSG::beginEditCP(pLight0BeaconN, OSG::Node::CoreFieldMask);
        pSD->pLight0BeaconN->setCore(pSD->pLight0Beacon);
    //OSG::endEditCP(pLight0BeaconN, OSG::Node::CoreFieldMask);
    OSG::commitChanges();
    //OSG::beginEditCP(pLight0N);
        pLight0N->setCore(pLight0);
    //OSG::endEditCP(pLight0N);
    OSG::commitChanges();
    
    //OSG::beginEditCP(pLight0N);
        pLight0->setAmbient  ( 0.5f,  0.5f,  0.5f,  1.0f);
        pLight0->setDiffuse  ( 0.3f,  0.3f,  0.3f,  1.0f);
        pLight0->setSpecular ( 0.5f,  0.5f,  0.5f,  1.0f);
        pLight0->setDirection( 0.0f,  0.5f,  0.5f       );
        pLight0->setBeacon   (pSD->pLight0BeaconN            );
    //OSG::endEditCP(pLight0N);
    OSG::commitChanges();

    OSG::setName(pLight0N,       "_internal_pLight0N"      );
    OSG::setName(pSD->pLight0BeaconN, "_internal_pLight0BeaconN");
    

    // END Light 0
    
    // assemble scene
    //OSG::beginEditCP(pSD->pSceneTransN);
        pSD->pSceneTransN->setCore (pSD->pSceneTrans);
        pSD->pSceneTransN->addChild(pLight0N        );       
    //OSG::endEditCP(pSD->pSceneTransN);
    OSG::commitChanges();
       
    //OSG::beginEditCP(pSD->pRootN);
        pSD->pRootN->setCore (OSG::Group::create());
        pSD->pRootN->addChild(pSD->pSceneTransN   );
    //OSG::endEditCP  (pSD->pRootN);
    OSG::commitChanges();

    //OSG::beginEditCP(pLight0N);
        pLight0N->addChild(pSD->pModelTransN);
    //OSG::endEditCP  (pLight0N);
    OSG::commitChanges();

    // adjust model to match initial position and view
    OSG::Matrix lookAtMatInv;
    OSG::MatrixLookAt(lookAtMatInv, pSO->mStartPos,
                                    pSO->mStartPos + pSO->mViewDir,
                                    pSO->mUpDir                    );
    lookAtMatInv.invert();
    
    
     OSG::commitChanges();
    // END SCENE CONSTRUCTION
    
    pSD->pNavigator = createNavigator(pSO->mNavigatorType);
    pSD->pNavigator->setTranslateFactor(pSO->mTransScale);
    pSD->pNavigator->setRotateFactor   (pSO->mRotScale  );    
    
    pSD->mNavigatorAdapter.setNavigator(pSD->pNavigator );
    pSD->mNavigatorAdapter.setTransform(pSD->pSceneTrans);
    
    pSD->mNavigatorAdapter.initialize();
    
    //set Object Cache
    pSD->pObjCache->setRoot(pSD->pRootN);  
    

    return pSD;
}

NavigatorBase *
    MultiLoadAppBase::createNavigator(std::string const &navigatorType)
{
    NavigatorBase *pNavigator = NULL;

    if(navigatorType == "GamepadNavigator")
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
            << "MultiLoadAppBase::createNavigator: Creating GamepadNavigator.\n"
            << vprDEBUG_FLUSH;

        pNavigator = new GamepadNavigator(this);
    }
    else if(navigatorType == "WandNavigator")
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
            << "MultiLoadAppBase::createNavigator: Creating WandNavigator.\n"
            << vprDEBUG_FLUSH;

        pNavigator = new WandNavigator(this);
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
            << "MultiLoadAppBase::createNavigator: Invalid navigator type: " << navigatorType << std::endl
            << vprDEBUG_FLUSH;
    }
    
    return pNavigator;
}




void 
	MultiLoadAppBase::refreshMaterials(void)
{
	loadMaterialFiles();
	pMatManager->refreshCache();
}

void 
	MultiLoadAppBase::refreshTextures(void)
{	
	pTexManager->refreshCache();
}

void
	MultiLoadAppBase::loadCameraFiles(
        CameraManager *pCamManager, SceneOptionsBase const *pSO)
{
    std::vector<std::string>::const_iterator cfIt  = pSO->mCamFiles.begin();
    std::vector<std::string>::const_iterator cfEnd = pSO->mCamFiles.end  ();
    
    for(; cfIt != cfEnd; ++cfIt)
    {
        pCamManager->readFile(*cfIt);
    }
}

