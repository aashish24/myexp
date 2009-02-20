
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#if 0
#include "Geom/OsgDashboard.h"

using namespace OsgTools::Geom;

osg::Group* OsgDashboard::createBox()
{
  osg::Group* group = new osg::Group;  
  
  // create the geometry for the wall.
  osg::Geometry* geom = new osg::Geometry;
  
  osg::Vec3Array* vertices = new osg::Vec3Array(4);
  (*vertices)[0] = mTopLeft;
  (*vertices)[1] = mBottomLeft;
  (*vertices)[2] = mBottomRight;
  (*vertices)[3] = mTopRight;
  geom->setVertexArray(vertices);
  
  
  osg::Vec2Array* texcoords = new osg::Vec2Array(4);
  (*texcoords)[0].set(0.0f,1.0f);
  (*texcoords)[1].set(0.0f,0.0f);
  (*texcoords)[2].set(1.0f,0.0f);
  (*texcoords)[3].set(1.0f,1.0f);
  geom->setTexCoordArray(0,texcoords);

  
  osg::Vec3Array* normals = new osg::Vec3Array(1);
  (*normals)[0].set(1.0f,0.0f,0.0f);
  geom->setNormalArray(normals);
  geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
  
  /*  
    osg::Vec4Array* colors = new osg::Vec4Array(1);
    (*colors)[0].set(0.0f,0.2f,1.0f,1.0f);
    geom->setColorArray(colors);
    geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
  */

  geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));
  
  osg::Geode* geom_geode = new osg::Geode;
  geom_geode->addDrawable(geom);
  group->addChild(geom_geode);

  return group;
}

#endif
