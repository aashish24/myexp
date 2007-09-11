
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

#include "OsgTools/OsgToolsConfig.h"
#include "OsgTools/Geom/OsgDashboard.h"
#include "OsgTools/Callback/OsgUniformCallback.h"

#include <iostream>

#include "SceneManager.h"

static osg::ref_ptr<osg::Group> rootNode;


static osg::StateSet* ModelInstance()
{
    static float zvalue = 0.0f;
    static osg::Node* masterModel = new OsgTools::Geom::OsgDashboard( 500.0, 500.0, osg::Vec3f( -10.0, 0.0, 0.0 ) );

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


static osg::Program* ShaderProgram;
static osg::Shader*  ShaderVertObj;
static osg::Shader*  ShaderFragObj;

#define NORMAL_MAP          1
#define DEACL_TEXTURE       2      

osg::ref_ptr<osg::Group>

SceneManager::buildScene()
{
   osg::Image* decalImage =  osgDB::readImageFile("Images/BumpMap/Decal.png");
   osg::Texture2D* decalTexture( new osg::Texture2D( decalImage ) );    

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
        ss->setTextureAttribute( TEXUNIT_NOISE, noiseTexture );
        ss->setTextureAttribute( TEXTURE, decalTexture );
        
        ShaderProgram = new osg::Program;
        ShaderProgram->setName( "eroded" );
        mProgramList.push_back( ShaderProgram );

        ShaderVertObj = new osg::Shader( osg::Shader::VERTEX );
        ShaderFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        ShaderProgram->addShader( ShaderFragObj );
        ShaderProgram->addShader( ShaderVertObj );
        
        ss->setAttributeAndModes( ShaderProgram, osg::StateAttribute::ON );
        ss->addUniform( new osg::Uniform( "lightPosition", osg::Vec3( 0.0f, 0.0f, 4.0f ) ) );        
        ss->addUniform( new osg::Uniform( "sampler3d", TEXUNIT_NOISE ) );
        ss->addUniform( new osg::Uniform( "texture", TEXTURE ) ); 
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

    
    LoadShaderSource( ShaderVertObj, "Erode/Erode.vert" );
    LoadShaderSource( ShaderFragObj, "Erode/Erode.frag" );
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

