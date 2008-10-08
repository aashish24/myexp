
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
#include "osg/LightSource"

#include "osgUtil/TangentSpaceGenerator"

#include "OsgTools/OsgToolsConfig.h"
#include "OsgTools/Geom/OsgDashboard.h"
#include "OsgTools/Callback/OsgUniformCallback.h"

#include <iostream>

#include "osg/LightModel"

#include "SceneManager.h"

static osg::ref_ptr<osg::Group> rootNode;
static osg::ref_ptr< osgUtil::TangentSpaceGenerator > tsg;

static osg::Light* light1( new osg::Light() );
static osg::StateSet* ss;
static osg::MatrixTransform* lightMat;
static osg::Node* masterModel;


osg::Node* buildPlane()
{
  osg::ref_ptr< osg::Geode > plane( new osg::Geode() );
  osg::ref_ptr< osg::Geometry > geom( new osg::Geometry() );
  
  osg::ref_ptr< osg::Vec3Array > vertices( new osg::Vec3Array );
  vertices->push_back( osg::Vec3( -5.0, 0.0, -5.0 ) ); 
  vertices->push_back( osg::Vec3(  5.0, 0.0, -5.0 ) ); 
  vertices->push_back( osg::Vec3(  5.0, 0.0,  5.0 ) ); 
  vertices->push_back( osg::Vec3( -5.0, 0.0,  5.0 ) ); 
  
  osg::ref_ptr< osg::Vec3Array > normals( new osg::Vec3Array );
  normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) ); 
  normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) ); 
  normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) ); 
  normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) ); 
  
  osg::ref_ptr< osg::Vec3Array > texcoords( new osg::Vec3Array );
  texcoords->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) ); 
  texcoords->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) ); 
  texcoords->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) ); 
  texcoords->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) ); 
  
  osg::ref_ptr< osg::DrawElementsUInt > quad( new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS, 0 ) );
  quad->push_back( 0 );
  quad->push_back( 1 );
  quad->push_back( 2 );
  quad->push_back( 3 );

  geom->setVertexArray( vertices.get() );
  geom->setNormalArray( normals.get() );
  geom->setTexCoordArray( 0, texcoords.get() );

  geom->addPrimitiveSet( quad.get() );
  plane->addDrawable( geom.get() );

  return plane.release();
}

static osg::StateSet* ModelInstance()
{
    masterModel = buildPlane();

    osg::Material* mat( new osg::Material() );
    mat->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4f( 0.7, 0.7, 0.7, 1.0 ) );
    mat->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4f( 0.7, 0.7, 0.7, 1.0 ) );
    mat->setSpecular( osg::Material::FRONT_AND_BACK, osg::Vec4f( 0.9, 0.9, 0.9, 1.0 ) );
    mat->setShininess( osg::Material::FRONT_AND_BACK, 128.0 );

    osg::StateSet* mms = masterModel->getOrCreateStateSet();
    mms->setAttributeAndModes( mat );
    
    
    #if 0
    osg::Group* group = static_cast< osg::Group* >( masterModel );
    
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

        geom->setVertexAttribArray( 2, tsg->getNormalArray() );
        geom->setVertexAttribBinding( 2, osg::Geometry::BIND_PER_VERTEX );

        //geom->setVertexAttribIndices( 1, geom->getNormalIndices() );

        //geom->setVertexAttribArray( 2, tsg->getNormalArray() );
        //geom->setVertexAttribBinding( 2, osg::Geometry::BIND_PER_VERTEX );
        //geom->setVertexAttribBinding( osg::( 2, geom->getNormalIndices() );

        /*GLint locB  = glGetAttribLocation( gProgram, "binormal" );
        glBindAttribLocation( gProgram, locB, "binormal" );
        glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, b->getDataPointer() );*/
      }
    }
  #endif

    osg::PositionAttitudeTransform* xform = new osg::PositionAttitudeTransform();
    xform->setPosition( osg::Vec3( 0.0f, 1.0f, zvalue ) );
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

