
#include "MyApp.h"

#include "Veda/Tweek/TweekCommand.h"

#include "osgDB/ReadFile"

#include <fstream>

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : Veda::Core::OsgBase( kern, argc, argv )
{	
}


void MyApp::appInit()
{
	enableFeature( TWEEK );
	setBackgroundColor( ( gmtl::Vec4f(0.35, 0.35, 0.35, 1.0 ) ).getData() );	
}


void MyApp::appBufferPreDraw()
{
	glClearColor( 0.5, 0.5, 0.0, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );
}


void MyApp::appSceneInit()
{	
	std::cout <<"Initializing scene: " << std::endl; 
	osg::ref_ptr< osg::Group > modelGroupNode = new osg::Group();
	loadGroupedData( modelGroupNode.get(), ".//data/ModelList.txt" );
	if( modelGroupNode.get() )
	{
		mModelGroupNode->addChild( modelGroupNode.get() );
	}			
}


void MyApp::appLatePreFrame()
{
	/*	
	if( mReadyCommandList.size() != 0 )
	{
		std::cerr << mReadyCommandList.size() << std::endl;
		
    for( size_t i=0; i < mReadyCommandList.size(); ++i )
		{
			takeAction( mReadyCommandList[i]->mKey, mReadyCommandList[i]->mValue ); 
		}
	}	

	clearReadyCommandList();	
	*/
}

void MyApp::appPostFrame()
{
}

void MyApp::takeAction( const std::string& key, const std::string& value )
{	
	if( value == "HIDE" )
	{
		mModelGroupNode->setNodeMask( 0x00 );	
	}
	
	if( value == "SHOW" )
	{
		mModelGroupNode->setNodeMask( 0xff );
	}
}


void MyApp::loadGroupedData( osg::Group* groupNode, const std::string& fileName )
{
	std::ifstream inputFile( fileName.c_str(), std::ios_base::in );
	
  if( inputFile.good() ) 
	{		
		while( !inputFile.eof() )
		{
			std::string dataFileName; 
			inputFile >> dataFileName >> std::ws;

      osg::ref_ptr<osg::Node> modelNode = osgDB::readNodeFile(dataFileName);
			if(modelNode.get())
			{	
				osg::StateSet* state = modelNode->getOrCreateStateSet();				
				osg::ref_ptr< osg::MatrixTransform > modelTransform = new osg::MatrixTransform();
				modelTransform->addChild( modelNode.get() );
				groupNode->addChild( modelTransform.get() );			
			}
			else 
			{
        // Error. 
			}
		}
	}
	else
	{	
    // Error. 
	}

	inputFile.close();
}
