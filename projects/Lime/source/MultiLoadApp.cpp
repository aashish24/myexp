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
 * File:          MultiLoadApp.cpp,v
 * Date modified: 2005/08/11 02:38:32
 * Version:       1.19.2.1
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <iostream>
#include <cstdlib>
#include <string>

#include <MultiLoadApp.h>
#include <CameraManager.h>
#include <ExtrusionManager.h>
#include <MaterialBinder.h>
#include <MaterialManager.h>
#include <NamedObjectCache.h>
#include <ObjectRenamer.h>
#include <SceneGraphPrinter.h>
#include <Console.h>


/*==========================================================================*/
/* MultiLoadApp::SceneOptions                                                  */
/*==========================================================================*/

    MultiLoadApp::SceneOptions::SceneOptions(void)    
    : Inherited (),
      mExtFiles (),
      
      mWaterLevel         (0.0),
      mFogNearAbove       (0.0),
      mFogFarAbove        (1000.0),
      mFogNearColorAbove  (0.0, 0.0, 0.0, 1.0),
      mFogFarColorAbove   (0.0, 0.0, 0.0, 1.0),
      mKeyColorAbove      (0.0, 0.0, 0.0, 1.0),
      mAntiColorAbove     (0.0, 0.0, 0.0, 1.0),
      mSpecularFactorAbove(0.0),
      mFogNearBelow       (0.0),
      mFogFarBelow        (1000.0),
      mFogNearColorBelow  (0.0, 0.0, 0.0, 1.0),
      mFogFarColorBelow   (0.0, 0.0, 0.0, 1.0),
      mKeyColorBelow      (0.0, 0.0, 0.0, 1.0),
      mAntiColorBelow     (0.0, 0.0, 0.0, 1.0),
      mSpecularFactorBelow(0.0)
{
    // nothing to do    	
}

    MultiLoadApp::SceneOptions::~SceneOptions(void)
{
    // nothing to do
}

/*==========================================================================*/
/* MultiLoadApp::SceneData                                                     */
/*==========================================================================*/

    MultiLoadApp::SceneData::SceneData(MaterialManager const *pMatManager)
    
    : Inherited     ( pMatManager ),      
      pExtManager   (new ExtrusionManager()),
      mModeIndex    (MI_UNDEFINED)
{
    pExtManager ->setObjCache  (pObjCache  );    
}

    MultiLoadApp::SceneData::~SceneData(void)
{       	
    if (pExtManager) delete pExtManager;
    pExtManager    = NULL;
 }

/*==========================================================================*/
/* MultiLoadApp                                                                */
/*==========================================================================*/

MultiLoadApp::MultiLoadApp(vrj::Kernel* kern)
    : Inherited      (kern),
      mFrameTime     (),
      mDeltaFrameTime()
{
}


MultiLoadApp::~MultiLoadApp()
{
}



MultiLoadApp::SceneDataBase  *
	MultiLoadApp::initScene    (SceneOptionsBase const *pSOB)
{
    const SceneOptions *pSO = dcastOptions(pSOB                      );
          SceneData    *pSD = dcastData   (Inherited::initScene(pSOB));
     
    loadExtrusionFiles(pSD->pExtManager, pSO);
    pSD->pExtManager->apply ();
    pSD->pExtManager->update();
    
    return pSD;
}


/*===========================================================================*/
/* VRJuggler Callbacks                                                       */
/*===========================================================================*/
void 
    MultiLoadApp::preFrame(void)
{
    Inherited::preFrame();    
    
    updateDynamicParams();

    editSceneData()->pExtManager->update();    
}

void
    MultiLoadApp::init(void)
{
    Inherited::init();
    
    mAppStartTime.setNow();                             // LOCAL TIME
//     mAppStartTime = mButtonNextScene->getTimeStamp();   // CLUSTER TIME
}

void
    MultiLoadApp::exit(void)
{
    Inherited::exit();
}

