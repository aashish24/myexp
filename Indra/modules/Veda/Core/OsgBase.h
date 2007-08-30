
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// OSG based application should be derived from here. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VEDA_CORE_OSGBASE_H__
#define __VEDA_CORE_OSGBASE_H__

#include <stdlib.h>

#include "vrj/vrjConfig.h"
#include "vrj/Draw/OSG/OsgApp.h"

#include "Veda/Core/AppBase.h"
#include "Veda/Core/SharedData.h"

#include "Veda/Design/OsgInteractor.h"

#include "osg/Group"
#include "osg/MatrixTransform"
#include "osg/FrameStamp"
#include "osg/Timer"
#include "osg/Light"
#include "osg/LightSource"
#include "osg/LightModel"
#include "osg/StateSet"

#include "osgDB/DatabasePager"

#include "osgUtil/SceneView"

#include "Veda/Export.h"

#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgDBd.lib" )
# pragma comment( lib, "osgUtild.lib" )
# pragma comment( lib, "osgFXd.lib" )
# pragma comment( lib, "osgTextd.lib" )
# elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgUtil.lib" )
# pragma comment( lib, "osgFX.lib" )
# pragma comment( lib, "osgText.lib" )
#endif

namespace Veda
{
  namespace Core
  {
    class VEDA_EXPORT OsgBase : public AppBase, public vrj::OsgApp
    {
      public:
       
        typedef Neiv::Pointer::SmartPtr< OsgBase >      RefPtr;

        OsgBase( vrj::Kernel* kern, int& argc, char** argv );

       
        /////////////////////////////////////////////////////////////////////////
        //
        // Initialization functions. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void                                    setAll();      
        virtual void                                    setOsg();
        virtual void                                    setApp();  
      
        virtual void                                    init();
        virtual void                                    contextInit();
        
        virtual void                                    initScene();    
        virtual void                                    initSceneNodes();
        
        virtual void                                    wandInit();    
        
        virtual Design::OsgInteractor*                  getOsgInteractor();
        virtual void                                    setOsgInteractor( Design::OsgInteractor* );

        osg::Group*                                     getScene();
        virtual void                                    configSceneView( osgUtil::SceneView* sv );
      
        virtual float                                   getDrawScaleFactor();
        
        virtual void                                    viewAll( osg::MatrixTransform* tranform, float zScale = 2.0 );  
    
        /////////////////////////////////////////////////////////////////////////
        //
        // Per frame functions. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void                                    bufferPreDraw ();       

        virtual void                                    preFrame();
        
        virtual void                                    latePreFrame();
        
        virtual void                                    draw();
        
        virtual void                                    intraFrame();
        
        virtual void                                    postFrame();

        virtual void                                    cleanUp();


      protected:    
      
        
        virtual                                         ~OsgBase();

        /////////////////////////////////////////////////////////////////////////
        //
        // Application specific functions. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void                                    appInit(){}
        
        virtual void                                    appSceneInit(){}
        
        virtual void                                    appContextInit(){}

        virtual void                                    appPostInit(){}
        
        virtual void                                    appBufferPreDraw();
      
        virtual void                                    appPreFrame(){}

        virtual void                                    appLatePreFrame(){}
        
        virtual void                                    appPreOsgDraw(){}

        virtual void                                    appPostOsgDraw(){}

        virtual void                                    appOpenGLDraw(){} 

        virtual void                                    appIntraFrame(){}
        
        virtual void                                    appPostFrame(){}


        /////////////////////////////////////////////////////////////////////////
        //
        // Scene related functions. 
        //
        /////////////////////////////////////////////////////////////////////////

        virtual void                                   setBackgroundColor( float* color );

        virtual const osg::Vec3&                       getSceneInitialPosition() const;      
        virtual void                                   setSceneInitialPosition( const osg::Vec3& position );
        
        virtual const                                  osg::Vec3& getScenePivotPoint() const;
        virtual void                                   setScenePivotPoint( const osg::Vec3& pivot );

