
#include <osg/Notify>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>

using namespace osg;

osg::ref_ptr<osg::Node> buildScene()
{
  // Root node. 
  osg::ref_ptr<osg::Group> rootN( new osg::Group() );

  // Geode that contains the leaf nodes. 
  osg::ref_ptr<osg::Geode> geodeN( new osg::Geode() ); 
  osg::ref_ptr<osg::Geometry> geom( new osg::Geometry() );
  
  geodeN->addDrawable( geom.get() );
  rootN->addChild( geodeN.get() );

  // Add data to the geometry. 
  osg::ref_ptr<osg::Vec4Array> vertices = new osg::Vec4Array();
  vertices->push_back( osg::Vec4(0.0, 0.0, 0.0, 1.0 ) );
  vertices->push_back( osg::Vec4(10.0, 0.0, 0.0, 1.0 ) );
  vertices->push_back( osg::Vec4(10.0, 10.0, 0.0, 1.0 ) );  

  osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(); 
  colors->push_back( osg::Vec4( 0.0, 1.0, 0.0, 1.0 ) );
  colors->push_back( osg::Vec4( 1.0, 0.0, 0.0, 1.0 ) );
  colors->push_back( osg::Vec4( 0.0, 0.0, 1.0, 1.0 ) );

  osg::ref_ptr<osg::DrawElementsUInt> faces = new osg::DrawElementsUInt( GL_TRIANGLES, 0 );
  faces->push_back(0);
  faces->push_back(1); 
  faces->push_back(2); 

  geom->setVertexArray( vertices.get() );
  geom->setColorArray( colors.get() );
  geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
  geom->addPrimitiveSet( faces.get() );

  // Return root node. 
  return rootN;
}


int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    viewer.setSceneData( buildScene().get() );    

    return viewer.run();
}

/*EOF*/

