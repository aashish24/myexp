
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

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

  for( int i = 1; i < argc; ++i  )
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
  setFeature( ALL, false );
	setBackgroundColor( ( gmtl::Vec4f( 0.35, 0.35, 0.35, 1.0 ) ).getData() );		
  setNearFar( 0.1, 1000000000.0 );
  setSceneInitialPosition( osg::Vec3( 0.0, 10.0, 0.0 ) );
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
      osg::ref_ptr< osg::MatrixTransform > mat1( new osg::MatrixTransform() );
      mat1->setMatrix( osg::Matrix::translate( osg::Vec3f( 10.0f, 0.0f, 0.0f ) ) ); 

      osg::ref_ptr< osg::MatrixTransform > mat2( new osg::MatrixTransform() );
      mat2->setMatrix( osg::Matrix::translate( osg::Vec3f( -10.0f, 0.0f, 0.0f ) ) ); 

      mat1->addChild( model.get() );
      mat2->addChild( model.get() );

      mModelGroupNode->addChild( mat1.get() );
 		  mModelGroupNode->addChild( mat2.get() );
    }	  
  }  
}

void MyApp::appLatePreFrame()
{
  //osg::Matrix mat( osg::Matrix::translate( osg::Vec3f( -10.0, 0.0, 0.0 ) ) );
  //mSceneTransformNode->setMatrix( mat );
}

