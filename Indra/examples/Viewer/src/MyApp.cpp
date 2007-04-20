
#include "MyApp.h"

#include "fstream"

#include "osg/Group"
#include "osg/Node"
#include "osg/PolygonMode"
#include "osg/LineSegment"

#include "osgDB/ReadFile"

#include "Core/Types.h"

#include "gmtl/Matrix.h"
#include "gmtl/Math.h"   
#include "gmtl/MatrixOps.h"

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgBase( kern, argc, argv )
{
	count = 0;
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
	osg::ref_ptr< osg::Group > modelGroupNode( new osg::Group() );
	loadGroupedData( modelGroupNode.get(), ".//../data/ModelList.txt" );

	osg::ref_ptr< osg::StateSet > stateset = modelGroupNode->getOrCreateStateSet();
	if(stateset.valid())
	{
  	osg::ref_ptr< osg::PolygonMode > poly_mode( new osg::PolygonMode() );
		poly_mode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		stateset->setAttributeAndModes(poly_mode.get(), osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
	}

	if(modelGroupNode.get())
	{
		mModelGroupNode->addChild(modelGroupNode.get());
  }	
}

void MyApp::loadGroupedData(osg::Group* groupNode, const std::string& fileName)
{
	std::ifstream inputFile(fileName.c_str(), std::ios_base::in);
	if(inputFile.good()) 
	{		
		while(!inputFile.eof())
		{
			std::string dataFileName; 
			inputFile >> dataFileName >> std::ws;
			osg::ref_ptr< osg::Node > modelNode = osgDB::readNodeFile(dataFileName);
			if(modelNode.get())
			{		
				groupNode->addChild(modelNode.get());					
			}
			else 
			{				
			}
		}
	}
	else
	{			
	}
	inputFile.close();
}

