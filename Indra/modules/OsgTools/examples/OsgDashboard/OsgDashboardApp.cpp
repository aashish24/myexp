
#include "osgDB/ReadFile"
#include "osgUtil/Optimizer"
#include "osgViewer/Viewer"

#include "OsgTools/Geom/OsgDashboard.h"

#include <iostream>

int main( int argc, char **argv )
{
    osg::ArgumentParser arguments( &argc,argv );

    osg::ref_ptr< osg::Group > scene( new osg::Group() );

    osg::ref_ptr< osg::Node > loadedModel = osgDB::readNodeFiles( arguments );    
    
    if ( !loadedModel ) 
    {
        std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;        
    }

    osgViewer::Viewer viewer;
    
    //scene->addChild( loadedModel.get() );
    scene->addChild( new OsgTools::Geom::OsgDashboard( 500.0, 500.0, osg::Vec3f( -10.0, 0.0, 0.0 ) ) );
    viewer.setSceneData( scene.get() );    
    return viewer.run();
}