osg::ref_ptr<osg::Group> SceneManager::buildScene()
{
   //osg::Image* decalImage =  osgDB::readImageFile("Images/BumpMap/DecalMap.jpg");
   //osg::Texture2D* decalTexture( new osg::Texture2D( decalImage ) );    

   osg::Image* normalImage =  osgDB::readImageFile("Images/BumpMap/FieldstoneBumpDOT3.jpg");
   osg::Texture2D* normalTexture( new osg::Texture2D( normalImage ) );    

   
   light1->setLightNum( 0 );
   light1->setPosition( osg::Vec4( 0.0, -5.0, 0.0, 1.0 ) );
   light1->setSpecular( osg::Vec4( 1.0, 1.0, 1.0, 1.0 ) );
   light1->setDiffuse( osg::Vec4( 0.9, 0.0, 0.0, 1.0 ) );

   osg::Light* light2( new osg::Light() );
   light2->setLightNum( 1 );
   light2->setPosition( osg::Vec4( 0.0, 10.0, 0.0, 1.0 ) );
   light2->setSpecular( osg::Vec4( 0.9, 0.0, 0.0, 1.0 ) );
   light2->setDiffuse( osg::Vec4( 0.9, 0.0, 0.0, 1.0 ) );
   light2->setAmbient( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );

   osg::LightSource* ls1( new osg::LightSource() );
   ls1->setLight( light1 );

   osg::LightModel* lightModel( new osg::LightModel() );
   lightModel->setLocalViewer( true );


   osg::LightSource* ls2( new osg::LightSource() );
   
   ls1->setLight( light1);
   //ls2->setLight( light2 );

   lightMat = new osg::MatrixTransform();
   osg::Geode* lightNode( new osg::Geode() );
   lightNode->addDrawable( new osg::ShapeDrawable( new osg::Sphere( osg::Vec3f( 0.0, 0.0, 0.0 ), 1.0 ) ) );
   lightMat->addChild( lightNode ); 

   osg::Vec4 lightPos = light1->getPosition();

   //lightMat->setMatrix( osg::Matrix::translate( lightPos[0], lightPos[1], lightPos[2] ) );

   osg::MatrixTransform* mat ( new osg::MatrixTransform() );
   mat->addChild( lightMat );

   //lightMat->setReferenceFrame( osg::Transform::ABSOLUTE_RF );

    // the root of our scenegraph.
    rootNode = new osg::Group;

    osg::StateSet* sset ( new osg::StateSet() );
    rootNode->setStateSet( sset );

    //ls1->setLocalStateSetModes( osg::StateAttribute::ON );
    ls1->setStateSetModes( *( sset ), osg::StateAttribute::ON );
    sset->setAttributeAndModes( lightModel, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );

    mat->addChild( ls1 );
    //mat->addChild( ls2 );

    rootNode->addChild( mat );
    

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

    ss = ModelInstance();
        

    // the "eroded" shader, uses a noise texture to discard fragments
    #if 0
    {
        ss = ModelInstance();
        ss->setTextureAttribute( NORMAL_MAP, normalTexture );
        
        ShaderProgram = new osg::Program;
        ShaderProgram->setName( "BumpMap" );
        mProgramList.push_back( ShaderProgram );

        ShaderVertObj = new osg::Shader( osg::Shader::VERTEX );
        ShaderFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        ShaderProgram->addShader( ShaderFragObj );
        ShaderProgram->addShader( ShaderVertObj );
        
        ss->setAttributeAndModes( ShaderProgram, osg::StateAttribute::ON );        
        ss->addUniform( new osg::Uniform( "NormalMap", NORMAL_MAP ) );
        ss->addUniform( new osg::Uniform( "LightPos", osg::Vec4f( light1->getPosition() ) ) );

        //ss->addUniform( new osg::Uniform( "Decal", DECAL_TEXTURE ) );
        
        ShaderProgram->addBindAttribLocation( "tangent", osg::Drawable::ATTRIBUTE_6 );
        //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, tsg->getTangentArray() );

        ShaderProgram->addBindAttribLocation( "binormal", osg::Drawable::ATTRIBUTE_7 );
        //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, tsg->getBinormalArray() );

        //ShaderProgram->addBindAttribLocation( "normal", osg::Drawable::NORMALS );
        //glVertexAttribPointer( 10, 3, GL_FLOAT, false, 0, tsg->getNormalArray() );
    }

    reloadShaderSource();
    
    #endif  // 0

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

void SceneManager::update()
{
  static float theta = 0.0;
  static float x = 0.0;
  static float y = -50.0;
  static float z = 0.0;

  float xConst;
  float yConst;
  float zConst;

  osg::BoundingSphere bs = masterModel->getBound();
  xConst = bs.center()[0];
  yConst = bs.center()[1];
  zConst = bs.center()[2];

  x = 50.0 * cos( theta ) + xConst;
  z = 50.0 * sin( theta ) + zConst;
  y = yConst;

  theta = theta + 0.1;

  if( theta >= 360.0 )
  {
    theta = 0.0;
  }

  light1->setPosition( osg::Vec4( x, y, z, 1.0 ) );
  //ss->addUniform( new osg::Uniform( "LightPos", osg::Vec4f( light1->getPosition() ) ) );
  //lightMat->setMatrix( osg::Matrix::translate( x, y, z ) );
}