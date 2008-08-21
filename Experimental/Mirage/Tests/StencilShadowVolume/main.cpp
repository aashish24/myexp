
#ifdef _MSC_VER
  #include <windows.h>
#endif

#include "GL/glew.h"
#include "GL/glut.h" 
#include "GL/gl.h"

#include "MsgCore/GLSLProgram.h"
#include "MsgCore/GLSLShader.h"
#include "MsgCore/Viewer.h"
#include "MsgCore/Geode.h"
#include "MsgCore/Geometry.h"

#include "MsgDB/FileRead.h"

#include "MsgMath/Vector.h"
#include "MsgMath/Matrix.h"
#include "MsgMath/MatrixVecOps.h"

#include "MsgCore/Material.h"

#include <list>
#include <limits>


// Definitions. 
#define TESTING 0

using namespace Msg;

enum Mode 
{
  NAVIGATE    = 0x0, 
  MOVE_LIGHT  = 0x1, 
  ANIMATE     = 0x2
};

// Flags. 
static bool                               _twoSided         = false;
static bool                               _pause            = true;
static bool                               _debugMode        = false;

static Mode                               _mode             ( MOVE_LIGHT );

static const int                          MAX_LISTS = 30;

// Display lists. 
GLuint                                    _shadowVol;
GLubyte                                   _shadowVolLists[MAX_LISTS];

static const GLfloat                      _lightAmbient[]   = { 0.2f, 0.2f, 0.2f, 1.0f };
static const GLfloat                      _lightDiffuse[]   = { 1.0f, 0.6f, 0.6f, 1.0f };
static const GLfloat                      _lightSpecular[]  = { 1.0f, 0.6f, 0.6f, 1.0f };

static GLfloat                            _lightPosition[]  = { 0.0f, 0.0f, 0.0f, 1.0 };

GLdouble                                  _top;
GLdouble                                  _bottom;
GLdouble                                  _left;
GLdouble                                  _right;

MsgCore::SmartPtr< MsgCore::Material >    _matBlue          ( new MsgCore::Material() );
MsgCore::SmartPtr< MsgCore::Material >    _matRed           ( new MsgCore::Material() );
MsgCore::SmartPtr< MsgCore::Material >    _matShadow        ( new MsgCore::Material() );

MsgCore::SmartPtr< MsgCore::GLSLProgram > _extrusionProgram ( new MsgCore::GLSLProgram() );
MsgCore::SmartPtr< MsgCore::GLSLShader >  _vertShader       ( new MsgCore::GLSLShader( MsgCore::GLSLShader::VERTEX_SHADER ) );
MsgCore::SmartPtr< MsgCore::GLSLShader >  _fragShader       ( new MsgCore::GLSLShader( MsgCore::GLSLShader::FRAGMENT_SHADER ) );

MsgCore::SmartPtr< MsgCore::Viewer >      _viewer           ( new MsgCore::Viewer() );

// Create scene _root node. 
MsgCore::SmartPtr< MsgCore::Group >       _root             ( new MsgCore::Group() );


///////////////////////////////////////////////////////////////////////////////
//
// Defining data structure required for working on geometry and creation of 
// shadow volumes. 
//
///////////////////////////////////////////////////////////////////////////////

struct Vertex
{
  int _vertexIndex;
  int _normalIndex;
  int _texCoordIndex;

