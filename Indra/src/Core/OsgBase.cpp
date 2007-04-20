
#include "Core/OsgBase.h"

#include "Util/OsgConv.h"

#include "vrj/Draw/DrawManager.h"
#include "vrj/Display/DisplayManager.h"

#include "osg/LightSource"
#include "osg/Vec3f"
#include "osg/ShapeDrawable"
#include "osg/StateSet"

#include "osgDB/Registry"

///////////////////////////////////////////////////////////////////////////////
//
// Constructor. 
//
///////////////////////////////////////////////////////////////////////////////

Core::OsgBase::OsgBase( vrj::Kernel* kern, int& argc, char** argv ) :  
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
  
Core::OsgBase::~OsgBase()
{
	cleanUp();
}

///////////////////////////////////////////////////////////////////////////////
//
// Set defaults. 
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::setAll()
{  
	setOsg();
	setApp();
}


///////////////////////////////////////////////////////////////////////////////
//
// Set osg related parameters.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::setOsg()
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

void Core::OsgBase::setApp()
{	
	Interaction * osgInteraction = new OsgInteraction(); 		

	if( osgInteraction )
	{		
		setInteraction( osgInteraction );				
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

void Core::OsgBase::init()
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
	// interaction engine. 

	AppBase::init();
}

///////////////////////////////////////////////////////////////////////////////
//
// Context specific initialization.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::contextInit()
{
	vrj::OsgApp::contextInit();									
	
	appContextInit();
}


///////////////////////////////////////////////////////////////////////////////
//
// Initialize scene.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::initScene()
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

	getInteraction()->root( mSceneRoot.get() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Initialize scene graph nodes.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::initSceneNodes()
{	
	mSceneRoot			      = new osg::Group();
	mSceneTransformNode   = new osg::MatrixTransform();
	mSceneStaticNode	    = new osg::MatrixTransform();
	mModelTransformNode   = new osg::MatrixTransform();
	mModelGroupNode		    = new osg::Group();
	mLightGroup			      = new osg::Group();
	mLightModel			      = new osg::LightModel();
 
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

void Core::OsgBase::wandInit()
{	
}  


///////////////////////////////////////////////////////////////////////////////
//
// View the entire scene. 
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::viewAll( osg::MatrixTransform* transform, float zScale )
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
  parent->preMult( osg::Matrixf::translate( Util::OsgConv::transformToOpenGL( mSceneInitialPosition ) ) );		
}


///////////////////////////////////////////////////////////////////////////////
//
// Add light in the scene.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::addSceneLight()
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
// Get interaction. 
//
///////////////////////////////////////////////////////////////////////////////

Core::OsgInteraction* Core::OsgBase::getInteraction()
{
  return ( static_cast< OsgInteraction* >( AppBase::interaction() ) );
}


///////////////////////////////////////////////////////////////////////////////
//
// Set interaction. 
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::setInteraction( Interaction* interaction )
{
  AppBase::interaction( interaction );

	mInteractionSet = true;		
}


///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

osg::Group* Core::OsgBase::getScene()
{
  return mSceneRoot.get();
}


///////////////////////////////////////////////////////////////////////////////
//
// Configured newly created scene view.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::configSceneView( osgUtil::SceneView* sceneView )
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

float Core::OsgBase::getDrawScaleFactor() 
{
  return gadget::PositionUnitConversion::ConvertToMeters;
}


///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::bufferPreDraw()
{
  appBufferPreDraw();	
}


///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::preFrame()
{
  if( SharedData::mCommand.isLocal() )
  {
    osg::Timer_t currTimer	= mTimer.tick();
    
    float deltaTime			    = mTimer.delta_s( mLastTime, currTimer ) ;
    long  refTime			      = static_cast< long >( mTimer.delta_s( mStartTime, currTimer ) );

    mLastTime = currTimer;

    SharedData::mCommand->mSharedLongTypeObjects[ "FRAME_COUNT" ]	= ++mFrameNumber;			
    SharedData::mCommand->mSharedLongTypeObjects[ "REF_TIME"]	    = refTime;;

    getInteraction()->navigator( WORLD ).frameRenderTime( deltaTime );
  }

  updateDeviceData();	

  appPreFrame();
}


///////////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////////

inline void Core::OsgBase::latePreFrame()
{	
  updateOSG();	

  update();
  
  updateTweek();
  
  appLatePreFrame();
}


///////////////////////////////////////////////////////////////////////////////
//
// Draw scene graph and call application's OpenGL draw funtion.  
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::draw()
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

void Core::OsgBase::intraFrame()
{
  appIntraFrame();
}


///////////////////////////////////////////////////////////////////////////////
//
// Post draw function.
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::postFrame()
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

void Core::OsgBase::cleanUp()
{
  osgDB::Registry::instance()->setDatabasePager(0);
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::setBackgroundColor( float* backgroundColor )
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

const osg::Vec3& Core::OsgBase::getSceneInitialPosition() const
{
  return mSceneInitialPosition;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::setSceneInitialPosition( const osg::Vec3& position ) 
{
  mSceneInitialPosition    = position;
  mSceneInitialPositionSet = true;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

const osg::Vec3& Core::OsgBase::getScenePivotPoint() const
{
  return mScenePivotPoint;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::setScenePivotPoint( const osg::Vec3& pivot )
{
  mScenePivotPoint    = pivot;
  mScenePivotPointSet = true;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

void Core::OsgBase::updateOSG()
{
  if( mFrameStamp.valid() )
  {	
    mFrameStamp->setFrameNumber	 ( SharedData::mCommand->mSharedLongTypeObjects[ "FRAME_COUNT" ] );
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

void Core::OsgBase::appBufferPreDraw()
{
  // Set default OpenGL background color to black.
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
}