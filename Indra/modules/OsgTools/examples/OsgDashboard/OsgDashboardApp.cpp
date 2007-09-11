
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "osgDB/ReadFile"
#include "osgUtil/Optimizer"
#include "osgViewer/Viewer"

#include "OsgTools/OsgToolsConfig.h"
#include "OsgTools/Geom/OsgDashboard.h"

#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgDBd.lib" )
# pragma comment( lib, "osgUtild.lib" )
# pragma comment( lib, "osgGAd.lib" )
# pragma comment( lib, "osgTextd.lib" )
# pragma comment( lib, "osgViewerd.lib" )
# pragma comment( lib, "OpenThreadsd.lib" )
# elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgUtil.lib" )
# pragma comment( lib, "osgGA.lib" )
# pragma comment( lib, "osgText.lib" )  
# pragma comment( lib, "osgViewer.lib" )  
# pragma comment( lib, "OpenThreads.lib" )
#endif

#include <iostream>

int main( int argc, char **argv )
{
  osg::ArgumentParser arguments( &argc,argv );

  osg::ref_ptr< osg::Group > scene( new osg::Group() );
  osg::ref_ptr< OsgTools::Geom::OsgDashboard > dBoard( new OsgTools::Geom::OsgDashboard( 500.0, 500.0, osg::Vec3f( -10.0, 0.0, 0.0 ) ) );

  osg::ref_ptr< osg::Node > loadedModel = osgDB::readNodeFiles( arguments );    
  
  if ( !loadedModel ) 
  {
      std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;        
  }

  osgViewer::Viewer viewer;
      
  // Load a sample texture. 
  osg::ref_ptr< osg::Image > image = osgDB::readImageFile( "PN.png" );
  if( image.get() )
  {
    osg::ref_ptr< osg::Texture2D > texture = new osg::Texture2D( image.get() );

    if( texture.valid() )
    {
      // Turn lighting calculation off on dashboard.
      dBoard->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
      dBoard->setTexture( texture.get(), OsgTools::Geom::OsgDashboard::ALL );
    }
  }

  scene->addChild( loadedModel.get() );        
  scene->addChild( dBoard.get() );
  viewer.setSceneData( scene.get() );    
  return viewer.run();
}

