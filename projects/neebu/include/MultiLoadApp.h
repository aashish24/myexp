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

#ifndef _MULTILOADAPP__H_
#define _MULTILOADAPP__H_

#include <MultiLoadAppBase.h>
#include <PathHandler.h>


#include <gadget/Type/Digital.h>
#include <gadget/Type/DigitalInterface.h>
#include <gadget/Type/DigitalData.h>
#include <gadget/Type/DigitalProxy.h>

// foward declarations
class CameraManager;
class ExtrusionManager;
class MaterialBinder;
class MaterialManager;
class NamedObjectCache;
class ObjectRenamer;
class ShaderManager;
class TextureManager;
class Console;


/*! ==============================================================================
 *  MultiLoadApp is a child class that implements specific
 *  functionality or extends the base application class.
 *  In this case, MultiLoadApp handles the extrusion files and underwater 
 *  rendering for the OTC project. 
 *  
 *  ===========================================================================
 */

class MultiLoadApp : public MultiLoadAppBase
{
  public:
    typedef MultiLoadAppBase Inherited;
    typedef MultiLoadApp     Self;
      
             MultiLoadApp(vrj::Kernel* kern);
    virtual ~MultiLoadApp(void             );   
    
    /*=======================================================================*/
    /* VRJuggler Callbacks                                                   */
    /*=======================================================================*/
              
    virtual void preFrame(void);
    
    virtual void init(void);
    virtual void exit(void);
    
    /*=======================================================================*/
    /* Scene Handling                                                        */
    /*=======================================================================*/
    
    virtual void switchScene(int index);
    
    /*=======================================================================*/
    /* Commandline Arguments                                                 */
    /*=======================================================================*/
    
    virtual void setupArguments       (bpo::options_description &commonDesc,
                                       bpo::options_description &cmdLineDesc,
                                       bpo::options_description &fileDesc,
                                       bpo::options_description &hiddenDesc  );
    virtual bool handleSceneArguments (bpo::variables_map const &vm          );
    

  protected:
    /*=======================================================================*/
    /* Per scene data structures                                             */
    /*=======================================================================*/
    
    static const int MI_UNDEFINED = -1;
    static const int MI_BELOW     =  0;
    static const int MI_ABOVE     =  1;
      
    struct SceneOptions : public SceneOptionsBase
    {
        typedef SceneOptionsBase Inherited;
        typedef SceneOptions     Self;
    
                 SceneOptions(void);
        virtual ~SceneOptions(void);
    
        std::vector<std::string>  mExtFiles;
        OSG::Real32               mWaterLevel;
        OSG::Real32               mFogNearAbove;
        OSG::Real32               mFogFarAbove;
        OSG::Vec4f                mFogNearColorAbove;
        OSG::Vec4f                mFogFarColorAbove;
        OSG::Vec4f                mKeyColorAbove;
        OSG::Vec4f                mAntiColorAbove;
        OSG::Real32               mSpecularFactorAbove;
        OSG::Real32               mFogNearBelow;
        OSG::Real32               mFogFarBelow;
        OSG::Vec4f                mFogNearColorBelow;
        OSG::Vec4f                mFogFarColorBelow;
        OSG::Vec4f                mKeyColorBelow;
        OSG::Vec4f                mAntiColorBelow;
        OSG::Real32               mSpecularFactorBelow;
    };
    
    struct SceneData : public SceneDataBase
    {
        typedef SceneDataBase Inherited;
        typedef SceneData     Self;
    
         SceneData(MaterialManager const *pMatManager);
        virtual ~SceneData(void);
        
        ExtrusionManager   *pExtManager;
        int                 mModeIndex;
    };
        
    
    virtual SceneDataBase    *initScene    (SceneOptionsBase const *pSOB);
    
    virtual SceneOptionsBase *createSceneOptions (void                 );
    virtual void              destroySceneOptions(SceneOptionsBase *pSO);
    
    virtual SceneDataBase    *createSceneData    (void                 );
    virtual void              destroySceneData   (SceneDataBase    *pSD);
        
    // updates
    virtual void updateTime         (vpr::Interval const &newTime);
            void updateDynamicParams(void                        );
    
    void loadExtrusionFiles(ExtrusionManager   *pExtManager,
                            SceneOptions const *pSO         );
    
    vpr::Interval             mAppStartTime;
    vpr::Interval             mFrameTime;
    vpr::Interval             mDeltaFrameTime;
    
  private:
    SceneData const           *getSceneData (void) const;
    SceneData                 *editSceneData(void);
  
    SceneOptions const        *getSceneOptions (void) const;
    SceneOptions              *editSceneOptions(void);

    static SceneOptions       *dcastOptions(SceneOptionsBase       *pSO);
    static SceneOptions const *dcastOptions(SceneOptionsBase const *pSO);
  
    static SceneData          *dcastData   (SceneDataBase          *pSD);
    static SceneData const    *dcastData   (SceneDataBase const    *pSD);
    
    virtual void somefunction();
};

inline void MultiLoadApp::somefunction(){
    vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
        << "CHILD CLASS FUNCTION\n "        
        << vprDEBUG_FLUSH;
}

inline MultiLoadApp::SceneOptionsBase *
    MultiLoadApp::createSceneOptions(void)
{
    return new SceneOptions();
}

inline void
    MultiLoadApp::destroySceneOptions(SceneOptionsBase *pSO)
{
    delete dcastOptions(pSO);
}

inline MultiLoadApp::SceneDataBase *
    MultiLoadApp::createSceneData(void)
{
    return new SceneData(pMatManager);
}

inline void
    MultiLoadApp::destroySceneData(SceneDataBase *pSD)
{
    delete dcastData(pSD);
}

inline MultiLoadApp::SceneData const *
    MultiLoadApp::getSceneData(void) const
{
    return dcastData(mActiveSceneData);
}

inline MultiLoadApp::SceneData *
    MultiLoadApp::editSceneData(void)
{
    return dcastData(mActiveSceneData);
}

inline MultiLoadApp::SceneOptions const *
    MultiLoadApp::getSceneOptions (void) const
{
    return dcastOptions(mActiveSceneOptions);
}

inline MultiLoadApp::SceneOptions *
    MultiLoadApp::editSceneOptions(void)
{
    return dcastOptions(mActiveSceneOptions);
}

inline MultiLoadApp::SceneOptions *
    MultiLoadApp::dcastOptions(SceneOptionsBase *pSO)
{
    return dynamic_cast<SceneOptions *>(pSO);
}

inline MultiLoadApp::SceneOptions const *
    MultiLoadApp::dcastOptions(SceneOptionsBase const *pSO)
{
    return dynamic_cast<SceneOptions const *>(pSO);
}

inline MultiLoadApp::SceneData *
    MultiLoadApp::dcastData(SceneDataBase *pSD)
{
    return dynamic_cast<SceneData *>(pSD);
}

inline MultiLoadApp::SceneData const *
    MultiLoadApp::dcastData(SceneDataBase const *pSD)
{
    return dynamic_cast<SceneData const *>(pSD);
}

#endif // _MULTILOADAPP__H_
