
/// MYApp includes.
#include "MyApp.h"

/// C++ includes.
#include <fstream>

/// OSG includes. 
#include <osg/Group>
#include <osg/Node>
#include <osg/PolygonMode>
#include <osg/ShapeDrawable> 

#include <vjCore/Types.h>

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : 
	OsgVJApp( kern, argc, argv ), 
	count( 0 ), 
	mIsSceneView( false )
{
}

///---------------------------------------------------------------------
/// One time initialization. 
///---------------------------------------------------------------------
void MyApp::appInit()
{
	setDevice(ALL, OFF);	

	setBackgroundColor((gmtl::Vec4f(0.35, 0.35, 0.35, 1.0)).getData());	
	setNearFar(0.1, 100.0);	
	getEngine()->setNavigationMode( FLIGHT );   	
}

///---------------------------------------------------------------------
/// 
///---------------------------------------------------------------------
void MyApp::appBufferPreDraw()
{   	
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);	
}

///---------------------------------------------------------------------
/// Scenegraph will be build here. 
///---------------------------------------------------------------------
void MyApp::appSceneInit()
{	
	std::cerr << " [MyApp] apiInit starts: " << std::endl;		

	osg::ref_ptr<osg::Group> modelGroupNode = new osg::Group();
	loadGroupedData(modelGroupNode.get(), ".//../data/ModelList.txt");

	if(modelGroupNode.get())
	{
       	mModelGroupNode->addChild(modelGroupNode.get());		
	}	
	std::cerr << " [MyApp] apiInit ends: " << std::endl;
}

///---------------------------------------------------------------------
/// Load data files from the XML. 
/// TODO: Parameter should be ref_ptr not the raw pointer. 
///---------------------------------------------------------------------
void MyApp::loadGroupedData(osg::Group* groupNode, const std::string& fileName)
{
	std::ifstream inputFile(fileName.c_str(), std::ios_base::in);
	if(inputFile.good()) 
	{		
		while(!inputFile.eof())
		{
			std::string dataFileName; 
			inputFile >> dataFileName >> std::ws;
			std::cerr << " [MyApp] Start loading: "  << dataFileName << std::endl;
			osg::ref_ptr<osg::Node> modelNode = osgDB::readNodeFile(dataFileName);
			if(modelNode.get())
			{		
				/// Just for the fun lets add one more cow. (Shallow Copy in OSG). 
				std::cerr << " Name: " << modelNode->getName();		
				osg::ref_ptr<osg::MatrixTransform> modelTransform_1 = new osg::MatrixTransform();
				//osg::ref_ptr<osg::MatrixTransform> modelTransform_2 = new osg::MatrixTransform();

				/// I found that we need to perform the translation first <BR> 
				/// before we add the model to the second transform node <BR>
				/// else it does not work. (any translation does not work.)
				//modelTransform_2->preMult(osg::Matrixf::translate(10.0, 0.0,0.0));
				modelTransform_1->addChild(modelNode.get());
				//modelTransform_2->addChild(modelNode.get());
				groupNode->addChild(modelTransform_1.get());	
				//groupNode->addChild(modelTransform_2.get());	
			}
			else 
			{
				std::cerr << " [MyApp]		Failed to load: "  << dataFileName << std::endl;
			}

			std::cerr << " [MyApp]		Finished loading: "  << dataFileName << std::endl;
		}
	}
	else
	{	
		std::cerr << " [MyApp]		Input file is corrupted: "  << std::endl;
	}
	inputFile.close();
}

void MyApp::appPreFrame()
{
	/*
	mKm = new KeyboardMouse( 1024, 735 );
	mKm->init();
	if( mSceneViewer.valid() && !mIsSceneView )
	{
		mKmCallBack = new VJKeyboadMouseCallback( mModelTransformNode.get() );
		mKm->setCallBack( mKmCallBack );
		mIsSceneView = true;
	}
	*/
}

void MyApp::appLatePreFrame()
{
	/*
	if( mIsSceneView )
	{
		mKm->update( mKmCallBack );
		osg::Matrixd mat = mKmCallBack->getViewMatrix();
		/*
			std::cout
				<< mat(0, 0) << " " << mat(0, 1) << " " << mat(0, 2) << mat(0, 3) << std::endl
				<< mat(1, 0) << " " << mat(1, 1) << " " << mat(1, 2) << mat(1, 3) << std::endl
				<< mat(2, 0) << " " << mat(2, 1) << " " << mat(2, 2) << mat(2, 3) << std::endl
				<< mat(3, 0) << " " << mat(3, 1) << " " << mat(3, 2) << mat(3, 3) << std::endl;
		

		mSceneTransformNode->setMatrix( mat );
		
	}
	*/
}

void MyApp::appPostOsgDraw()
{
	;
}