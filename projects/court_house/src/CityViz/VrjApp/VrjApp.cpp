
#include "VrjApp.h"

#include <fstream>

#include "osg/Image"
#include "osg/Group"
#include "osg/Node"
#include "osg/Geometry"
#include "osg/PolygonMode"
#include "osg/LineSegment"
#include "osg/Texture2D"
#include "osg/TexEnv"

#include "VrjCore/Types.h"
#include "VrjUtil/OsgTreeTraversal.h"

#include "gmtl/Matrix.h"
#include "gmtl/Math.h"   
#include "gmtl/MatrixOps.h"

#include "SimFlow/App/Parser.h"
#include "SimFlow/App/AppSAX2Handler.h"

const osg::Vec3f LOWER_LEFT ( -1.3081, -0.9779, -3.9624 );
const osg::Vec3f UPPER_RIGHT(  1.3081,  0.9779, -3.9624 );

VrjApp::VrjApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgVJApp( kern, argc, argv )
{	
}

///////////////////////////////////////////////////////////////////////////////
//
// Create a dashboard.
//
///////////////////////////////////////////////////////////////////////////////

osg::Group* VrjApp::createDashboard()
{
	osg::Group*    group( new osg::Group );	  
	osg::Geometry* geom ( new osg::Geometry );

  osg::BoundingBox bb( LOWER_LEFT, UPPER_RIGHT );
	
  osg::Vec3f topLeft     = osg::Vec3f( bb.xMin(), bb.yMax(), bb.zMin() );
	osg::Vec3f bottomLeft  = osg::Vec3f( bb.xMin(), bb.yMin(), bb.zMin() );
	osg::Vec3f bottomRight = osg::Vec3f( bb.xMax(), bb.yMin(), bb.zMin() );
	osg::Vec3f topRight    = osg::Vec3f( bb.xMax(), bb.yMax(), bb.zMin() );

	osg::Vec3Array* vertices = new osg::Vec3Array( 4 );
	( *vertices )[ 0 ] = topLeft;
	( *vertices )[ 1 ] = bottomLeft;
	( *vertices )[ 2 ] = bottomRight;
	( *vertices )[ 3 ] = topRight;
	geom->setVertexArray( vertices );
	
	
	osg::Vec2Array* texcoords = new osg::Vec2Array( 4 );

	( *texcoords )[ 0 ].set( 0.0f, 1.0f );
	( *texcoords )[ 1 ].set( 0.0f, 0.0f );
	( *texcoords )[ 2 ].set( 1.0f, 0.0f );
	( *texcoords )[ 3 ].set( 1.0f, 1.0f );

	geom->setTexCoordArray( 0,texcoords );

	
	osg::Vec3Array* normals = new osg::Vec3Array( 1 );
	( *normals )[ 0 ].set( 1.0f, 0.0f, 0.0f );
	geom->setNormalArray( normals );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	
	geom->addPrimitiveSet( new osg::DrawArrays( GL_QUADS,0,4 ) );
	
	osg::Geode* geode = new osg::Geode;
	geode->addDrawable( geom );
	group->addChild( geode );

	return group;
}


///////////////////////////////////////////////////////////////////////////////
//
// One time initialization. 
//
///////////////////////////////////////////////////////////////////////////////

void VrjApp::appInit()
{
  setDevice( ALL, OFF );	
	setBackgroundColor( ( gmtl::Vec4f( 0.30, 0.15, 0.55, 1.0 ) ).getData() );	
	setSceneInitialPosition( osg::Vec3( 0.0, 0.0, 0.0 ) );
	setNearFar( 5.0, 1000000000.0 );

	mInteraction = new VrjInteraction();

	setEngine( mInteraction );

	mInteraction->setNavigationMode( HELICOPTER );
	mInteraction->setTransSpeed( 100.0 );
	mInteraction->setTransDelta( 10.0 );
} 

///////////////////////////////////////////////////////////////////////////////
//
// Clear OpenGL buffers. 
//
///////////////////////////////////////////////////////////////////////////////

void VrjApp::appBufferPreDraw()
{
	// Set background color to black.
	glClearColor( 0.5, 0.5, 0.0, 0.0 );

	glClear( GL_COLOR_BUFFER_BIT );
	
}

///////////////////////////////////////////////////////////////////////////////
//
// Scene initialization. 
//
///////////////////////////////////////////////////////////////////////////////