void
    MultiLoadApp::switchScene(int index)
{
    Inherited::switchScene(index);
    
    SceneData *pSD = dynamic_cast<SceneData *>(mActiveSceneData);
    
    if(pSD != NULL)
    {
        pSD->mModeIndex = MI_UNDEFINED;
    }
}

/*===========================================================================*/
/* Commandline Arguments                                                     */

/*! Add arguments to be recognized on the command line or in the
    per scene config files.
 */
void
    MultiLoadApp::setupArguments(bpo::options_description &commonDesc,
                              bpo::options_description &cmdLineDesc,
                              bpo::options_description &fileDesc,
                              bpo::options_description &hiddenDesc  )
{
    Inherited::setupArguments(commonDesc, cmdLineDesc, fileDesc, hiddenDesc);
    
    fileDesc.add_options()
        ("extrusion-file", bpo::value<std::vector<std::string> >()->composing(),
         "Extrusion description file(s)")
        ("water-level",           bpo::value<OSG::Real32>(), "Water level to switch between above/below parameter sets")
        ("fog-near-above",        bpo::value<OSG::Real32>(), "Fog near plane distance above water")
        ("fog-far-above",         bpo::value<OSG::Real32>(), "Fog far plane distance above water")
        ("fog-near-color-above",  bpo::value<OSG::Vec4f>(), "Fog near color above water")
        ("fog-far-color-above",   bpo::value<OSG::Vec4f>(), "Fog far color above water")
        ("key-color-above",       bpo::value<OSG::Vec4f>(), "Key color above water")
        ("anti-color-above",      bpo::value<OSG::Vec4f>(), "Anti color above water")
        ("specular-factor-above", bpo::value<OSG::Real32>(), "Specular factor above water")
        ("fog-near-below",        bpo::value<OSG::Real32>(), "Fog near plane distance below water")
        ("fog-far-below",         bpo::value<OSG::Real32>(), "Fog far plane distance below water")
        ("fog-near-color-below",  bpo::value<OSG::Vec4f>(), "Fog near color below water")
        ("fog-far-color-below",   bpo::value<OSG::Vec4f>(), "Fog far color below water")
        ("key-color-below",       bpo::value<OSG::Vec4f>(), "Key color below water")
        ("anti-color-below",      bpo::value<OSG::Vec4f>(), "Anti color below water")
        ("specular-factor-below", bpo::value<OSG::Real32>(), "Specular factor below water")
        ;
}


