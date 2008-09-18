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
 * File:          MultiLoadApp.h,v
 * Date modified: 2005/05/13 14:30:50
 * Version:       1.16
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _MULTILOADAPPBASE_H_
#define _MULTILOADAPPBASE_H_

#include <iostream>
#include <iomanip>
/*-----------------------------Juggler includes-------------------------------*/
#include <vrj/vrjConfig.h>
#include "OpenSG2App.h"
//#include <vrj/Draw/OpenSG/OpenSGApp.h>
#include <vrj/Draw/OGL/GlContextData.h>
#include <vrj/Kernel/Kernel.h>
#include <vrj/Display/Projection.h>
#include <vrj/Display/CameraProjection.h>
/*-----------------------------GMTL includes-------------------------------*/
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/Coord.h>
#include <gmtl/Xforms.h>
/*-----------------------------OpenSG includes--------------------------------*/
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGLight.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGSimpleAttachments.h>
/*------------------------------Boost includes--------------------------------*/
#include <boost/program_options.hpp>
namespace bpo = boost::program_options;
/*------------------------------ lib3ds includes -----------------------------*/
#include <lib3ds/file.h>
/*----------------------------------------------------------------------------*/
#include "NavigatorBase.h"
#include "OpenSGNavigatorAdapter.h"
#include "PathHandler.h"
#include "Lib3dsBridge.h"
#include "MaterialManager.h"
#include "MaterialBinder.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "NamedObjectCache.h"
#include "CameraManager.h"
#include "Console.h"


/*! ==============================================================================
 *  MultiLoadAppBase is the base application class to load multiple scenes 
 *  and switch among them.  It also provides a console to allow runtime editing  
 *  
 *  Scenes are loaded through configuration (.cfg) files with the following parameters:
 *      model-file	    = <.3ds file>  
 *      mapping-file	= <.map file>  
 *      camera-file     = <.cam file>
 *      binding-file	= <.txt file>
 *      material-file   = <.txt file>
 *      navigator	    = <GamepadNavigator or WandNavigator>
 *      trans-scale     = <float>
 *      rot-scale       = <float>
 *      up-dir		    = <floatvector>
 *      view-dir	    = <floatvector>
 *      depth-near	    = <float>
 *      depth-far	    = <float>
 *      background-color= <floatvector> 
 *      pre-cache	    = <bool>
 * 
 *  Derived App classes can add new parameters to the .cfg file or 
 *  command line.
 *  ===========================================================================
 */
class MultiLoadAppBase : public vrj::OpenSG2App
{
  public:
    typedef vrj::OpenSG2App   Inherited;
    typedef MultiLoadAppBase  Self;
    
    /*=======================================================================*/
    /* Per scene data structures                                             */
    /*=======================================================================*/
    
    /*! Per scene options (read from configuration file).
        To extend in a derived class, override createSceneOptions,
        destroySceneOptions functions.
     */
    struct SceneOptionsBase
    {
    			 SceneOptionsBase(void);
        virtual ~SceneOptionsBase(void);
    
        std::string  mModelFile;        /*!< Filename of scene model */
        std::string  mMapFile;          /*!< Filename storing mapping information (short name in .3ds file <--> long name in materials file) */
        
        std::vector<std::string>  mBindFiles;
        std::vector<std::string>  mCamFiles;
        
        std::string  mNavigatorType;
        
        OSG::Color3f mBackgroundColor;  /*!< Color of window background */
        OSG::Vec3f   mUpDir;            /*!< Initial up direction */
        OSG::Pnt3f   mStartPos;         /*!< Initial position */
        OSG::Vec3f   mViewDir;          /*!< Initial view direction */
        
        float        mTransScale;       /*!< Scale translation speed */
        float        mRotScale;         /*!< Scale rotation speed */
        
        float        mDepthNear;        /*!< Near clipping plane */
        float        mDepthFar;         /*!< Far clipping plane */
        
        bool         mRunPreCache;      /*!< Run pass to validate/create all GL objects */
    };
    
    typedef std::vector<SceneOptionsBase *>   SceneOptionsList;
    typedef SceneOptionsList::iterator        SceneOptionsListIt;
    typedef SceneOptionsList::const_iterator  SceneOptionsListConstIt;
    
    /*! Per scene data.
        To extend in a derived class, override createSceneData,
        destroySceneData functions.
     */
    struct SceneDataBase
    {
                 SceneDataBase(MaterialManager const *pMatManager);
        virtual ~SceneDataBase(void);
    