        virtual void                                   addSceneLight();

        virtual void                                   updateOSG();


      protected:  

        /////////////////////////////////////////////////////////////////////////
        //
        //   
        //                    Root
        //                     |
        //        -------------------------
        //        |            |
        //  SceneTransform   SceneStatic     
        //        |             |
        //  ModelTransform    
        //        |
        //    ModelGroup         
        //        |
        //  
        //
        /////////////////////////////////////////////////////////////////////////      


        /////////////////////////////////////////////////////////////////////////
        // 
        // Root node. 
        //
        /////////////////////////////////////////////////////////////////////////
         
        osg::ref_ptr< osg::Group >                     mSceneRoot;


        /////////////////////////////////////////////////////////////////////////
        // 
        // Scene transform. 
        //
        /////////////////////////////////////////////////////////////////////////

        osg::ref_ptr< osg::MatrixTransform >           mSceneTransformNode;


        /////////////////////////////////////////////////////////////////////////
        // 
        // Scene static node ( Absolute reference ).
        //
        /////////////////////////////////////////////////////////////////////////

        osg::ref_ptr< osg::MatrixTransform >           mSceneStaticNode;


        /////////////////////////////////////////////////////////////////////////
        // 
        // Model transform node. 
        //
        /////////////////////////////////////////////////////////////////////////

        osg::ref_ptr< osg::MatrixTransform >           mModelTransformNode;      


        /////////////////////////////////////////////////////////////////////////
        // 
        // Group for all dynamic data in the scene. 
        //
        /////////////////////////////////////////////////////////////////////////

        osg::ref_ptr< osg::Group >                     mModelGroupNode;  

        
        /////////////////////////////////////////////////////////////////////////
        // 
        // All lights in the scene attached to this node. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        osg::ref_ptr<osg::Group>                       mLightGroup;

        
        /////////////////////////////////////////////////////////////////////////
        //
        // Light model which will define whether the viewpoint is local 
        // of infine. This is very critical to make sure we dont get 
        // different specularity across different screens. If we have 
        // infinite view point then the view direction will be parallel 
        // and towards Z direction. As this makes calculations for 
        // specularity easier it also make lighting poor as then hightlight 
        // at any vertex is independent of its position relative to eye 
        // coordinate. Setting local viewer to true make it look proper 
        // but with a performace hit as light has to be calculated at 
        // every vertex.
        //
        ////////////////////////////////////////////////////////////////////////
         
        osg::ref_ptr< osg::LightModel >                mLightModel;

        
        /////////////////////////////////////////////////////////////////////////
        //
        // Scene background color. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        osg::Vec4f                                    mSceneBackgroundColor;


        /////////////////////////////////////////////////////////////////////////
        //
        // Application can set their own initial position which Will be 
        // used after the scene bounding sphere center gets translated to 
        // origin.
        //
        /////////////////////////////////////////////////////////////////////////
        
        osg::Vec3f                                    mSceneInitialPosition;

        
        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        bool                                          mSceneInitialPositionSet;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////
        
        osg::Vec3                                      mScenePivotPoint; 
        

        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        bool                                           mScenePivotPointSet;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        bool                                           mInteractionSet;

      
        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        osg::ref_ptr< osgUtil::SceneView >             mSceneViewer;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        osg::ref_ptr< osgDB::DatabasePager >           mOsgDatabasePager;


        /////////////////////////////////////////////////////////////////////////
        //
        //
        //
        /////////////////////////////////////////////////////////////////////////

        long unsigned                                   mFrameNumber;

      private:
        
        osg::ref_ptr< osg::StateSet >                   mRootStateSet;

        
        osg::ref_ptr< osg::FrameStamp >                 mFrameStamp;    

        osg::Timer                                      mTimer;
        osg::Timer_t                                    mStartTime;
        osg::Timer_t                                    mLastTime;
    };  
  }
}

#endif // __VEDA_CORE_OSGBASE_H__
