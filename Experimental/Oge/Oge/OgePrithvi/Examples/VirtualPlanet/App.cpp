
#include "App.h"

#include "fstream"

#include "osg/Group"
#include "osg/Node"
#include "osg/PolygonMode"
#include "osg/LineSegment"

#include "osgDB/ReadFile"

using namespace Oge::OgeVrj::VrjOsg;

App::App( int& argc, char** argv ) : VrjViewer( argc, argv )
{
  _planet = new Oge::OgePrithvi::PrithviCore::Planet();
  _planet->readKwl( std::string( "F://data//gis//earth//blue_marble.kwl" ) );
  _planet->setElevationScale( 10.0 );	
}

//
void App::contextInit()
{  
  VrjViewer::contextInit();
  _planet->initShaders();
}

// One time initialization. 
void App::init()
{ 
  VrjViewer::init();
} 

void App::initScene()
{
  this->setSceneData( _planet->root() );
}
