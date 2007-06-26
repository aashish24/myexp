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
	//: Initialize member variables here.
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
	std::cerr << " [MyApp] apiInit ends: " << std::endl;
}

void MyApp::appOpenGLDraw()
{
	glPushMatrix();
	//glTranslatef(5.0, 0.0, -20.0);
	glBegin(GL_QUADS);					// Draw The Cube Using quads
		glColor3f(0.0f,1.0f,0.0f);		// Color Blue
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);		// Color Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);		// Color Red	
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);		// Color Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);		// Color Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);		// Color Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)
	glEnd();	
	glPopMatrix();
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