void VrjApp::appSceneInit()
{	
  try  
	{
		// Root. 
		//mRoot  = new osg::Group();

		mModelGroupNode->addChild( mRoot.get() );

    const std::string sceneFile ( "../config/scene.sfd" );    

    // Create a scene manager. 
     mSceneManager = &( SimFlow::Scene::SceneManager::instance() );

    // App specific handler for XML. 
    SimFlow::App::AppSAX2Handler* handler = new SimFlow::App::AppSAX2Handler();
    handler->sceneManager( mSceneManager.get() );
  	
    // Parser object. 
    SimFlow::App::Parser* parser = new SimFlow::App::Parser();
    parser->init();
    parser->setHandler( handler );
    parser->readXML( sceneFile );

    mSceneManager->buildScene();

		mModelGroupNode->addChild( mSceneManager->root() );

    // Load all the textures. 

    std::vector< std::string > dashboardTextures;  
    
    dashboardTextures.push_back( "../data/textures/500000000.png" );    

    for( size_t i = 0; i <  dashboardTextures.size(); ++i )
    {
      osg::ref_ptr< osg::Image > image = osgDB::readImageFile(  dashboardTextures[ i ] );
      if( image.valid() )
      {
        osg::ref_ptr< osg::Texture2D > texture( new osg::Texture2D( image.get() ) );
        mTextures.push_back( texture.get() );
        std::cout << "Success loading texture " <<  dashboardTextures[i] << std::endl;
      }
    }

    // Create a dashboard.
    osg::ref_ptr< osg::MatrixTransform >  dashboard( new osg::MatrixTransform() );
    if( dashboard.valid() )
    {
      dashboard->addChild( createDashboard() );
      dashboard->preMult( osg::Matrixf::rotate( osg::DegreesToRadians( 76.0 ), 0.0, 1.0, 0.0 ) );
	    dashboard->preMult( osg::Matrixf::translate( 0.2, 0.0, -1.0 ) );

      osg::ref_ptr< osg::StateSet > stateSet( dashboard->getOrCreateStateSet() );

      if( mTextures[0].valid() && stateSet.valid() )
      {  
        stateSet->setTextureAttributeAndModes( 0, mTextures[ 0 ].get() );        
        stateSet->setMode( GL_LIGHTING , osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF );

        // Texture env. 
        osg::ref_ptr< osg::TexEnv > texEnv( new osg::TexEnv() );
        if( texEnv.valid() )
        {
          texEnv->setMode( osg::TexEnv::REPLACE );
          stateSet->setTextureAttributeAndModes( 0, texEnv.get(), osg::StateAttribute::ON );
        }      
      }

      mSceneStaticNode->addChild( dashboard.get() );
    }

    mGroups[ "base"   ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "base"  );
    mGroups[ "group1" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group1" );
    mGroups[ "group2" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group2" );
    mGroups[ "group3" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group3" );
    mGroups[ "group4" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group4" );
		mGroups[ "group5" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group5" );
    mGroups[ "group6" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group6" );
    mGroups[ "group7" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group7" );
    mGroups[ "group8" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "group8" );
    mGroups[ "planes" ]     = VrjUtil::OsgTreeTraversal::findNodeByName( mModelGroupNode.get(), "planes" );

		if( mGroups["group1"].valid() )
    {
      mGroups["group1"]->setNodeMask( 0x00 );
    }
  
		if( mGroups["group2"].valid() )
    {
      mGroups["group2"]->setNodeMask( 0x00 );
    }

    if( mGroups["group3"].valid() )
    {
      mGroups["group3"]->setNodeMask( 0x00 );
    }

    if( mGroups["group4"].valid() )
    {
      mGroups["group4"]->setNodeMask( 0x00 );
    }

		if( mGroups["group5"].valid() )
    {
      mGroups["group5"]->setNodeMask( 0x00 );
    }

		if( mGroups["group6"].valid() )
    {
      mGroups["group6"]->setNodeMask( 0x00 );
    }

		if( mGroups["group7"].valid() )
    {
      mGroups["group7"]->setNodeMask( 0x00 );
    }

		if( mGroups["group8"].valid() )
    {
      mGroups["group8"]->setNodeMask( 0x00 );
    }

    if( mGroups[ "planes" ].valid() )
    {
      mGroups[ "planes" ]->setNodeMask( 0x00 );
    }
  }
  catch( ... )
  {
    std::cerr << "Error 4652013840: Unknown error. " << std::endl; 
  }
}


void VrjApp::appPreFrame()
{	
}


void VrjApp::appLatePreFrame()
{
  if(  mInteraction->getButton1Status() )
  {
    static int counter1 = 0;
    counter1 = ( counter1 + 1 ) % 8;

    switch( counter1 )
    {
      case 0: 
      { 
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0xff ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); } 
        break; 
      }

      case 1: 
      { 
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0xff ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); }         
        break; 
      }

      case 2: 
      {
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0xff ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); } 
        
        break; 
      }
      case 3: 
      {
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0xff ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); }         
        break; 
      }
			case 4: 
      {
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0xff ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); }         
        break; 
      }
			case 5: 
      {
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0xff ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); }         
        break; 
      }
			case 6: 
      {
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0xff ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0x00 ); }         
        break; 
      }

			case 7: 
      {
        if( mGroups[ "group1" ].valid() ) { mGroups["group1"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group2" ].valid() ) { mGroups["group2"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group3" ].valid() ) { mGroups["group3"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group4" ].valid() ) { mGroups["group4"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group5" ].valid() ) { mGroups["group5"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group6" ].valid() ) { mGroups["group6"]->setNodeMask( 0x00 ); } 
        if( mGroups[ "group7" ].valid() ) { mGroups["group7"]->setNodeMask( 0x00 ); } 
				if( mGroups[ "group8" ].valid() ) { mGroups["group8"]->setNodeMask( 0xff ); }         
        break; 
      }
    };

    mInteraction->setButton1Pressed( false );
   
  }

  if( mInteraction->getButton3Status() )
  {
    if( mGroups[ "planes" ].valid() )
    {
      mGroups[ "planes" ]->setNodeMask( !mGroups[ "planes" ]->getNodeMask() );
    }
  }

  mSceneManager->update();
}