bool
    MultiLoadApp::handleSceneArguments(bpo::variables_map const &vm)
{
    if(!Inherited::handleSceneArguments(vm))
        return false;
    
    
    SceneOptionsBase *pSOB = mSceneOptions.back();
    SceneOptions     *pSO  = dynamic_cast<SceneOptions *>(pSOB);
        
    if(vm.count("extrusion-file"))
    {
        std::vector<std::string> const &files =
            vm["extrusion-file"].as<std::vector<std::string> >();
            
        std::vector<std::string>::const_iterator fIt  = files.begin();
        std::vector<std::string>::const_iterator fEnd = files.end  ();
    
        for(; fIt != fEnd; ++fIt)
        {
            std::string fullFile;
            
            if(mPathHandler.findFile(*fIt, fullFile))
            {
                pSO->mExtFiles.push_back(fullFile);
            }
            else
            {
                vprDEBUG(vprDBG_ERROR, vprDBG_CRITICAL_LVL) 
                    << "MultiLoadApp::handleSceneArguments: "
                    << "Could not find extrusion file [" << *fIt << "]\n"
                    << vprDEBUG_FLUSH;
            }
        }
    }
    
    if(vm.count("water-level"))
    {
        pSO->mWaterLevel = vm["water-level"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Water level ["
            << pSO->mWaterLevel << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-near-above"))
    {
        pSO->mFogNearAbove = vm["fog-near-above"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog near plane (above) ["
            << pSO->mFogNearAbove << "].\n"
            << vprDEBUG_FLUSH;
    }

    if(vm.count("fog-far-above"))
    {
        pSO->mFogFarAbove = vm["fog-far-above"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog far plane (above) ["
            << pSO->mFogFarAbove << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-near-color-above"))
    {
        pSO->mFogNearColorAbove = vm["fog-near-color-above"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog near color (above) ["
            << pSO->mFogNearColorAbove << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-far-color-above"))
    {
        pSO->mFogFarColorAbove = vm["fog-far-color-above"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog far color (above) ["
            << pSO->mFogFarColorAbove << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("key-color-above"))
    {
        pSO->mKeyColorAbove = vm["key-color-above"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Key color (above) ["
            << pSO->mKeyColorAbove << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("anti-color-above"))
    {
        pSO->mAntiColorAbove = vm["anti-color-above"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Anti color (above) ["
            << pSO->mAntiColorAbove << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("specular-factor-above"))
    {
        pSO->mSpecularFactorAbove = vm["specular-factor-above"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Specular factor (above) ["
            << pSO->mSpecularFactorAbove << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-near-below"))
    {
        pSO->mFogNearBelow = vm["fog-near-below"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog near plane (below) ["
            << pSO->mFogNearBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-far-below"))
    {
        pSO->mFogFarBelow = vm["fog-far-below"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog far plane (below) ["
            << pSO->mFogFarBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-near-color-below"))
    {
        pSO->mFogNearColorBelow = vm["fog-near-color-below"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog near color (below) ["
            << pSO->mFogNearColorBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("fog-far-color-below"))
    {
        pSO->mFogFarColorBelow = vm["fog-far-color-below"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Fog far color (below) ["
            << pSO->mFogFarColorBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("key-color-below"))
    {
        pSO->mKeyColorBelow = vm["key-color-below"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Key color (below) ["
            << pSO->mKeyColorBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("anti-color-below"))
    {
        pSO->mAntiColorBelow = vm["anti-color-below"].as<OSG::Vec4f>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Anti color (below) ["
            << pSO->mAntiColorBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(vm.count("specular-factor-below"))
    {
        pSO->mSpecularFactorBelow = vm["specular-factor-below"].as<OSG::Real32>();
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MultiLoadApp::handleSceneArguments: Specular factor (below) ["
            << pSO->mSpecularFactorBelow << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    return true;
}

void
    MultiLoadApp::updateTime(vpr::Interval const &newTime)
{
    Inherited::updateTime(newTime);
    
    mDeltaFrameTime = (newTime - mAppStartTime - mFrameTime);
    mFrameTime      = newTime - mAppStartTime;
    
    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL) 
        << "MultiLoadApp::updateTime: frameTime "      << mFrameTime.secf() << "\n"
        << "MultiLoadApp::updateTime: deltaFrameTime " << mDeltaFrameTime.secf()
        << std::endl << vprDEBUG_FLUSH;
}

void
    MultiLoadApp::updateDynamicParams(void)
{
    if(mActiveSceneData == NULL)
        return;
    
    float         height;
    SceneOptions *pSO    = dynamic_cast<SceneOptions *>(mActiveSceneOptions);
    SceneData    *pSD    = dynamic_cast<SceneData    *>(mActiveSceneData   );
    
    if(pSD->mFreeCam == true)
    {
        OSG::Pnt3f p(0.0, 0.0, 0.0);
        OSG::Matrix mS = pSD->pSceneTrans->getMatrix();
        OSG::Matrix mM = pSD->pModelTrans->getMatrix();
    
        mM.mult(mS);
        mM.invert();
        mM.mult(p);
            
        height = p[1];
    }
    else
    {
        OSG::Pnt3f p(0.0, 0.0, 0.0);
        OSG::Matrix mS = pSD->pSceneTrans->getMatrix();
        OSG::Matrix mM = pSD->pModelTrans->getMatrix();
        
        mM.mult(mS);
        mM.invert();
        mM.mult(p);
                
        height = p[2];
    }
    
    if(height > pSO->mWaterLevel && pSD->mModeIndex != MI_ABOVE)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadApp::updateDynamicParams: Enabling ABOVE parameter set.\n"
            << vprDEBUG_FLUSH;
        
        pSD->mModeIndex = MI_ABOVE;
        
        editSceneOptions()->mBackgroundColor[0] = pSO->mFogFarColorAbove[0];
        editSceneOptions()->mBackgroundColor[1] = pSO->mFogFarColorAbove[1];
        editSceneOptions()->mBackgroundColor[2] = pSO->mFogFarColorAbove[2];
        
        pMatManager->setDynamicParam("keyColor",     pSO->mKeyColorAbove      );
        pMatManager->setDynamicParam("antiColor",    pSO->mAntiColorAbove     );
        pMatManager->setDynamicParam("gSpec",        pSO->mSpecularFactorAbove);
        pMatManager->setDynamicParam("fogNearColor", pSO->mFogNearColorAbove  );
        pMatManager->setDynamicParam("fogFarColor",  pSO->mFogFarColorAbove   );
        pMatManager->setDynamicParam("fogNear",      pSO->mFogNearAbove       );
        pMatManager->setDynamicParam("fogFar",       pSO->mFogFarAbove        );
    }
    else if(height <= pSO->mWaterLevel && pSD->mModeIndex != MI_BELOW)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MultiLoadApp::updateDynamicParams: Enabling BELOW parameter set.\n"
            << vprDEBUG_FLUSH;
        
        pSD->mModeIndex = MI_BELOW;
        
        editSceneOptions()->mBackgroundColor[0] = pSO->mFogFarColorBelow[0];
        editSceneOptions()->mBackgroundColor[1] = pSO->mFogFarColorBelow[1];
        editSceneOptions()->mBackgroundColor[2] = pSO->mFogFarColorBelow[2];
        
        pMatManager->setDynamicParam("keyColor",     pSO->mKeyColorBelow      );
        pMatManager->setDynamicParam("antiColor",    pSO->mAntiColorBelow     );
        pMatManager->setDynamicParam("gSpec",        pSO->mSpecularFactorBelow);
        pMatManager->setDynamicParam("fogNearColor", pSO->mFogNearColorBelow  );
        pMatManager->setDynamicParam("fogFarColor",  pSO->mFogFarColorBelow   );
        pMatManager->setDynamicParam("fogNear",      pSO->mFogNearBelow       );
        pMatManager->setDynamicParam("fogFar",       pSO->mFogFarBelow        );
    }
    
    if(pSD->mAnimPlaying && !pSD->mAnimPaused)
    {
        // convert time elapsed time since animation started into frames
        vpr::Interval elapsedTime = pSD->mAnimTime - pSD->mAnimStartTime;
        float         frame       = 30.0f * elapsedTime.secf();
        float         numFrames   =         pSD->pLFile->frames;
    
        if(frame >= numFrames)
        {
            if(mActiveSceneData->mAnimLoop == true)
                frame = std::fmod(frame, numFrames) + 1.0f;
            else    
                frame = numFrames;
        }
        
        float animTime = frame / numFrames;
        
        pMatManager->setDynamicParam("animTime", animTime);
    }
    
    pMatManager->setDynamicParam("frameTime",      mFrameTime     .secf());
    pMatManager->setDynamicParam("deltaFrameTime", mDeltaFrameTime.secf());
}

void
    MultiLoadApp::loadExtrusionFiles(
        ExtrusionManager *pExtManager, SceneOptions const *pSO)
{
    std::vector<std::string>::const_iterator efIt  = pSO->mExtFiles.begin();
    std::vector<std::string>::const_iterator efEnd = pSO->mExtFiles.end  ();
    
    for(; efIt != efEnd; ++efIt)
    {
        pExtManager->readFile(*efIt);
    }
}





