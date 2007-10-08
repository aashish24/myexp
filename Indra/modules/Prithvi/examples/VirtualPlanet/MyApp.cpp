
#include "MyApp.h"

#include "fstream"

#include "osg/Group"
#include "osg/Node"
#include "osg/PolygonMode"
#include "osg/LineSegment"

#include "osgDB/ReadFile"

#include "Veda/Core/Types.h"
#include "Prithvi/Core/Planet.h"

#include "gmtl/Matrix.h"
#include "gmtl/Math.h"   
#include "gmtl/MatrixOps.h"

using namespace Veda::Core;

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgBase( kern, argc, argv )
{
  mPlanet = new Prithvi::Core::Planet();
  mPlanet->readKwl( std::string( argv[ 1 ] ) );
  mPlanet->setElevationScale( 10.0 );	
}

//
void MyApp::appContextInit()
{  
  mPlanet->initShaders();
}

// One time initialization. 
void MyApp::appInit()
{
  setBackgroundColor( ( gmtl::Vec4f( 0.35, 0.35, 0.35, 1.0 ) ).getData() );		
  setNearFar( 0.00001, 10.0 );
  setSceneInitialPosition( osg::Vec3( 0.0, 0.0, 0.0 ) );  

  try
  {
    getOsgInteractor()->getNavigator()->navigationMode( OSSIMNAV );
  }
  catch( ... )
  {
    std::cerr << "Unknown Error: Invalid pointer or memory corruption error " << std::endl;
  }
} 

// Clears OpenGL buffers. 
void MyApp::appBufferPreDraw()
{
	glClearColor( 0.5, 0.5, 0.5, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );
}

// Scenegraph will be build here. 
void MyApp::appSceneInit()
{
  mPlanet = new Prithvi::Core::Planet();
  mPlanet->readKwl( "/home/aashish/src/ossim/current/archive/ossimPlanet/examples/ossimplanetviewer/archive_manager.kwl" );
  mPlanet->setElevationScale( 10.0 );

  mModelGroupNode->addChild( mPlanet->root() );
}

// Frame function just before draw. 
void MyApp::appLatePreFrame()
{
}