void VrjApp::addSceneLight()
{
	mRoot = new osg::MatrixTransform();
	mRoot->setReferenceFrame( osg::Transform::ABSOLUTE_RF );

	osg::ref_ptr< osg::StateSet > stateSet = mSceneRoot->getOrCreateStateSet();

	if( !stateSet.valid() )
	{
		return;
	}

	stateSet->setMode( GL_LIGHT1, osg::StateAttribute::ON );
	stateSet->setMode( GL_LIGHT2, osg::StateAttribute::ON );

	osg::ref_ptr<osg::Light> light0 = new osg::Light();
	light0->setLightNum(0);
	light0->setAmbient(osg::Vec4d( 0.0, 0.0, 0.0, 1.0 ) );
	light0->setDiffuse(osg::Vec4d( 0.5, 0.5, 0.5, 1.0 ) );
	light0->setSpecular(osg::Vec4d( 0.05, 0.05, 0.05, 1.0 ) );
	light0->setPosition(osg::Vec4f( 0.0, 0.0, 0.0, 1.0 ) );

	osg::ref_ptr<osg::Light> light1 = new osg::Light();
	light1->setLightNum(1);
	light1->setAmbient(osg::Vec4d(0.02, 0.02, 0.02, 1.0));
	light1->setDiffuse(osg::Vec4d( 0.7, 0.7, 0.7, 1.0));
	light1->setSpecular(osg::Vec4d( 0.7, 0.7, 0.7, 1.0));
	light1->setPosition(osg::Vec4d(0.0, 10000.0,  0.0, 1.0));

  osg::ref_ptr<osg::Light> light2 = new osg::Light();
	light2->setLightNum(2);
	light2->setAmbient(osg::Vec4d( 0.2, 0.2, 0.2, 1.0 ) );
	light2->setDiffuse(osg::Vec4d( 0.3, 0.3, 0.3, 1.0 ) );
	light2->setSpecular(osg::Vec4d( 0.3, 0.3, 0.3, 1.0 ) );
	light2->setPosition(osg::Vec4d( 10000.0, 10000.0, 0.0, 1.0 ) );

	osg::ref_ptr<osg::LightSource> lightSource0 = new osg::LightSource();
	lightSource0->setLight(light0.get());	
	lightSource0->setLocalStateSetModes(osg::StateAttribute::ON);
	
	osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource();
	lightSource1->setLight(light1.get());	
	lightSource1->setLocalStateSetModes(osg::StateAttribute::ON);	

  osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource();
	lightSource2->setLight( light2.get() );	
	lightSource2->setLocalStateSetModes( osg::StateAttribute::ON );	

	if( mLightModel.valid() )
	{
		//mLightModel->setLocalViewer( true);
		mLightModel->setAmbientIntensity( osg::Vec4( 0.25, 0.25, 0.25, 1.0 ) );		
	}
	else
	{
		;
	}

	if( stateSet.valid() )
	{
		lightSource0->setStateSetModes(*(stateSet.get()),osg::StateAttribute::ON);
		lightSource1->setStateSetModes(*(stateSet.get()),osg::StateAttribute::ON);
    lightSource2->setStateSetModes(*(stateSet.get()),osg::StateAttribute::ON);
		stateSet->setAttributeAndModes
			( mLightModel.get(), osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );
	}
	else
	{
		;
	}	

	mLightGroup->addChild( lightSource0.get() );
	mLightGroup->addChild( lightSource1.get() );
	mLightGroup->addChild( lightSource2.get() );

	//mSceneStaticNode->addChild( mLightGroup.get() );
}