  virtual bool operator==( const Vertex& rhs )
  {
    if( ( this->_vertexIndex == rhs._vertexIndex )  &&  
        ( this->_normalIndex == rhs._normalIndex )  && 
        ( this->_texCoordIndex == rhs._texCoordIndex ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};


struct Edge 
{
  Vertex _vertex1; 
  Vertex _vertex2;
  
  virtual bool operator==( const Edge& rhs )
  {
    if( ( this->_vertex1 == rhs._vertex1 )  &&  ( this->_vertex2 == rhs._vertex2 ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};


// Predicate for STL list unique algorithm. 
class compare
{
  public: 
    bool operator()( Edge first, Edge second )
    {
        if( ( first._vertex1._vertexIndex == second._vertex1._vertexIndex ) || 
            ( first._vertex2._vertexIndex == second._vertex1._vertexIndex ) )
        {
          if( ( first._vertex1._vertexIndex == second._vertex2._vertexIndex ) || 
            ( first._vertex2._vertexIndex == second._vertex2._vertexIndex ) )
          {
            return true;
          }
        }

        return false;
    }
};


struct Triangle
{
  MsgMath::Vec3i _faceIndex;
}; 


void drawFloor()
{
  glPushMatrix();
    glBegin( GL_QUADS );
      glVertex3f( -100.0, -1.0, 100.0 );
      glVertex3f(  100.0, -1.0, 100.0 );
      glVertex3f(  100.0, -1.0,-100.0 );
      glVertex3f( -100.0, -1.0,-100.0 );
    glEnd();
  glPopMatrix();
}


void init()
{
  glEnable( GL_DEPTH_CLAMP_NV );
  glEnable( GL_DEPTH_TEST );
  //glEnable( GL_LIGHTING );
  //glEnable( GL_LIGHT0 );  

  //glLightfv( GL_LIGHT0, GL_AMBIENT, _lightAmbient );
  //glLightfv( GL_LIGHT0, GL_DIFFUSE, _lightDiffuse );
  //glLightfv( GL_LIGHT0, GL_SPECULAR, _lightSpecular );  

  // @todo: Planning to perform extraction of vertices via shaders. 
  // Commented out for time being. 
  /* 
  _vertShader->sourceAsFile( "PositionExtrusionShader.vert" );
  _fragShader->sourceAsFile( "PositionExtrusionShader.frag" );

  _vertShader->contextInit();
  _fragShader->contextInit();

  _extrusionProgram->attach( _vertShader.get() );
  _extrusionProgram->attach( _fragShader.get() );

  _extrusionProgram->link();
  */

  glClearColor( 0.0, 0.0, 0.0, 1.0 );

  // Initialize viewer. 
  _viewer->init();
  
  if( !_root.valid() )
  {
    std::cerr << " ERROR: Out of memory or invalid pointer. " << std::endl;
    std::exit( 0 );
  }

  // Read geometry files. 
  MsgCore::SmartPtr< MsgCore::Node > model =  
    MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\trunk\\Experimental\\Mirage\\Data\\Models\\Box.obj" );

  if( model.valid() )
  {
    _root->addChild( model.get() );
  }
  else
  {
    throw " Model not found error: ";
  }

  MsgCore::SmartPtr< MsgCore::Node > floor =  
    MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\trunk\\Experimental\\Mirage\\Data\\Models\\Floor.obj" );

  if( floor.valid() )
  {
    _root->addChild( floor.get() );    
  }
  else
  {
    throw " Model not found error: ";
  }

  _viewer->sceneData( _root.get() );

  // Set materials. 
  if( _matBlue.valid() )
  {
    _matBlue->setProperty( DIFFUSE, MsgMath::Vec4f( 0.0, 0.0, 0.5, 1.0 ) );
    _matBlue->setProperty( AMBIENT, MsgMath::Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
    _matBlue->setProperty( SPECULAR, MsgMath::Vec4f( 0.0, 0.0, 0.5, 1.0 ) );


    //model->getOrCreateStateSet()->attribute( _matBlue.get() );
  }
  else
  {
    // Warning. 
  }

  // Set materials. 
  if( _matRed.valid() )
  {
    _matRed->setProperty( DIFFUSE, MsgMath::Vec4f( 0.0, 0.7, 0.1, 1.0 ) );
    _matRed->setProperty( AMBIENT, MsgMath::Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
    _matRed->setProperty( SPECULAR, MsgMath::Vec4f( 0.0, 0.7, 0.1, 1.0 ) );

    //floor->getOrCreateStateSet()->attribute( _matRed.get() );
  }
  else
  {
    // Warning. 
  }

   // Set materials. 
  if( _matShadow.valid() )
  {
    _matShadow->setProperty( DIFFUSE, MsgMath::Vec4f( 0.1, 0.1, 0.1, 0.5 ) );
    _matShadow->setProperty( AMBIENT, MsgMath::Vec4f( 0.1, 0.1, 0.1, 0.5 ) );
    _matShadow->setProperty( SPECULAR, MsgMath::Vec4f( 0.1, 0.1, 0.1, 0.5 ) );

    //floor->getOrCreateStateSet()->attribute( _matRed.get() );
  }
  else
  {
    // Warning. 
  }

  // Assign ids to display lists. 
  _shadowVol = glGenLists( MAX_LISTS );  
}


//Convert a openGL Matrix into Matrix44d. 
MsgMath::Matrix44d convert( GLdouble* matrix ) 
{
  MsgMath::Matrix44d mat;
  mat.set( matrix );

  return mat;
}


void pushBack( std::list< Edge >& edges, Edge& edge )
{
  bool result = false;
  
  std::list< Edge >::iterator itr = edges.begin();
  for( itr; itr != edges.end(); ++itr )
  {
    if( ( ( edge._vertex1 == itr->_vertex1 ) || 
          ( edge._vertex2 == itr->_vertex1 ) ) &&
        ( ( edge._vertex1 == itr->_vertex2 ) || 
          ( edge._vertex2 == itr->_vertex2 ) ) )
    {
      result = true;
      edges.erase( itr );      
      break;
    }
  }

  if( !result )
  {
    edges.push_back( edge );
  }
}


void getGeodes( std::vector< MsgCore::SmartPtr< MsgCore::Geode > >& geodes, MsgCore::Group* group )
{
  // If NULL
  if( !group )
    return; 

  for( size_t index = 0; index < group->children().size(); ++index )
  {
    // If we get a valid node. 
    if( MsgCore::Node* node = group->child( index ) )
    {      
      if( MsgCore::Geode* geode = node->asGeode() )
      {
        geodes.push_back( geode );
      }
      else if( MsgCore::Group* subGroup = node->asGroup() )
      {
        // Recursive call. 
        getGeodes( geodes, subGroup );
      }
    }
  }  
}

///////////////////////////////////////////////////////////////////////////////
//
// @todo: Two issues. 
// 1. How we are going to draw in the same coordinate system as where 
// we have the original geometry as still we dont have the transform node. 
// 2. We are not iterating over the nodes which are group nodes under the _root? 
// 3. This code will work till we dont have transform nodes. 
//
///////////////////////////////////////////////////////////////////////////////

void buildShadowVolume()
{
  // Lets query the vertices. 
  MsgCore::Node* node = _viewer->sceneData(); 
  
  // Check for valid node. 
  if( !node )
  {
    std::cerr << " WARNING: Invalid or NULL node. " << std::endl;
    return;
  }
   
  MsgCore::SmartPtr< MsgCore::Group > gr = node->asGroup();
  
  // Now check each child of the _root node. 
  // Grab any geometry. 
  // Construct shadow volume out of it.   

  // Now currently checking only at one level ( ignorning group  nodes ). 
  std::vector< MsgCore::SmartPtr< MsgCore::Geode > > geodes; 
  
  // Get all the geodes under this group node. 
  getGeodes( geodes, gr.get() ); 

  for( size_t index = 0; index < geodes.size(); ++index )
  { 
    MsgCore::Geode* geode = geodes[index].get();

    // Get the Model View matrix. 
    GLdouble worldMatrix[16]; 

    glGetDoublev( GL_MODELVIEW_MATRIX, worldMatrix );

    // Convert into Matrix44d so that we can use it for multiplication with verticess. 
    MsgMath::Matrix44d mat = convert( worldMatrix );

    if( geode ) 
    {
      std::vector< MsgCore::SmartPtr< MsgCore::Drawable > > drawables = geode->getDrawableList();

      for( size_t i = 0; i < drawables.size(); ++i ) 
      {
        MsgCore::Geometry* geom = dynamic_cast< MsgCore::Geometry* >( drawables[i].get() );
        if( geom )
        {
          std::vector< Triangle > _capTriangles; 
          std::vector< Triangle > _backTriangles; 
          std::list< Edge > _edges;

          MsgCore::SmartPtr< MsgCore::Vec3iArray > indices    = geom->vertexIndices();
          MsgCore::SmartPtr< MsgCore::Vec3iArray > nIndices   = geom->normalIndices();
          MsgCore::SmartPtr< MsgCore::Vec3Array >  vertices    = geom->vertexArray();
          MsgCore::SmartPtr< MsgCore::Vec3Array >  normals     = geom->normalArray();
          
          MsgMath::Vec4d lightPos = MsgMath::Vec4d( _lightPosition[0], _lightPosition[1], _lightPosition[2], 1 );

          for( size_t k = 0; k < indices->size() ; ++k ) 
          {
            int i1 = indices->at( k )[0];
            int i2 = indices->at( k )[1];
            int i3 = indices->at( k )[2];

            // We may get the geometry which are not called single index geometries.  
            int ni1 = nIndices->at( k )[0];
            int ni2 = nIndices->at( k )[1];
            int ni3 = nIndices->at( k )[2];
              
            MsgMath::Vec3d vecOrig1 = vertices->at( i1 );
            MsgMath::Vec4d vecModi1( vecOrig1[0], vecOrig1[1], vecOrig1[2], 1 );  

            MsgMath::Vec3d vecOrig2 = vertices->at( i2 );
            MsgMath::Vec4d vecModi2( vecOrig2[0], vecOrig2[1], vecOrig2[2], 1 );  

            MsgMath::Vec3d vecOrig3 = vertices->at( i3 );
            MsgMath::Vec4d vecModi3( vecOrig3[0], vecOrig3[1], vecOrig3[2], 1 );  

            //MsgMath::Vec4d lightDir1 = lightPos - MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vecModi1 );
            MsgMath::Vec4d lightDir1 = lightPos - vecModi1;
            lightDir1.normalize();

            //MsgMath::Vec4d lightDir2 = lightPos - MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vecModi2 );
            MsgMath::Vec4d lightDir2 = lightPos - vecModi2;
            lightDir2.normalize();
            
            //MsgMath::Vec4d lightDir3 = lightPos - MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vecModi3 );;  
            MsgMath::Vec4d lightDir3 = lightPos - vecModi3;
            lightDir3.normalize();
            
            MsgMath::Vec3d normal1 =  normals->at( ni1 );
            MsgMath::Vec3d normal2 =  normals->at( ni2 );
            MsgMath::Vec3d normal3 =  normals->at( ni3 );

            MsgMath::Vec4d normal1Modi( normal1[0], normal1[1], normal1[2], 1 );
            MsgMath::Vec4d normal2Modi( normal2[0], normal2[1], normal2[2], 1 );
            MsgMath::Vec4d normal3Modi( normal3[0], normal3[1], normal3[2], 1 );

            int count = 0;

            bool edge1Passed = false; 

            if( ( normal1Modi.dot( lightDir1 ) > 0 ) && ( normal2Modi.dot( lightDir2 ) > 0 ) )
            {
              edge1Passed = true;
            }
          
            if( _twoSided )
            {
              if( ( -normal1Modi.dot( lightDir1 ) > 0 ) && ( -normal2Modi.dot( lightDir2 ) > 0 ) )
              {
                edge1Passed = true;
              }
            }


            if( edge1Passed )
            {
              //std::cout << "Vertex 1 passed: " << std::endl;
              Vertex vertex1; 
              vertex1._vertexIndex = i1;
              vertex1._normalIndex = i1;
              vertex1._texCoordIndex = i1;

              Vertex vertex2; 
              vertex2._vertexIndex = i2;
              vertex2._normalIndex = i2;
              vertex2._texCoordIndex = i2;

              Edge edge; 
              edge._vertex1 = vertex1; 
              edge._vertex2 = vertex2;


              // Insert only if it does not exist. 
              pushBack( _edges, edge );
              //_edges.push_back( edge );

              ++count;
            }           

            bool edge2Passed = false;
            
            if( ( normal2Modi.dot( lightDir2 ) > 0 ) && ( normal3Modi.dot( lightDir3 ) > 0 ) )
            {
              edge2Passed = true;
            }

            if( _twoSided )
            {
              if( ( -normal2Modi.dot( lightDir2 ) > 0 ) && ( -normal3Modi.dot( lightDir3 ) > 0 ) )
              {
                edge2Passed = true;
              }
            }

            if( edge2Passed )
            {
              Vertex vertex1; 
              vertex1._vertexIndex = i2;
              vertex1._normalIndex = i2;
              vertex1._texCoordIndex = i2;

              Vertex vertex2; 
              vertex2._vertexIndex = i3;
              vertex2._normalIndex = i3;
              vertex2._texCoordIndex = i3;

              Edge edge; 
              edge._vertex1 = vertex1; 
              edge._vertex2 = vertex2;

              // Insert only if it does not exist. 
              pushBack( _edges, edge );
              //_edges.push_back( edge );

              ++count;
            }

            bool edge3Passed = false;

            if( ( normal3Modi.dot( lightDir3 ) > 0 ) && ( normal1Modi.dot( lightDir1 ) > 0 ) )  
            {
              edge3Passed = true;
            }

            if( _twoSided )
            {
              if( ( -normal3Modi.dot( lightDir3 ) > 0 ) && ( -normal1Modi.dot( lightDir1 ) > 0 ) )  
              {
                edge3Passed = true;
              } 
            }

            if( edge3Passed )
            {
              Vertex vertex1; 
              vertex1._vertexIndex = i3;
              vertex1._normalIndex = i3;
              vertex1._texCoordIndex = i3;

              Vertex vertex2; 
              vertex2._vertexIndex = i1;
              vertex2._normalIndex = i1;
              vertex2._texCoordIndex = i1;

              Edge edge; 
              edge._vertex1 = vertex1; 
              edge._vertex2 = vertex2;

              // Insert only if it does not exist. 
              pushBack( _edges, edge );
              //_edges.push_back( edge );

              ++count;
            }

            if( count == 3 )
            {
              Triangle triangle;
              triangle._faceIndex = MsgMath::Vec3i( i1, i2, i3 );
              _capTriangles.push_back( triangle );
            }
            else
            {
              Triangle triangle;
              triangle._faceIndex = MsgMath::Vec3i( i1, i2, i3 );
              _backTriangles.push_back( triangle );
            }

          } // End  for( size_t k = 0; k < indices->size() ; ++k )            
         
          
          std::list< Edge >::iterator jItr = _edges.begin();

          // @todo: This is supposed to be infinity. We need to 
          // use projection matrix which will account for this. 
          // Read Gamasutra article on this.                     
          
          // Shadow volume ( Not including front or back cap. ). 
          glNewList( _shadowVol + ( index * 3 ), GL_COMPILE );
          for( jItr; jItr != _edges.end(); ++jItr )
          {            
            glPushMatrix();
            glBegin( GL_QUADS );              
              MsgMath::Vec3d vec3d1 = vertices->at( jItr->_vertex2._vertexIndex );
              MsgMath::Vec3d vec3d2 = vertices->at( jItr->_vertex1._vertexIndex );
              
              MsgMath::Vec4d vec4d1( vec3d1[0], vec3d1[1], vec3d1[2], 1.0 );
              MsgMath::Vec4d vec4d2( vec3d2[0], vec3d2[1], vec3d2[2], 1.0 );
              
              MsgMath::Vec4d vertex41( vec4d1[0] - lightPos[0], vec4d1[1] - lightPos[1], vec4d1[2] - lightPos[2], 0.0 );
              vertex41 = vec4d1 + vertex41;
              
              MsgMath::Vec4d vertex42( vec4d2[0] - lightPos[0], vec4d2[1] - lightPos[1], vec4d2[2] - lightPos[2], 0.0 );
              vertex42 = vec4d2 + vertex42;

              // Extended vertices drawn at infinity ( or at the far plane ). 
              vertex41[3] = 0.0;
              vertex42[3] = 0.0;

              glVertex4dv( vec4d1.front() );              
              glVertex4dv( vec4d2.front() );
              glVertex4dv( vertex42.front() ); 
              glVertex4dv( vertex41.front() );              
            glEnd();                     
            glPopMatrix();            
          }
          glEndList();

          
          // Front cap. 
          glNewList( _shadowVol + ( index * 3 + 1 ), GL_COMPILE );
          glPushMatrix();
          std::vector< Triangle >::const_iterator constItr;
          glEnable( GL_POLYGON_OFFSET_FILL );
          glPolygonOffset( 0.0f, 100.0f );
          glBegin( GL_TRIANGLES );
          for( constItr = _capTriangles.begin(); constItr != _capTriangles.end(); ++constItr )
          {           
            glVertex3dv( vertices->at( constItr->_faceIndex[0] ).front() );
            glVertex3dv( vertices->at( constItr->_faceIndex[1] ).front() );
            glVertex3dv( vertices->at( constItr->_faceIndex[2] ).front() );            
          }
          glEnd();
          glDisable( GL_POLYGON_OFFSET_FILL );  
          glPopMatrix();
          glEndList();

          // Back cap. 
          glNewList( _shadowVol + ( index * 3 + 2 ), GL_COMPILE );
          glPushMatrix();     
          
          // What happens when our occluder is just a plane. 
          // In that case out front facing polygons will be back facing as 
          // well and we need to reverse the draw order then. 
          bool reverse = false;
          if( _backTriangles.empty() )
          {
            _backTriangles = _capTriangles;
            reverse = true;
          }

          for( constItr = _backTriangles.begin(); constItr != _backTriangles.end(); ++constItr )
          {           
            MsgMath::Vec3d v0 = vertices->at( constItr->_faceIndex[0] );            
            MsgMath::Vec3d v1 = vertices->at( constItr->_faceIndex[1] );            
            MsgMath::Vec3d v2 = vertices->at( constItr->_faceIndex[2] );

            if( !reverse )
            {
              glBegin( GL_TRIANGLES );  
                glVertex4d( v0[0] + v0[0] - lightPos[0], v0[1] + v0[1]- lightPos[1], v0[2] + v0[2] - lightPos[2], 0 ); 
                glVertex4d( v1[0] + v1[0] - lightPos[0], v1[1] + v1[1]- lightPos[1], v1[2] + v1[2] - lightPos[2], 0 ); 
                glVertex4d( v2[0] + v2[0] - lightPos[0], v2[1] + v2[1]- lightPos[1], v2[2] + v2[2] - lightPos[2], 0 ); 
              glEnd();
            }
            else
            {
               glBegin( GL_TRIANGLES );  
                glVertex4d( v2[0] + v2[0] - lightPos[0], v2[1] + v2[1]- lightPos[1], v2[2] + v2[2] - lightPos[2], 0 ); 
                glVertex4d( v1[0] + v1[0] - lightPos[0], v1[1] + v1[1]- lightPos[1], v1[2] + v1[2] - lightPos[2], 0 ); 
                glVertex4d( v0[0] + v0[0] - lightPos[0], v0[1] + v0[1]- lightPos[1], v0[2] + v0[2] - lightPos[2], 0 );
              glEnd();
            }
          }                    
          glPopMatrix();
          glEndList();

        } // End if( geom  )
      } // End for( size_t i = 0; i < drawables.size(); ++i ) 
    } // End if( ge ) 
  } // End  for loop. 
}


void drawShadowVolume( bool debugMode = false )
{
  for( size_t i=0; i < MAX_LISTS;++i )
  {
    _shadowVolLists[i] = i;
  }

  if( !debugMode ) 
  {
    glPushMatrix();
      glListBase( _shadowVol );
      glCallLists( MAX_LISTS, GL_UNSIGNED_BYTE, _shadowVolLists );
    glPopMatrix();
  }
  else
  {    
    // Save color, material attributes. 
    glPushAttrib( GL_LIGHTING_BIT | GL_CURRENT_BIT );    
    
    glColor3f( 1.0, 0.0, 0.0 );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glPushMatrix();
      glListBase( _shadowVol );      
      glCallLists( MAX_LISTS, GL_UNSIGNED_BYTE, _shadowVolLists );
    glPopMatrix();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );    
    
    // Restore. 
    glPopAttrib();
  }
}


void drawScene() 
{   
#if TESTING  
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );
  glLightModelfv( GL_AMBIENT, _lightAmbient );
  glLightModelfv( GL_SPECULAR, _lightSpecular );
  glLightModelfv( GL_DIFFUSE, _lightDiffuse );
  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, _lightAmbient );
  glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, _lightDiffuse );
  if( _mode == !NAVIGATE )
  {  
    buildShadowVolume();
  }

  drawShadowVolume();

#else
  glDisable( GL_LIGHTING );

  buildShadowVolume();

  if( !_debugMode )
  {
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glEnable( GL_LIGHTING );
    glDisable( GL_LIGHT0 );
    
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, _lightAmbient );    
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );

    _viewer->draw();  

    glDepthMask( GL_FALSE );

    glEnable( GL_BLEND );
    glBlendFunc( GL_ONE, GL_ONE );

    GLfloat zero[] = { 0.0, 0.0, 0.0, 1.0 };    
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, zero );
      
    glEnable( GL_STENCIL_TEST );
    glClear( GL_STENCIL_BUFFER_BIT );
    glStencilMask( ~0 );
    
    glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
      
    glStencilFunc( GL_ALWAYS, 0x00, ~0 );
    glStencilOp( GL_KEEP, GL_INCR, GL_KEEP );
    glCullFace( GL_FRONT );
    drawShadowVolume();

    glStencilFunc( GL_ALWAYS, 0x00, ~0 );
    glStencilOp( GL_KEEP, GL_DECR, GL_KEEP );      
    glCullFace( GL_BACK );
    drawShadowVolume(); 
    
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
    glDepthFunc( GL_EQUAL );    

    glCullFace( GL_BACK );
    glEnable( GL_LIGHT0 );
    
    glPushMatrix();    
    glLightfv( GL_LIGHT0, GL_POSITION, _lightPosition );        
    glPopMatrix(); 
    
    glLightfv( GL_LIGHT0, GL_DIFFUSE, _lightDiffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, _lightSpecular );  
    glStencilFunc( GL_EQUAL, 0x00, ~0 );
    glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );
    glDepthFunc( GL_EQUAL );
    _viewer->draw(); 
    
    glDisable( GL_BLEND );
    glDisable( GL_CULL_FACE );
    glDisable( GL_STENCIL_TEST ); 
    glDepthFunc( GL_LESS );
    glDepthMask( GL_TRUE );
  }
  else
  {
    //drawFloor();
    drawShadowVolume( _debugMode );
  }

#endif 
} 