        // OpenSG scene elements
        OSG::NodeRefPtr         pRootN;
        
        OSG::NodeRefPtr         pSceneTransN;
        OSG::TransformRefPtr    pSceneTrans;
    
        OSG::NodeRefPtr         pModelTransN;
        OSG::TransformRefPtr    pModelTrans;
    
        OSG::NodeRefPtr         pModelN;
    
        // Lib3ds scene elements and connection to OpenSG
        Lib3dsFile             *pLFile;
        Lib3dsBridge           *pBridge;
        
        // Free fly navigator
        NavigatorBase          *pNavigator;
        OpenSGNavigatorAdapter  mNavigatorAdapter;
        
        // 
        NamedObjectCache       *pObjCache;
        MaterialBinder         *pMatBinder;
        
        //Scripted camera
        CameraManager          *pCamManager;
        bool                    mFreeCam;
        
        // Animation data
        vpr::Interval           mAnimStartTime;
        vpr::Interval           mAnimTime;
        bool                    mAnimPlaying;
        bool                    mAnimPaused;
        bool                    mAnimLoop;
    };
    
    typedef std::vector<SceneDataBase *>   SceneDataList;
    typedef SceneDataList::iterator        SceneDataListIt;
    typedef SceneDataList::const_iterator  SceneDataListConstIt;
    
    void loadBindingFiles  (MaterialBinder     *pMatBinder,
    						SceneOptionsBase const *pSO         );
    void loadCameraFiles   (CameraManager      *pCamManager, 
    						SceneOptionsBase const *pSO         );
    
    /*=======================================================================*/
    /* Constructors/Destructor                                               */
    /*=======================================================================*/
    
             MultiLoadAppBase(vrj::Kernel* kern);
    virtual ~MultiLoadAppBase(void             );
    
    /*=======================================================================*/
    /* VRJuggler Callbacks                                                   */
    /*=======================================================================*/
    
    virtual void init(void);    
    virtual void initScene(void);    
    virtual void bufferPreDraw(void);    
    virtual void draw(void);    
    virtual void contextInit(void);    
    virtual void preFrame(void);    
    virtual void exit(void);
    
    /*=======================================================================*/
    /* Scene Handling                                                        */
    /*=======================================================================*/
    
    virtual OSG::Node*      getScene    (void);
    virtual OSG::NodeRefPtr getModelNode(void) const;
    
    virtual void         switchScene (int index);
    
    void startAnimation (void);
    void pauseAnimation (void);
    void toggleAnimation(void);
    void stopAnimation  (void);
    void rewindAnimation(void);
    
    /*=======================================================================*/
    /* Commandline Arguments                                                 */
    /*=======================================================================*/
    
            void processArguments     (int argc, char *argv[]);
    
    virtual void setupArguments       (bpo::options_description &commonDesc,
                                       bpo::options_description &cmdLineDesc,
                                       bpo::options_description &fileDesc,
                                       bpo::options_description &hiddenDesc  );
    virtual bool handleGlobalArguments(bpo::variables_map const &vm          );
    virtual bool handleSceneArguments (bpo::variables_map const &vm          );
            

    /*=======================================================================*/
    /* Access                                                                */
    /*=======================================================================*/    
    MaterialManager const *getMaterialManager (void) const;
    MaterialManager       *editMaterialManager(void);
    
    ShaderManager const   *getShaderManager   (void) const;
    ShaderManager         *editShaderManager  (void);    
    
    TextureManager const  *getTextureManager  (void) const;
    TextureManager        *editTextureManager (void);

    PathHandler const     &getPathHandler (void) const;
    PathHandler           &editPathHandler(void);

    /*=======================================================================*/
    /* Edit                                                                  */
    /*=======================================================================*/
    void refreshMaterials();
    void refreshTextures ();
    //void refreshBindings ();
        
    
  protected:
   /*=======================================================================*/
   /* Initialization                                                        */
   /*    Every component separately, called by initScene in the order below */
   /*    The idea is that each one is independent, child classes can        */
   /*    modify any                                                         */
   /*=======================================================================*/    
    //Materials    
    virtual void              initMaterials(void);
    //Geometry and object cache
    virtual SceneDataBase    *initScene    (SceneOptionsBase const *pSO );
    //Material Bindings
    virtual void              initBindings (SceneOptionsBase const *pSO,
                                            SceneDataBase          *pSD );
    //Scripted Camera
    virtual void              initCamera   (SceneOptionsBase const *pSO,
                                            SceneDataBase          *pSD );
    
