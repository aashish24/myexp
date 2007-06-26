//:
//: 

//: MYApp includes.
#include "MyApp.h"

//: C++ includes.
#include <fstream>

//: OSG includes. 
#include <osg/ImageStream>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osg/CullFace>

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

	std::vector<std::string> movies; 
	osg::Vec3 pos(0.0f,0.0f,0.0f);

	osgDB::DynamicLibrary::loadLibrary("osgdb_xine.so");        

	osg::ref_ptr<osg::Group> groupNode = new osg::Group();

	std::vector< osg::ref_ptr<osg::Geode> > myGeodeVector;
	myGeodeVector.push_back(new osg::Geode());
	myGeodeVector.push_back(new osg::Geode());

	groupNode->addChild(myGeodeVector[0].get());
	groupNode->addChild(myGeodeVector[1].get());
    mModelGroupNode->addChild(groupNode.get());
	//mModelGroupNode->addChild(myGeode.get());

	movies.push_back(".//../data/Left.avi");
	movies.push_back(".//../data/Right.avi");

	for(size_t i=0; i < movies.size(); ++i)
	{
		osg::ref_ptr<osg::Image> myImage = osgDB::readImageFile(movies[i]);
		osg::ref_ptr<osg::ImageStream> myImageStream = dynamic_cast<osg::ImageStream*>(myImage.get());
		if(myImageStream.valid())
		{
			myImageStream->play();
		}

		 
		 myGeodeVector[i]->addDrawable(createTexturedQuadGeometry(pos,myImage->s(),myImage->t(),myImage.get()));
		 myGeodeVector[i]->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		 pos.z() += myImage->t()*1.5f;
	}
	
	std::cerr << " [MyApp] apiInit ends: " << std::endl;
}

void MyApp::appDraw()
{
	vrj::GlUserData* user_data = vrj::GlDrawManager::instance()->currentUserData();
	int cur_eye = 0;

	if(user_data)
	{
		cur_eye = user_data->getProjection()->getEye();
	}
	

	osg::ref_ptr<osg::Group> group = dynamic_cast<osg::Group*> (mModelGroupNode->getChild(0));

	osg::ref_ptr<osg::Node> nodeL = group->getChild(0);
	osg::ref_ptr<osg::Node> nodeR = group->getChild(1);

	if(cur_eye == vrj::Projection::RIGHT)
	{
		
		nodeL->setNodeMask(0x00);

		//: For some reason I have to turn the right "on" here .... 
		//: TODO --> Find out why ? 
		nodeR->setNodeMask(0xFF);
		
		//mModelGroupNode->getChild(0)->setNodeMask(0x00);
	}

	if(cur_eye == vrj::Projection::LEFT)
	{

		//std::cerr << " Eye is: " << cur_eye << std::endl;
		nodeR->setNodeMask(0x00);

		//: For some reason I have to turn the left "on" here .... 
		//: TODO --> Find out why ? 
		nodeL->setNodeMask(0xFF);

		//mModelGroupNode->getChild(1)->setNodeMask(0x00);
	}
}
osg::Geometry* MyApp::createTexturedQuadGeometry(const osg::Vec3& pos,float width,float height, osg::Image* image)
{
    bool useTextureRectangle = true;
    if (useTextureRectangle)
    {
		osg::Geometry* pictureQuad = osg::createTexturedQuadGeometry(pos,
                                           osg::Vec3(width,0.0f,0.0f),
                                           osg::Vec3(0.0f,0.0f,height),
                                           0.0f,image->t(), image->s(),0.0f);
                                       
        pictureQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0,
                    new osg::TextureRectangle(image),
                    osg::StateAttribute::ON);
                    
        return pictureQuad;
    }
    else
    {
		osg::Geometry* pictureQuad = osg::createTexturedQuadGeometry(pos,
                                           osg::Vec3(width,0.0f,0.0f),
                                           osg::Vec3(0.0f,0.0f,height),
                                           0.0f,0.0f, 1.0f,1.0f);
                                       
        pictureQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0,
                    new osg::Texture2D(image),
                    osg::StateAttribute::ON);

        return pictureQuad;
    }
}
