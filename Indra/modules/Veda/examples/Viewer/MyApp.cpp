
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

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgBase( kern, argc, argv )
{	
  osg::Matrix mat();

  for( unsigned int i = 1; i < argc; ++i  )
  {
    if( std::string( argv[ i ] ) == "-f" )
    {
      mFileNames.push_back( argv[ ++i ] );
    }
  }
}

// One time initialization. 

void MyApp::appInit()
{
  setDevice( ALL, OFF );
	setBackgroundColor((gmtl::Vec4f(0.35, 0.35, 0.35, 1.0)).getData());		
  setNearFar(0.1, 1000000000.0);
} 

// Clears OpenGL buffers. 
void MyApp::appBufferPreDraw()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

// Scenegraph will be build here. 
void MyApp::appSceneInit()
{
  for( size_t i = 0; i < mFileNames.size(); ++i )
  {
    osg::ref_ptr< osg::Node > model = osgDB::readNodeFile( mFileNames[ i ] );
    if( model.valid() )
    {
 		  mModelGroupNode->addChild( model.get() );
    }	  
  }  
}