    /*=======================================================================*/
    /* Per scene data structures                                             */
    /*=======================================================================*/ 
    virtual SceneOptionsBase *createSceneOptions (void                 );
    virtual void              destroySceneOptions(SceneOptionsBase *pSO);
  
    virtual SceneDataBase    *createSceneData    (void                 );
    virtual void              destroySceneData   (SceneDataBase    *pSD);
       
    virtual void initGLState(void);
      
    NavigatorBase *createNavigator(std::string const &navigatorType);

    /*=======================================================================*/
    /* Global data structures                                                */
    /*=======================================================================*/    
    std::vector<std::string>           mConfigFileNames;
    std::vector<std::string>           mVJConfigFileNames;
    
    PathHandler                        mPathHandler;
    ShaderManager                     *pShaderManager;
    TextureManager                    *pTexManager;
    std::vector<std::string>           mMatFiles;
    MaterialManager        		        *pMatManager;   
 
    SceneOptionsList                   mSceneOptions;    
    SceneDataList                      mSceneData;

    vpr::Interval                      mCurrTime;
    virtual void updateTime (vpr::Interval    const &newTime);
    
    void loadMaterialFiles (void                            );
    
    gadget::DigitalInterface  mButtonNextScene;
    gadget::DigitalInterface  mButtonPrevScene;
    
    gadget::DigitalInterface  mButtonToggleSceneAnim;
    gadget::DigitalInterface  mButtonRewindSceneAnim;
    
    gadget::DigitalInterface  mButtonToggleFreeCamera;
    gadget::DigitalInterface  mButtonToggleCameraAnim;
    gadget::DigitalInterface  mButtonRewindCameraAnim;    
    
    gadget::PositionInterface mHead;
     
    
    /*=======================================================================*/
    /* Currently active scene                                                */
    /*=======================================================================*/
    int                                mActiveScene;        
    SceneOptionsBase                  *mActiveSceneOptions;
    SceneDataBase                     *mActiveSceneData;
    
    /*=======================================================================*/
    /* Remote edit                                                           */
    /*=======================================================================*/    
    Console					 *pConsole;
    
};




/*! Returns the root of the active scene, or OSG::NullFC
 */
inline OSG::Node*
    MultiLoadAppBase::getScene(void)
{
    OSG::NodeRefPtr pScene;
    
    if(mActiveSceneData != NULL)
        pScene = mActiveSceneData->pRootN;
    
    return pScene.get();
}

/*! Returns the root of the model for the active scene, or OSG::NullFC
 */
inline OSG::NodeRefPtr
    MultiLoadAppBase::getModelNode(void) const
{
    OSG::NodeRefPtr pModel;
    
    if(mActiveSceneData != NULL)
        pModel = mActiveSceneData->pModelN;
        
    return pModel;
}

/*! Create new per scene options instance
 */
inline MultiLoadAppBase::SceneOptionsBase *
    MultiLoadAppBase::createSceneOptions(void)
{
    return new SceneOptionsBase();
}

/*! Destroy per scene options instance
 */
inline void
    MultiLoadAppBase::destroySceneOptions(SceneOptionsBase *pSO)
{
    delete pSO;
}

/*! Create new per scene data instance
 */
inline MultiLoadAppBase::SceneDataBase *
    MultiLoadAppBase::createSceneData(void)
{
    return new SceneDataBase(pMatManager);
}

/*! Destroy per scene data instance
 */
inline void
    MultiLoadAppBase::destroySceneData(SceneDataBase *pSD)
{
    delete pSD;
}

inline MaterialManager const *
	MultiLoadAppBase::getMaterialManager(void) const
{
    return pMatManager;
}

inline MaterialManager *
	MultiLoadAppBase::editMaterialManager(void)
{
    return pMatManager;
}

inline ShaderManager const *
	MultiLoadAppBase::getShaderManager(void) const
{
    return pShaderManager;
}

inline ShaderManager *
	MultiLoadAppBase::editShaderManager(void)
{
    return pShaderManager;
}

inline TextureManager const *
	MultiLoadAppBase::getTextureManager(void) const
{
    return pTexManager;
}

inline TextureManager *
	MultiLoadAppBase::editTextureManager(void)
{
    return pTexManager;
}

inline PathHandler const &
	MultiLoadAppBase::getPathHandler(void) const
{
    return mPathHandler;
}

inline PathHandler &
	MultiLoadAppBase::editPathHandler(void)
{
    return mPathHandler;
}


#endif // _MULTILOADAPPBASE_H_
