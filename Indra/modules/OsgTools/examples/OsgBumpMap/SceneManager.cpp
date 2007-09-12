
#include "osg/ShapeDrawable"
#include "osg/PositionAttitudeTransform"
#include "osg/Geode"
#include "osg/Node"
#include "osg/Material"
#include "osg/Notify"
#include "osg/Vec3"
#include "osg/Texture1D"
#include "osg/Texture2D"
#include "osg/Texture3D"
#include "osgDB/ReadFile"
#include "osgDB/FileUtils"
#include "osgUtil/Optimizer"

#include "osg/Program"
#include "osg/Shader"
#include "osg/Uniform"

#include "osgUtil/TangentSpaceGenerator"

#include "OsgTools/OsgToolsConfig.h"
#include "OsgTools/Geom/OsgDashboard.h"
#include "OsgTools/Callback/OsgUniformCallback.h"

#include <iostream>

#include "SceneManager.h"

static osg::ref_ptr<osg::Group> rootNode;
static osg::ref_ptr< osgUtil::TangentSpaceGenerator > tsg;

static osg::StateSet* ModelInstance()
{
    static float zvalue = 0.0f;
    static osg::Node* masterModel = new OsgTools::Geom::OsgDashboard( 500.0, 500.0, osg::Vec3f( -10.0, 0.0, 0.0 ) );

    static OsgTools::Geom::OsgDashboard* group = static_cast< OsgTools::Geom::OsgDashboard* >( masterModel );

    if( !group )
      return 0x00;
    
    static osg::Group* sub = static_cast< osg::Group* >( group->getChild( 0 ) );
    static osg::Geode* geode = static_cast< osg::Geode* >( sub->getChild( 0 ) );

    if( geode )
    {
      osg::Geometry* geom = static_cast< osg::Geometry* >( geode->getDrawable( 0 ) );
      if( geom )
      {
        tsg =  new osgUtil::TangentSpaceGenerator();
        tsg->generate( geom );

        geom->setVertexAttribArray( 6, tsg->getTangentArray() );
        geom->setVertexAttribBinding( 6, osg::Geometry::BIND_PER_VERTEX );
        //geom->setVertexAttribIndices( 0, geom->getNormalIndices() );

        geom->setVertexAttribArray( 7, tsg->getBinormalArray() );
        geom->setVertexAttribBinding( 7, osg::Geometry::BIND_PER_VERTEX );
        //geom->setVertexAttribIndices( 1, geom->getNormalIndices() );

        //geom->setVertexAttribArray( 2, tsg->getNormalArray() );
        //geom->setVertexAttribBinding( 2, osg::Geometry::BIND_PER_VERTEX );
        //geom->setVertexAttribBinding( osg::( 2, geom->getNormalIndices() );

        /*GLint locB  = glGetAttribLocation( gProgram, "binormal" );
        glBindAttribLocation( gProgram, locB, "binormal" );
        glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, b->getDataPointer() );*/
      }
    }

    osg::PositionAttitudeTransform* xform = new osg::PositionAttitudeTransform();
    xform->setPosition( osg::Vec3( 0.0f, -1.0f, zvalue ) );
    zvalue = zvalue + 2.2f;
    xform->addChild( masterModel );
    rootNode->addChild( xform );
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


static osg::Program* ShaderProgram;
static osg::Shader*  ShaderVertObj;
static osg::Shader*  ShaderFragObj;

#define NORMAL_MAP          0
//#define DECAL_TEXTURE       1      

osg::ref_ptr<osg::Group>

SceneManager::buildScene()
{
   //osg::Image* decalImage =  osgDB::readImageFile("Images/BumpMap/DecalMap.jpg");
   //osg::Texture2D* decalTexture( new osg::Texture2D( decalImage ) );    

   osg::Image* normalImage =  osgDB::readImageFile("Images/BumpMap/NormalMap.jpg");
   osg::Texture2D* normalTexture( new osg::Texture2D( normalImage ) );    

    // the root of our scenegraph.
    rootNode = new osg::Group;

    // attach some Uniforms to the root, to be inherited by Programs.
    {
        /*osg::Uniform* OffsetUniform = new osg::Uniform( "Offset", osg::Vec3(0.0f, 0.0f, 0.0f) );
        osg::Uniform* SineUniform   = new osg::Uniform( "Sine", 0.0f );
        osg::Uniform* Color1Uniform = new osg::Uniform( "Color1", osg::Vec3(0.0f, 0.0f, 0.0f) );
        osg::Uniform* Color2Uniform = new osg::Uniform( "Color2", osg::Vec3(0.0f, 0.0f, 0.0f) );

        osg::StateSet* ss = rootNode->getOrCreateStateSet();
        ss->addUniform( OffsetUniform );
        ss->addUniform( SineUniform );
        ss->addUniform( Color1Uniform );
        ss->addUniform( Color2Uniform );*/
    }

    // the "eroded" shader, uses a noise texture to discard fragments
    {
        osg::StateSet* ss = ModelInstance();
        ss->setTextureAttribute( NORMAL_MAP, normalTexture );
                
        ShaderProgram = new osg::Program;
        ShaderProgram->setName( "BumpMap" );
        mProgramList.push_back( ShaderProgram );

        ShaderVertObj = new osg::Shader( osg::Shader::VERTEX );
        ShaderFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        ShaderProgram->addShader( ShaderFragObj );
        ShaderProgram->addShader( ShaderVertObj );
        
        ss->setAttributeAndModes( ShaderProgram, osg::StateAttribute::ON );
        ss->addUniform( new osg::Uniform( "lightDir", osg::Vec3( 0.0f, 100.0f, 0.0f ) ) );       
        ss->addUniform( new osg::Uniform( "NormalMap", NORMAL_MAP ) );
        //ss->addUniform( new osg::Uniform( "Decal", DECAL_TEXTURE ) );
        
        ShaderProgram->addBindAttribLocation( "tangent", osg::Drawable::ATTRIBUTE_6 );
        //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, tsg->getTangentArray() );

        ShaderProgram->addBindAttribLocation( "binormal", osg::Drawable::ATTRIBUTE_7 );
        //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, tsg->getBinormalArray() );

        //ShaderProgram->addBindAttribLocation( "normal", osg::Drawable::NORMALS );
        //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, tsg->getNormalArray() );
    }

    reloadShaderSource();

    return rootNode;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

SceneManager::SceneManager()
{
    mRootNode = buildScene();
    mShadersEnabled = true;
}

SceneManager::~SceneManager()
{
}

void SceneManager::reloadShaderSource()
{
    osg::notify(osg::INFO) << "reloadShaderSource()" << std::endl;

    
    LoadShaderSource( ShaderVertObj, "BumpMap/BumpMap.vert" );
    LoadShaderSource( ShaderFragObj, "BumpMap/BumpMap.frag" );
}


// mew 2003-09-19 : TODO Need to revisit how to better control
// osg::Program enable state in OSG core.  glProgram are
// different enough from other GL state that StateSet::setAttributeAndModes()
// doesn't fit well, so came up with a local implementation.
void SceneManager::toggleShaderEnable()
{
    mShadersEnabled = ! mShadersEnabled;
    osg::notify(osg::WARN) << "shader enable = " <<
            ((mShadersEnabled) ? "ON" : "OFF") << std::endl;
    for( unsigned int i = 0; i < mProgramList.size(); i++ )
    {
        //mProgramList[i]->enable( mShadersEnabled );
    }
}

