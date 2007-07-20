
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "Veda/VedaDefines.h"

#if HAVE_OSG

#include "Veda/Core/OsgBase.h"

#include "vrj/Draw/DrawManager.h"
#include "vrj/Display/DisplayManager.h"

#include "osg/LightSource"
#include "osg/Vec3f"
#include "osg/ShapeDrawable"
#include "osg/StateSet"

#include "osgDB/Registry"

namespace Veda
{
  namespace Core
  {
    ///////////////////////////////////////////////////////////////////////////////
    //
    // Constructor. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    OsgBase::OsgBase( vrj::Kernel* kern, int& argc, char** argv ) :  
      mSceneBackgroundColor     ( 0.35, 0.35, 0.35, 1.0 ),
      mSceneInitialPosition     ( 0.0, 0.0, 0.0 ),
      mSceneInitialPositionSet  ( false ), 
      mScenePivotPoint          ( 0.0, 0.0, 0.0 ), 
      mScenePivotPointSet       ( false ), 
      mInteractionSet           ( false ), 
      mFrameNumber              ( 0 ), 
      mRootStateSet             ( new osg::StateSet() )
    {  
    }    


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Destructor.
    //
    ///////////////////////////////////////////////////////////////////////////////
      
    OsgBase::~OsgBase()
    {
      cleanUp();
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set defaults. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setAll()
    {  
      setOsg();
      setApp();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set osg related parameters.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setOsg()
    {
      mFrameStamp = new osg::FrameStamp();  
      
      mStartTime  = mTimer.tick();
      mLastTime   = mStartTime;

      mFrameStamp->setReferenceTime( 0.0 );
      mFrameStamp->setFrameNumber( 0 );
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set application related variables.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setApp()
    {  
      Design::OsgInteractor * interactor = new Design::OsgInteractor();     

      if( interactor )
      {    
        setOsgInteractor( interactor );        
      }
      else
      {
      }
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialization. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::init()
    {    
      setAll();  
      
      vrj::OsgApp::init();

      
      vrj::DrawManager* dm = getDrawManager();
      if( dm )
      {
        int originX, originY, width, height;
        ( dm->getDisplayManager()->getActiveDisplays()[0] )->getOriginAndSize
          ( originX, originY, width, height );
        
        RenderGlobals::setDisplay( originX, originY, width, height );
      }

       appInit();    

      viewAll(mModelTransformNode.get());    

      appPostInit();

      // This should be the last call as before this application can
      // change some of the defaults and initializations of those param
      // will be delayed unless everything is finalized. This also 
      // removes the necessity of having another function to initialize 
      // getInteractor engine. 

      AppBase::init();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Context specific initialization.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::contextInit()
    {
      vrj::OsgApp::contextInit();                  
      
      appContextInit();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialize scene.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::initScene()
    {     
      initSceneNodes(); 
      
      addSceneLight();
      
      appSceneInit();

      if( !mOsgDatabasePager.valid() )
      {
        // Register any PagedLOD that needed to be tracked down in 
        // the scene graph. 
        mOsgDatabasePager = osgDB::Registry::instance()->getOrCreateDatabasePager();

        mOsgDatabasePager->setUseFrameBlock( false );
        mOsgDatabasePager->registerPagedLODs( mSceneRoot.get() );
        mOsgDatabasePager->setUnrefImageDataAfterApplyPolicy( true, false );    
      }

      wandInit(); 

      getOsgInteractor()->root( mSceneRoot.get() );
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialize scene graph nodes.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::initSceneNodes()
    {  
      mSceneRoot            = new osg::Group();
      mSceneTransformNode   = new osg::MatrixTransform();
      mSceneStaticNode      = new osg::MatrixTransform();
      mModelTransformNode   = new osg::MatrixTransform();
      mModelGroupNode       = new osg::Group();
      mLightGroup           = new osg::Group();
      mLightModel           = new osg::LightModel();
     
      mSceneRoot.get()->setName   ( "mSceneRoot" );
      mSceneTransformNode->setName( "mSceneTransformNode" );    
      mSceneStaticNode->setName   ( "mSceneStaticNode" );
      mModelTransformNode->setName( "mModelTransformNode" );      
      mModelGroupNode->setName    ( "mModelGroupNode" );  
      mLightGroup->setName        ( "mLightGroup" );
      

      if( !mSceneRoot.valid() && !mSceneTransformNode.valid() && !mSceneStaticNode.valid() &&
          !mModelTransformNode.valid() && mModelGroupNode.valid() && mLightGroup.valid(), 
          !mLightModel.valid() )
      {
        std::cerr << "Error 1289397492e: Out of memory error. " << std::endl;
      }
      
      mSceneRoot->addChild          ( mLightGroup.get() );   
      mModelTransformNode->addChild ( mModelGroupNode.get() );
      mSceneTransformNode->addChild ( mModelTransformNode.get() );
      mSceneRoot->addChild          ( mSceneStaticNode.get() );
      mSceneRoot->addChild          ( mSceneTransformNode.get() );  
      
      mSceneRoot->setStateSet( mRootStateSet.get() );
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Initialize scene graph nodes.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::wandInit()
    {  
    }  


    ///////////////////////////////////////////////////////////////////////////////
    //
    // View the entire scene. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::viewAll( osg::MatrixTransform* transform, float zScale )
    {        

      if( !transform ) 
      {
        return;
      }

      osg::BoundingSphere bs = mModelGroupNode->getBound();
      
      osg::Vec3f center = bs.center();    
      
      osg::Matrix::value_type z ( zScale* ( bs.radius() ) );  

      if( !mScenePivotPointSet )
      {
        mScenePivotPoint = center;
      }
      
      transform->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f ) );  

      transform->preMult( osg::Matrixf::translate( -mScenePivotPoint ) );

      // Initial tranlation to the scene. 
      if( !mSceneInitialPositionSet )
      {
        mSceneInitialPosition = osg::Vec3( 0.0, z, 0.0 );
      }

      osg::ref_ptr< osg::MatrixTransform > parent = dynamic_cast< osg::MatrixTransform* >( transform->getParent( 0 ) );
      
      parent->preMult( osg::Matrixf::translate( mSceneInitialPosition[ 0 ], mSceneInitialPosition[ 2 ], -mSceneInitialPosition[ 1 ] ) );    
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Add light in the scene.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::addSceneLight()
    {

      if( !mRootStateSet.valid() && mLightGroup.valid()  ) 
      {
        return;
      }
      
      // Default is three lights in the scene.
      std::vector< osg::ref_ptr< osg::Light > >       lights;
      std::vector< osg::ref_ptr< osg::LightSource > > sources;

      // Set local viewer.   
      if( mLightModel.valid() )
      {
        mLightModel->setLocalViewer( true );
      }

      // Initialize lights and light sources.
      for( size_t i = 0; i < 3; ++i )
      {
        lights.push_back  ( new osg::Light() );
        sources.push_back ( new osg::LightSource() ); 
        
        if( lights[ 0 ].valid() && sources[ i ].valid() )
        {
          lights[ i ]->setLightNum( i );

          sources[ i ]->setLight( lights[ i ].get() );
          sources[ i ]->setLocalStateSetModes( osg::StateAttribute::ON );
          sources[ i ]->setStateSetModes( *( mRootStateSet.get() ), osg::StateAttribute::ON );

          mLightGroup->addChild( sources[ i ].get() );
        }
      } 
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Get getInteractor. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    Design::OsgInteractor* OsgBase::getOsgInteractor()
    {
      return ( static_cast< Design::OsgInteractor* >( AppBase::getInteractor() ) );
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Set getInteractor. 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setOsgInteractor( Design::OsgInteractor* interactor )
    {
      AppBase::setInteractor( ( static_cast< void* >( interactor ) ) );
      
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    osg::Group* OsgBase::getScene()
    {
      return mSceneRoot.get();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Configured newly created scene view.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::configSceneView( osgUtil::SceneView* sceneView )
    {   
      vrj::OsgApp::configSceneView( sceneView );      

      mSceneViewer = sceneView;
      
      mSceneViewer->setDrawBufferValue( GL_NONE );
      mSceneViewer->setComputeNearFarMode( osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR );            
      mSceneViewer->setClearColor( mSceneBackgroundColor );

      mSceneViewer->getCullVisitor()->setDatabaseRequestHandler( mOsgDatabasePager.get() );          
      mSceneViewer->getUpdateVisitor()->setDatabaseRequestHandler( mOsgDatabasePager.get() );

      mSceneViewer->setFrameStamp( mFrameStamp.get() );            
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    float OsgBase::getDrawScaleFactor() 
    {
      return gadget::PositionUnitConversion::ConvertToMeters;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::bufferPreDraw()
    {
      appBufferPreDraw();  
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::preFrame()
    {		
      if( SharedData::mCommand.isLocal() )
      {
	//std::cout << "This node is local: " << std::endl;
        osg::Timer_t currTimer  = mTimer.tick();
        
        float deltaTime          = mTimer.delta_s( mLastTime, currTimer ) ;
        long  refTime            = static_cast< long >( mTimer.delta_s( mStartTime, currTimer ) );

        mLastTime = currTimer;

        SharedData::mCommand->mSharedLongTypeObjects[ "FRAME_COUNT" ]  = ++mFrameNumber;      
        SharedData::mCommand->mSharedLongTypeObjects[ "REF_TIME"]      = refTime;;

        getOsgInteractor()->getNavigator()->frameRenderTime( deltaTime );
      }

      updateDeviceData();    

      appPreFrame();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // 
    //
    ///////////////////////////////////////////////////////////////////////////////

    inline void OsgBase::latePreFrame()
    {  
      updateOSG();  

      updateAll();
      
      updateTweek();
      
      appLatePreFrame();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Draw scene graph and call application's OpenGL draw funtion.  
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::draw()
    {
      appPreOsgDraw();  

      glPushMatrix();    
      vrj::OsgApp::draw();    
      glPopMatrix();    
      
      appPostOsgDraw();

      glPushAttrib( GL_ALL_ATTRIB_BITS );
      glPushMatrix();

      glMatrixMode( GL_MODELVIEW );    
      glLoadIdentity();    
      
      glMultMatrix( mSceneTransformNode->getMatrix().ptr() );    
      
      appOpenGLDraw();

      glPopMatrix();
      glPopAttrib();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Runs in parallel with draw above.  
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::intraFrame()
    {
      appIntraFrame();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Post draw function.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::postFrame()
    {   
      appPostFrame();

      // Tell the DatabasePager that the frame is complete and that scene graph
      // is no longer be activity traversed.
      mOsgDatabasePager->signalEndFrame();

      // This is causing some delay in loading paged data. 
      //mOsgDatabasePager->clear();
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    // Perform any cleaning before exit.
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::cleanUp()
    {
      osgDB::Registry::instance()->setDatabasePager(0);
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setBackgroundColor( float* backgroundColor )
    {
      mSceneBackgroundColor.set( backgroundColor[ 0 ], 
                                 backgroundColor[ 1 ],
                                 backgroundColor[ 2 ],
                                 backgroundColor[ 3 ] ); 
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    const osg::Vec3& OsgBase::getSceneInitialPosition() const
    {
      return mSceneInitialPosition;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setSceneInitialPosition( const osg::Vec3& position ) 
    {
      mSceneInitialPosition    = position;
      mSceneInitialPositionSet = true;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    const osg::Vec3& OsgBase::getScenePivotPoint() const
    {
      return mScenePivotPoint;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::setScenePivotPoint( const osg::Vec3& pivot )
    {
      mScenePivotPoint    = pivot;
      mScenePivotPointSet = true;
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::updateOSG()
    {
      if( mFrameStamp.valid() )
      {  
        mFrameStamp->setFrameNumber   ( SharedData::mCommand->mSharedLongTypeObjects[ "FRAME_COUNT" ] );
        mFrameStamp->setReferenceTime( SharedData::mCommand->mSharedLongTypeObjects[ "REF_TIME" ] );
      }

      // Update the osgDB::DatabasePager. 
      mOsgDatabasePager->signalBeginFrame(mFrameStamp.get());
      mOsgDatabasePager->updateSceneGraph(mFrameStamp->getReferenceTime());   
    }


    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //
    ///////////////////////////////////////////////////////////////////////////////

    void OsgBase::appBufferPreDraw()
    {
      // Set default OpenGL background color to black.
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glClear(GL_COLOR_BUFFER_BIT);
    }
  }
}

#endif // HAVE_OSG

