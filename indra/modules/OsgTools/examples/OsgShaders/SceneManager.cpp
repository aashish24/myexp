
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
#include "Noise.h"

static osg::Image* make3DNoiseImage(int texSize)
{
    osg::Image* image = new osg::Image;
    image->setImage( texSize, texSize, texSize,
                     4, GL_RGBA, GL_UNSIGNED_BYTE,
                     new unsigned char[ 4 * texSize * texSize * texSize ],
                     osg::Image::USE_NEW_DELETE );

    const int startFrequency = 4;
    const int numOctaves = 4;

    int f, i, j, k, inc;
    double ni[3];
    double inci, incj, inck;
    int frequency = startFrequency;
    GLubyte *ptr;
    double amp = 0.5;

    osg::notify( osg::INFO ) << "creating 3D noise texture... ";

    for (f = 0, inc = 0; f < numOctaves; ++f, frequency *= 2, ++inc, amp *= 0.5)
    {
        SetNoiseFrequency(frequency);
        ptr = image->data();
        ni[0] = ni[1] = ni[2] = 0;

        inci = 1.0 / (texSize / frequency);
        for (i = 0; i < texSize; ++i, ni[0] += inci)
        {
            incj = 1.0 / (texSize / frequency);
            for (j = 0; j < texSize; ++j, ni[1] += incj)
            {
                inck = 1.0 / (texSize / frequency);
                for (k = 0; k < texSize; ++k, ni[2] += inck, ptr += 4)
                {
                    *(ptr+inc) = (GLubyte) (((noise3(ni) + 1.0) * amp) * 128.0);
                }
            }
        }
    }

    osg::notify(osg::INFO) << "DONE" << std::endl;
    return image;        
}

static osg::Texture3D* make3DNoiseTexture(int texSize )
{
    osg::Texture3D* noiseTexture = new osg::Texture3D;
    noiseTexture->setFilter(osg::Texture3D::MIN_FILTER, osg::Texture3D::LINEAR);
    noiseTexture->setFilter(osg::Texture3D::MAG_FILTER, osg::Texture3D::LINEAR);
    noiseTexture->setWrap(osg::Texture3D::WRAP_S, osg::Texture3D::REPEAT);
    noiseTexture->setWrap(osg::Texture3D::WRAP_T, osg::Texture3D::REPEAT);
    noiseTexture->setWrap(osg::Texture3D::WRAP_R, osg::Texture3D::REPEAT);
    noiseTexture->setImage( make3DNoiseImage(texSize) );
    return noiseTexture;
}


static osg::Image* make1DSineImage( int texSize )
{
    const float PI = 3.1415927;

    osg::Image* image = new osg::Image;
    image->setImage(  texSize, 1, 1,
                      4, GL_RGBA, GL_UNSIGNED_BYTE,
                      new unsigned char[ 4 * texSize ],
                      osg::Image::USE_NEW_DELETE );

    GLubyte* ptr = image->data();
    float inc = 2. * PI / ( float )texSize;
    for( int i = 0; i < texSize; i++ )
    {
        *ptr++ = ( GLubyte )( ( sinf( i * inc ) * 0.5 + 0.5 ) * 255.);
        *ptr++ = 0;
        *ptr++ = 0;
        *ptr++ = 1;
    }
    return image;        
}

static osg::Texture1D* make1DSineTexture( int texSize )
{
    osg::Texture1D* sineTexture = new osg::Texture1D;
    sineTexture->setWrap(osg::Texture1D::WRAP_S, osg::Texture1D::REPEAT);
    sineTexture->setFilter(osg::Texture1D::MIN_FILTER, osg::Texture1D::LINEAR);
    sineTexture->setFilter(osg::Texture1D::MAG_FILTER, osg::Texture1D::LINEAR);
    sineTexture->setImage( make1DSineImage(texSize) );
    return sineTexture;
}


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


static osg::Program* ErodedProgram;
static osg::Shader*  ErodedVertObj;
static osg::Shader*  ErodedFragObj;


#define TEXUNIT_SINE        1
#define TEXUNIT_NOISE       2
#define TEXTURE             3

osg::ref_ptr<osg::Group>

SceneManager::buildScene()
{
    osg::Texture3D* noiseTexture = make3DNoiseTexture( 32 /*128*/ );
    osg::Texture1D* sineTexture = make1DSineTexture( 32 /*1024*/ );
    
    osg::Image* image =  osgDB::readImageFile("Images/textura_jove.png");
    osg::Texture2D* decalTexture( new osg::Texture2D( image ) );    

    // the root of our scenegraph.
    rootNode = new osg::Group;

    // attach some Uniforms to the root, to be inherited by Programs.
    {
        osg::Uniform* OffsetUniform = new osg::Uniform( "Offset", osg::Vec3(0.0f, 0.0f, 0.0f) );
        osg::Uniform* SineUniform   = new osg::Uniform( "Sine", 0.0f );
        osg::Uniform* Color1Uniform = new osg::Uniform( "Color1", osg::Vec3(0.0f, 0.0f, 0.0f) );
        osg::Uniform* Color2Uniform = new osg::Uniform( "Color2", osg::Vec3(0.0f, 0.0f, 0.0f) );

        //OsgTools::Anime::OsgUniformCallback< double >* aOUCB 

        double a = 0.1;
        osg::ref_ptr< OsgTools::Callback::OsgUniformCallback< double, 5 >  >sa( new OsgTools::Callback::OsgUniformCallback< double, 5 >( 0.0, 0.0, 1.0, 0.001, 0 ) );
        OffsetUniform->setUpdateCallback( sa.get() );

        osg::StateSet* ss = rootNode->getOrCreateStateSet();
        ss->addUniform( OffsetUniform );
        ss->addUniform( SineUniform );
        ss->addUniform( Color1Uniform );
        ss->addUniform( Color2Uniform );
    }

    // the "eroded" shader, uses a noise texture to discard fragments
    {
        osg::StateSet* ss = ModelInstance();
        ss->setTextureAttribute( TEXUNIT_NOISE, noiseTexture );
        ss->setTextureAttribute( TEXTURE, decalTexture );
        
        ErodedProgram = new osg::Program;
        ErodedProgram->setName( "eroded" );
        _programList.push_back( ErodedProgram );

        ErodedVertObj = new osg::Shader( osg::Shader::VERTEX );
        ErodedFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        ErodedProgram->addShader( ErodedFragObj );
        ErodedProgram->addShader( ErodedVertObj );
        
        ss->setAttributeAndModes( ErodedProgram, osg::StateAttribute::ON );
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
    _rootNode = buildScene();
    _shadersEnabled = true;
}

SceneManager::~SceneManager()
{
}

void SceneManager::reloadShaderSource()
{
    osg::notify(osg::INFO) << "reloadShaderSource()" << std::endl;

    
    LoadShaderSource( ErodedVertObj, "Erode/Erode.vert" );
    LoadShaderSource( ErodedFragObj, "Erode/Erode.frag" );
}


// mew 2003-09-19 : TODO Need to revisit how to better control
// osg::Program enable state in OSG core.  glProgram are
// different enough from other GL state that StateSet::setAttributeAndModes()
// doesn't fit well, so came up with a local implementation.
void SceneManager::toggleShaderEnable()
{
    _shadersEnabled = ! _shadersEnabled;
    osg::notify(osg::WARN) << "shader enable = " <<
            ((_shadersEnabled) ? "ON" : "OFF") << std::endl;
    for( unsigned int i = 0; i < _programList.size(); i++ )
    {
        //_programList[i]->enable( _shadersEnabled );
    }
}