void display()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
  glEnable( GL_DEPTH_TEST );  

  glPushMatrix();
  drawScene();  
  glPopMatrix();

  glPushMatrix();
  GLfloat lightMat[] = { 1.0, 0.0, 0.0, 1.0 };
  glDisable( GL_LIGHTING );  
  glTranslatef( _lightPosition[0], _lightPosition[1], _lightPosition[2] ); 
  glutSolidSphere( 1.0f, 10, 10 );    
  glEnable( GL_LIGHTING );
  glPopMatrix();
  
  glutSwapBuffers();
}


void setPerspective( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{  
  const double pi180 = 0.017453292519943295769236907684886;
  _top= zNear * tan( pi180*fovy/2 );
  _bottom = -_top;
  _right = aspect*_top;
  _left = -_right;
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( _left, _right, _bottom, _top, zNear, zFar );
  glMatrixMode( GL_MODELVIEW );
}


void reshape( int w, int h )
{
  glViewport( 0, 0, w, h );

  glEnable( GL_DEPTH_CLAMP_NV );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  //gluPerspective( 45.0, ( double )w/h, 0.1, 10000.0 );
  //glFrustum( -1.0, 1.0, -1.0, 1.0, 0.1, 10000.0 );

  setPerspective( 45.0, static_cast< double >( w ) / h, 0.1, 10000.0 );
  
  
  double n = 0.1;
  /*double _right = -10.0;
  double _left =  10.0;
  double _top =  10.0;
  double _bottom = -10.0;*/

  //GLdouble mat[] = { ( 2*n ) / ( _right-_left ),
  //                    0, 
  //                    0, 
  //                    0, 
  //                    0, 
  //                    ( 2*n ) / ( _top-_bottom ), 
  //                    0, 
  //                    0, 
  //                    ( _right+_left ) / ( _right-_left ),
  //                    ( _top+_bottom ) / ( _top-_bottom ), 
  //                    -1,
  //                    -1,
  //                    0, 
  //                    0, 
  //                    ( -2*n ),
  //                    0
  //                  };



  //glMultMatrixd( mat );

  //glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( 0.0, 0.0, 60.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}


void idle()
{
  const static float distance = -20.0f;
  static float angle = 0.0f; 

  if( !_pause )
  {
    _lightPosition[0] = distance * cos( angle ); 
    _lightPosition[2] = -60.0 + distance * sin( angle );

    angle = angle + 0.01f;

    if( angle > 360.0f ) 
    {
      angle = 0.0f;
    }

    glutPostRedisplay();
  }
}


void keyboard( unsigned char key, int x, int y )
{
  if( key == 'D' )
  {
    _debugMode = !_debugMode;
  }

  switch( _mode )
  {
    case MOVE_LIGHT: 
    {
      if( key == 'a' )  { _lightPosition[0] = _lightPosition[0] - 1.0; }
      if( key == 'd' )  { _lightPosition[0] = _lightPosition[0] + 1.0; }
      if( key == 'w' )  { _lightPosition[2] = _lightPosition[2] - 1.0; }
      if( key == 's' )  { _lightPosition[2] = _lightPosition[2] + 1.0; }
      if( key == 'q' )  { _lightPosition[1] = _lightPosition[1] + 1.0; }
      if( key == 'e' )  { _lightPosition[1] = _lightPosition[1] - 1.0; }
      break;
    }
    case NAVIGATE: 
    {
      static bool rotate = false;
      
      if( key == 'r' )
        rotate = !rotate;

      if( !rotate )
      {
        if( key == 'a' ) { glTranslatef( -1.0f,  0.0,  0.0 ); }
        if( key == 'd' ) { glTranslatef(  1.0f,  0.0,  0.0 ); }
        if( key == 'w' ) { glTranslatef(  0.0f,  0.0, -1.0 ); }
        if( key == 's' ) { glTranslatef(  0.0f,  0.0,  1.0 ); }
        if( key == 'q' ) { glTranslatef(  0.0f,  1.0,  0.0 ); }
        if( key == 'e' ) { glTranslatef(  0.0f, -1.0,  0.0 ); }        
      }
      else
      {
        if( key == 'a' ) { glRotatef( 1.0f, 0.0f,  1.0f,  0.0f ); }
        if( key == 'd' ) { glRotatef(-1.0f, 0.0f,  1.0f,  0.0f ); }
        if( key == 'w' ) { glRotatef( 1.0f, 1.0f,  1.0f,  0.0f ); }
        if( key == 's' ) { glRotatef( 1.0f,-1.0f,  0.0f,  0.0f ); }
      }

      break;
    }
    case ANIMATE: 
    {
      if( key == 'p' )
      {
        _pause = !_pause;
      }
      break;
    }
  };  

  if( key == 'b' ){ _mode = MOVE_LIGHT; }
  if( key == 'n' ){ _mode = NAVIGATE; }
  if( key == 'm' ){ _mode = ANIMATE; }


  glutPostRedisplay();
}


int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );

  glutInitWindowPosition( 0, 0 );
  glutInitWindowSize( 800, 800 );

  glutCreateWindow( "StencilShadowVolume: Author Aashish Chaudhary" ); 

  init(); 

  glutDisplayFunc( display ); 
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutIdleFunc( idle );

  glutMainLoop();
}