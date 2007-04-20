//:
//: 

//: MYApp includes.
#include "MyApp.h"

//: C++ includes.
#include <fstream>

//: VJApp include.
#include <TweekCommand.h>


MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgVJApp( kern, argc, argv )
{
	; //: Initialize member variables here.
}

//:---------------------------------------------------------------------
//: One time initialization. 
//:---------------------------------------------------------------------
void MyApp::appInit()
{
	//: Set all the properties here
	setDevice(TWEEK, ON);
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

void MyApp::appLatePreFrame()
{

	//std::cerr << mDtSubject->getCommandList().size() << std::endl;
	
	if(mReadyCommandList.size() != 0)
	{
		std::cerr << mReadyCommandList.size() << std::endl;
		for(size_t i=0; i < mReadyCommandList.size(); ++i)
		{
			takeAction( mReadyCommandList[i]->mIdentifier,
						mReadyCommandList[i]->mEntity, 
						mReadyCommandList[i]->mStateAttribute, 
						mReadyCommandList[i]->mModifierString, 
						mReadyCommandList[i]->mModifierBoolean, 
						mReadyCommandList[i]->mModifierLong );
		}
	}	
	clearReadyCommandList();	
}

void MyApp::takeAction( std::string command_identifier, std::string entity, std::string state_attribute, std::string modifier_string, bool modifier_bool, long modifier_long )
{
	if(command_identifier == "Command1")
	{
		if(entity == "SceneRoot" && modifier_string == "OFF")
		{
			mSceneRoot->setNodeMask(0x00);
		}
		else if(entity == "SceneRoot" && modifier_string == "ON")
		{
			mSceneRoot->setNodeMask(0xFF);
		}
	}

	if(command_identifier == "Command2")
	{
		if((entity  == "Cow") && (state_attribute == "TextureUnit0"))
		{
			osg::ref_ptr<osg::Group> gNode1 = dynamic_cast<osg::Group*>(mModelGroupNode->getChild(0));
			if(gNode1.valid())
			{
				osg::ref_ptr<osg::Group> gNode2 = dynamic_cast<osg::Group*>(gNode1->getChild(0));
				if(gNode2.valid())
				{
					osg::ref_ptr<osg::StateSet> stateset = gNode2->getChild(0)->getOrCreateStateSet();
					if(stateset.valid())
					{
						if(modifier_string == "OFF")
							stateset->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF);
						else 
							stateset->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
					}
				}
			}
		}
	}
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
				osg::StateSet* state = modelNode->getOrCreateStateSet();				
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
