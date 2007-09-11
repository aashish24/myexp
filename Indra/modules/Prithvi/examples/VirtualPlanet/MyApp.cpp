
#include "MyApp.h"

#include "fstream"

#include "osg/Group"
#include "osg/Node"
#include "osg/PolygonMode"
#include "osg/LineSegment"

#include "osgDB/ReadFile"

#include "Veda/Core/Types.h"

#include "gmtl/Matrix.h"
#include "gmtl/Math.h"   
#include "gmtl/MatrixOps.h"

using namespace Veda::Core;

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgBase( kern, argc, argv ), 
  mPlanet( new Prithvi::Core::Planet() )
{	
  // Second argument should be a kwl file. 
  mPlanet->readKwl( std::string( argv[ 1 ] ) );
}

// One time initialization. 
void MyApp::appInit()
{
  setBackgroundColor( ( gmtl::Vec4f( 0.35, 0.35, 0.35, 1.0 ) ).getData() );		
  setNearFar( 0.00001, 10.0 );
  setSceneInitialPosition( osg::Vec3( 0.0, 0.0, 0.0 ) );
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
  mModelGroupNode->addChild( mPlanet->root() );
}

// Frame function just before draw. 
void MyApp::appLatePreFrame()
{
}

