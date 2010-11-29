
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/Node>
#include <osg/Material>
#include <osg/Notify>
#include <osg/Vec3>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Texture3D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgUtil/Optimizer>
#include <osgUtil/TangentSpaceGenerator>

#include <osg/Program>
#include <osg/Shader>
#include <osg/Uniform>

#include <iostream>

#include "GL2Scene.h"

static osg::ref_ptr<osg::Group> rootNode;

static std::vector< osg::ref_ptr<osg::Geometry> > geometries;

// Traverse the scene graph and find all the geometry nodes. 
class SceneVisitor : public osg::NodeVisitor
{
  public: 

    virtual void apply( osg::Node& node)
    { 
      osg::ref_ptr<osg::Group> group = node.asGroup();
      if(group.valid())
      {
        for(  size_t i=0; i < group->getNumChildren(); ++i )
        {
          group->getChild(i)->accept(*this);
        }  
      }
  
      osg::ref_ptr<osg::Geode> geode = dynamic_cast<osg::Geode*>(&node);
      if(!geode)
      {
        traverse(node);
        return;
      }

      osg::ref_ptr< osgUtil::TangentSpaceGenerator > tsg = new osgUtil::TangentSpaceGenerator();
      osg::Geode::DrawableList dList = geode->getDrawableList();
      for( size_t i=0; i < dList.size(); ++i )
      {
        if(osg::ref_ptr<osg::Geometry> geom = dynamic_cast<osg::Geometry*>(dList[i].get()))
        {
          tsg->generate( geom.get(), 0 );
          osg::Vec4Array* binormals = tsg->getBinormalArray();
          osg::Vec4Array* tangents  = tsg->getTangentArray();
          geom->setTexCoordArray( 1, tangents );
          geom->setTexCoordArray( 2, binormals );
        }
      }      

      // Keep searching.
      traverse(node);
    }
};


// Create some geometry upon which to render GLSL shaders.
static osg::Node* CreateModel()
{   
  return osgDB::readNodeFile("plane.obj");  
}

// Add a reference to the masterModel at the specified translation, and
// return its StateSet so we can easily attach StateAttributes.
static osg::StateSet* ModelInstance()
{
    static float zvalue = 0.0f;
    static osg::Node* masterModel = CreateModel();

    osg::PositionAttitudeTransform* xform = new osg::PositionAttitudeTransform();
    xform->setPosition(osg::Vec3( 0.0f, -1.0f, zvalue ));
    zvalue = zvalue + 2.2f;
    xform->addChild(masterModel);
    rootNode->addChild(xform);
    return xform->getOrCreateStateSet();
}

// load source from a file.
static void LoadShaderSource( osg::Shader* shader, const std::string& fileName )
{
    std::string fqFileName = osgDB::findDataFile(fileName);
    if( fqFileName.length() != 0 )
    {
        shader->loadShaderSourceFromFile( fqFileName.c_str() );
    }
    else
    {
        osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
    }
}


///////////////////////////////////////////////////////////////////////////
// rude but convenient globals

static osg::Program* BumpmapProgram;
static osg::Shader*  BumpmapVertObj;
static osg::Shader*  BumpmapFragObj;


///////////////////////////////////////////////////////////////////////////
// Compose a scenegraph with examples of GLSL shaders

#define TEXUNIT_SINE        1
#define TEXUNIT_NOISE       2

osg::ref_ptr<osg::Group>
GL2Scene::buildScene()
{ 
    // the root of our scenegraph.
    rootNode = new osg::Group;

    // the simple Microshader (its source appears earlier in this file)
    {        

        osg::StateSet* ss = ModelInstance();
        BumpmapProgram = new osg::Program;
        BumpmapVertObj = new osg::Shader(osg::Shader::VERTEX);
        BumpmapFragObj = new osg::Shader(osg::Shader::FRAGMENT);                     
   
        BumpmapProgram->setName( "bump_map" );
        _programList.push_back( BumpmapProgram );
        BumpmapProgram->addShader( BumpmapVertObj );
        BumpmapProgram->addShader( BumpmapFragObj );
        ss->setAttributeAndModes( BumpmapProgram, osg::StateAttribute::ON );

        this->reloadShaderSource();

        // Read normal map from the disk. 
        osg::ref_ptr<osg::Image> image = osgDB::readImageFile("./textures/stone-normal.png");
        osg::ref_ptr<osg::Texture2D> texture( new osg::Texture2D( image.get() ) ); 
        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

        ss->setTextureAttribute( 0, texture.get(), osg::StateAttribute::ON );
        osg::Uniform* textureUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D, "normalMap");
        textureUniform->set(0);
        ss->addUniform(textureUniform);

        // Read height map from the disk. 
        osg::ref_ptr<osg::Image> heightMapImage = osgDB::readImageFile("./textures/stone-height.png");
        osg::ref_ptr<osg::Texture2D> heightTexture( new osg::Texture2D( heightMapImage.get() ) );
        heightTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
        heightTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
        ss->setTextureAttribute( 1, heightTexture.get(), osg::StateAttribute::ON );
        osg::Uniform* heightMapUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D, "heightMap");
        heightMapUniform->set(1);
        ss->addUniform(heightMapUniform);


        // Read height map from the disk. 
        osg::ref_ptr<osg::Image> decalMapImage = osgDB::readImageFile("./textures/stone-color.png");
        osg::ref_ptr<osg::Texture2D> decalTexture( new osg::Texture2D( decalMapImage.get() ) );
        decalTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
        decalTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);        
        ss->setTextureAttribute( 2, decalTexture.get(), osg::StateAttribute::ON );
        osg::Uniform* decalMapUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D, "decalMap");
        decalMapUniform->set(2);
        ss->addUniform(decalMapUniform);
    }

    // Generate tanget and binormals. 
    osg::ref_ptr<SceneVisitor> sv = new SceneVisitor();;
    rootNode->accept(*sv);

    return rootNode;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

GL2Scene::GL2Scene()
{
    _rootNode = buildScene();
    _shadersEnabled = true;
}


GL2Scene::~GL2Scene()
{
}


void GL2Scene::reloadShaderSource()
{
    osg::notify(osg::INFO) << "reloadShaderSource()" << std::endl;

    LoadShaderSource( BumpmapVertObj, "./shaders/parallax_map.vert" );
    LoadShaderSource( BumpmapFragObj, "./shaders/parallax_map.frag" );
}


// mew 2003-09-19 : TODO Need to revisit how to better control
// osg::Program enable state in OSG core.  glProgram are
// different enough from other GL state that StateSet::setAttributeAndModes()
// doesn't fit well, so came up with a local implementation.

void GL2Scene::toggleShaderEnable()
{
    _shadersEnabled = ! _shadersEnabled;
    osg::notify(osg::WARN) << "shader enable = " <<
            ((_shadersEnabled) ? "ON" : "OFF") << std::endl;
    for( unsigned int i = 0; i < _programList.size(); i++ )
    {
        //_programList[i]->enable( _shadersEnabled );
    }
} 
