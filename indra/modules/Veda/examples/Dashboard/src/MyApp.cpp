//:
//: 

//: MYApp includes.
#include "MyApp.h"

//: C++ includes.
#include <fstream>

//: 
#include <osg/Group>
#include <osg/Node>

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgVJApp( kern, argc, argv )
{
	; //: Initialize member variables here.
	count = 0;
}

//:---------------------------------------------------------------------
//: One time initialization. 
//:---------------------------------------------------------------------
void MyApp::appInit()
{
	//: Set all the properties here
	setDevice(ALL, OFF);	
	setBackgroundColor((gmtl::Vec4f(0.35, 0.35, 0.35, 1.0)).getData());	
}

//:---------------------------------------------------------------------
//: 
//:---------------------------------------------------------------------
void MyApp::appBufferPreDraw()
{
	//: Set background color to black.
	glClearColor(0.5, 0.5, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

//:---------------------------------------------------------------------
//: Scenegraph will be build here. 
//:---------------------------------------------------------------------
void MyApp::appSceneInit()
{	
	std::cerr << " [MyApp] apiInit starts: " << std::endl;		

	osg::ref_ptr<osg::Group> modelGroupNode = new osg::Group();
	loadGroupedData(modelGroupNode.get(), ".//../data/ModelList.txt");
	if(modelGroupNode.get())
	{
		mModelGroupNode->addChild(modelGroupNode.get());
	}		

	mAppDigitalDashboard.setTextPos(osg::Vec3f((0.8), -0.6379, -3.9624));
	mAppDigitalDashboard.setTextColor(osg::Vec4(0.5, 0.5, 0.45, 1.0));
	mAppDigitalDashboard.setTextFont("fonts/nobilty.ttf");
	mAppDigitalDashboard.createDigitalDashboard(osg::Vec3f(-1.3081, -0.9779, -3.9624), 
												osg::Vec3f( 1.3081,  0.9779, -3.9624));

	osg::ref_ptr<osg::StateSet> stateset = mAppDigitalDashboard.getDigitalDashboardNode()->getOrCreateStateSet();
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(".//../data/images/WRTS-Evac.tga");
	if(image.valid())
	{
		osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D(image.get());
		stateset->setTextureAttributeAndModes(0, texture2D.get(), osg::StateAttribute::ON);
	}

	osg::ref_ptr<osg::MatrixTransform> dashboard_transform = new osg::MatrixTransform();
	//dashboard_transform->preMult(osg::Matrixf::rotate(osg::DegreesToRadians(76.0), 0.0, 1.0, 0.0));
	//dashboard_transform->preMult(osg::Matrixf::translate(0.2, 0.0, -1.0));

	dashboard_transform->addChild(mAppDigitalDashboard.getDigitalDashboardNode());
	mModelGroupNode->addChild(dashboard_transform.get());
	mAppDigitalDashboard.setText(0, std::string("Aashish"));
	

	std::cerr << " [MyApp] apiInit ends: " << std::endl;
}

void MyApp::appPostOsgDraw()
{
	/*
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0.0, 0.0 );
			glVertex2f(100.0, 0.0 );
			glVertex2f(100.0, 100.0 );
			glVertex2f(0.0, 100.0 );
		glEnd();
	glPopMatrix(); 
	*/
}

void MyApp::appPreFrame()
{
	if(count % 10 == 0)
	{
		//mAppDigitalDashboard.setText(0, "Aashish \n at Dt");
	}
	else if(count % 15 == 0)
	{
		//mAppDigitalDashboard.setText(0, "Aashish \n at Prism");
	}
	++count;
}



//:---------------------------------------------------------------------
//: Load data files from the XML. 
//: TODO: Parameter should be ref_ptr not the raw pointer. 
//:---------------------------------------------------------------------
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
				std::cerr << " Name: " << modelNode->getName();		
				osg::ref_ptr<osg::MatrixTransform> modelTransform = new osg::MatrixTransform();
				modelTransform->addChild(modelNode.get());
				groupNode->addChild(modelTransform.get());			
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
