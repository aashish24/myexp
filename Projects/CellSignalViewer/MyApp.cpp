
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

#include "OsgTools/Geom/OsgDashboard.h"

using namespace Veda::Core;

// All the dashboard will also be maintained in an array of dashboard pointers to 
// facilitate turning them on and off depending on user viewpoint location

MyApp::MyApp( vrj::Kernel* kern, int& argc, char** argv ) : OsgBase( kern, argc, argv )
{	

  for( int i = 1; i < argc; ++i  )
  {
    if( std::string( argv[ i ] ) == "-f" )
    {
      mFileNames.push_back( argv[ ++i ] );
    }
  }

	mCurrDashBoardOnNum = -1;
	mPrevDashBoardOnNum = -1;
	mTimer = 0;

}

// One time initialization. 

void MyApp::appInit()
{
  //setDevice( ALL, OFF );
	setBackgroundColor((gmtl::Vec4f(0.35, 0.35, 0.35, 1.0)).getData());		
  setNearFar(0.1, 1000000000.0);
	setSceneInitialPosition( osg::Vec3f(0.0, 0.0, 0.0) );

} 

// This function will return the first location of the texture of a point in 
// the array of dashboard. That texture and the subsequent 4 textures are the 
// texture related to that point and will be turn on. If negative value is 
// returned, then no dashboard need to turn on.
 int MyApp::calculateSignalPoint()
{	
	unsigned int dashboardCount = 0;
	osg::Vec3f tmpVec3f;

	// get the current viewpoint coordinate from vrjuggler
	// but that process is a little more involved, since vrjuggler is moving
	// the object and not the viewpoint, so have to get the scene transformation
	// matrix and derive the location of the view in the scene to determine
	// if the view is approaching the object

	osg::Matrix currentViewMatrix = mSceneTransformNode->getMatrix();
	osg::Vec3f currentViewPos = currentViewMatrix.getTrans();
	
//	std::cout << "The current raw location is x=" << currentViewPos.x() << " y=" << 
//		currentViewPos.y() << " z=" << currentViewPos.z() << std::endl;

	currentViewPos = -currentViewPos;
	currentViewPos.set(currentViewPos.x(), -currentViewPos.z(), (currentViewPos.y()+4));

//		std::cout << "The current location is x=" << currentViewPos.x() << " y=" << 
//		currentViewPos.y() << " z=" << currentViewPos.z() << std::endl;

	// test if the viewpoint is near any point and determine which point it is 
	// it will return the first dash board on the same level as the view and 
	// return the location of the dash boards in the array. If -1 is return, then 
	// it is not near any dash boards
	while (dashboardCount < mSignalPointsVec.size())
	{
		tmpVec3f.set(mSignalPointsVec[dashboardCount].x(), mSignalPointsVec[dashboardCount].y(),
			mSignalPointsVec[dashboardCount].z());
		// Check for dash board distance only if the view and the dash board is in the same level
		if ( (currentViewPos.z() - mSignalPointsVec[dashboardCount].w()) < 1 )
		{

//		std::cout << "The distance is " << (tmpVec3f - currentViewPos).length() << std::endl;
			if ( (tmpVec3f - currentViewPos).length() < viewDistance )
				return dashboardCount;
			else
				dashboardCount++;
		}
		else
			dashboardCount++;
	}

	// if the view is not close to any points
	return -1;
}

void MyApp::displayDashBoard()
{
	 // if viewport is within viewing distance of a point, then turn on the next five dashboards
	 if (mCurrDashBoardOnNum >= 0)
	 {
		 // Check if within range
		 if (mCurrDashBoardOnNum < ( int(mDashBoardVec.size()-4) ))
		 {
			 for (int i=mCurrDashBoardOnNum; i < (mCurrDashBoardOnNum+5); i++)
			 {
				 mDashBoardVec[i]->setNodeMask(0xFF);
			 }
			 mPrevDashBoardOnNum = mCurrDashBoardOnNum;
		 }
		 else
		 {
			 std::cout << "Out of Range" << std::endl;
			 std::exit(0);
		 }
	 }
	 // if no dash board should be on, then turn off the previous dashboards turned on
	 else
	 {
		 // if dash boards was previously turned on then turn it off
		 if (mPrevDashBoardOnNum >= 0)
		 {
			 for (int j=mPrevDashBoardOnNum; j < (mPrevDashBoardOnNum+5); j++)
			 {
				 mDashBoardVec[j]->setNodeMask(0x00);
			 }
		 }
	 }
	 mPrevDashBoardOnNum = mCurrDashBoardOnNum;
}

// Clears OpenGL buffers. 
void MyApp::appBufferPreDraw()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	mCurrDashBoardOnNum = calculateSignalPoint()*5;
	displayDashBoard();	
}

void MyApp::loadDashBoards()
{
	int level, point;
	float px, py, pz;
	char textureName[50];
	osg::ref_ptr< OsgTools::Geom::OsgDashboard > dashboard;
	osg::ref_ptr< osg::Image > image;
	osg::ref_ptr< osg::Texture2D > texture;
	osg::Vec4f signalPoint;

	std::ifstream inFile;
	inFile.open("data//pointlist.txt");

	if (!inFile) 
	{
		std::cout << "Unable to open file";
		std::exit(0); // terminate with error
	}

	while (!inFile.eof()) 
	{

		inFile >> level;
		inFile >> point;
		inFile >> px;
		inFile >> py;
		inFile >> pz;

		signalPoint.set(px, py, pz, level);
		if (signalPoint.valid())
		{
			mSignalPointsVec.push_back(signalPoint);
		}
		else
		{
			std::cout << "Invalid signal point" << std::endl;
			std::exit(0);
		}

		for (int i=0;i<5;i++)
		{
		
			dashboard = 
				new OsgTools::Geom::OsgDashboard( 0.1, 0.1, osg::Vec3f( (px+(i*0.1)), py, pz ) );

			if (i==0)
				sprintf(textureName,"data//%d00//R%d//EMF.jpg",level, point);
			else if (i==1)
				sprintf(textureName,"data//%d00//R%d//NF.jpg",level, point);
			else if (i==2)
				sprintf(textureName,"data//%d00//R%d//PN.jpg",level, point);
			else if (i==3)
				sprintf(textureName,"data//%d00//R%d//SP.jpg",level, point);
			else if (i==4)
				sprintf(textureName,"data//%d00//R%d//SS.jpg",level, point);

			image = osgDB::readImageFile(textureName);
		
			if( image.get() )
			{
				texture = new osg::Texture2D( image.get() );
				if( texture.valid() )
				{
					// Turn lighting calculation off on dashboard.
					dashboard->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
					dashboard->setTexture( texture.get(), OsgTools::Geom::OsgDashboard::ALL );
				}
			}

			// keep the pointer to the dashBoard inserted into the scenegraph
			mDashBoardVec.push_back(dashboard.get());
			
			// turn off the dashboard when loading it
			// to turn it on, change 0x00 to 0xFF
			dashboard->setNodeMask(0x00);
			mModelGroupNode->addChild(dashboard.get());
		}
	}
	inFile.close();
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
	loadDashBoards();
}

void MyApp::appLatePreFrame()
{

	//osg::Matrix tMat( osg::Matrix::translate( osg::Vec3f(2.036,0.0,-4.0) ) );
	//mSceneTransformNode->setMatrix(tMat);

}
