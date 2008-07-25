
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

using namespace Msg;

static bool animate   = false;
static bool two_sided = false;
static bool _pause    = true;

static const GLfloat lightAmbient[]   = { 1.0f, 0.6f, 0.6f, 1.0f };
static const GLfloat lightDiffuse[]   = { 1.0f, 0.6f, 0.6f, 1.0f };
static const GLfloat lightSpecular[]  = { 1.0f, 0.6f, 0.6f, 1.0f };

static       GLfloat lightPosition[]  = { -5.0f, 3.0f, 0.0f, 1.0 };

MsgCore::SmartPtr< MsgCore::Material > _matBlue   = new MsgCore::Material();
MsgCore::SmartPtr< MsgCore::Material > _matRed    = new MsgCore::Material();
MsgCore::SmartPtr< MsgCore::Material > _matShadow = new MsgCore::Material();

MsgCore::SmartPtr< MsgCore::GLSLProgram > extrusionProgram  = new MsgCore::GLSLProgram();
MsgCore::SmartPtr< MsgCore::GLSLShader >  vertShader        = new MsgCore::GLSLShader( MsgCore::GLSLShader::VERTEX_SHADER );
MsgCore::SmartPtr< MsgCore::GLSLShader >  fragShader        = new MsgCore::GLSLShader( MsgCore::GLSLShader::FRAGMENT_SHADER );

MsgCore::SmartPtr< MsgCore::Viewer > _viewer      = new MsgCore::Viewer();

// Create scene _root node. 
MsgCore::SmartPtr< MsgCore::Group > _root( new MsgCore::Group() );


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


void init()
{
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );  

  //glLightfv( GL_LIGHT0, GL_AMBIENT, lightAmbient );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse );
  glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpecular );  

  // @todo: Planning to perform extraction of vertices via shaders. 
  // Commented out for time being. 
  /* 
  vertShader->sourceAsFile( "PositionExtrusionShader.vert" );
  fragShader->sourceAsFile( "PositionExtrusionShader.frag" );

  vertShader->contextInit();
  fragShader->contextInit();

  extrusionProgram->attach( vertShader.get() );
  extrusionProgram->attach( fragShader.get() );

  extrusionProgram->link();
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
    MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\head\\Mirage\\Data\\Models\\Box.obj" );

  if( model.valid() )
  {
    _root->addChild( model.get() );
  }

  MsgCore::SmartPtr< MsgCore::Node > floor =  
    MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\head\\Mirage\\Data\\Models\\Floor.obj" );

  if( floor.valid() )
  {
    _root->addChild( floor.get() );    
  }

  _viewer->sceneData( _root.get() );

  // Set materials. 
  if( _matBlue.valid() )
  {
    _matBlue->setProperty( DIFFUSE, MsgMath::Vec4f( 0.0, 0.0, 0.5, 1.0 ) );
    _matBlue->setProperty( AMBIENT, MsgMath::Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
    _matBlue->setProperty( SPECULAR, MsgMath::Vec4f( 0.0, 0.0, 0.5, 1.0 ) );


    model->getOrCreateStateSet()->attribute( _matBlue.get() );
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

    floor->getOrCreateStateSet()->attribute( _matRed.get() );
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
}


//Convert a openGL Matrix into Matrix44d. 
MsgMath::Matrix44d convert( GLdouble* matrix ) 
{
  MsgMath::Matrix44d mat;
  mat.set( matrix );

  return mat;
}


// @todo: Two issues. 
// 1. How we are going to draw in the same coordinate system as where 
// we have the original geometry as still we dont have the transform node. 
// 2. We are not iterating over the nodes which are group nodes under the _root? 

void drawShadowVolume()
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
  for( size_t index = 0; index < gr->children().size(); ++index )
  {
    MsgCore::SmartPtr< MsgCore::Node > node = gr->child( index );

    MsgCore::Geode* geode = node->asGeode();

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
          std::list< Edge > _edges;

          MsgCore::SmartPtr< MsgCore::Vec3iArray > indices    = geom->vertexIndices();
          MsgCore::SmartPtr< MsgCore::Vec3iArray > nIndices   = geom->normalIndices();
          MsgCore::SmartPtr< MsgCore::Vec3Array >  vertices    = geom->vertexArray();
          MsgCore::SmartPtr< MsgCore::Vec3Array >  normals     = geom->normalArray();
          
          MsgMath::Vec4d lightPos = MsgMath::Vec4d( lightPosition[0], lightPosition[1], lightPosition[2], 1 );

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

            MsgMath::Vec4d lightDir1 = lightPos - MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vecModi1 );
            lightDir1.normalize();

            MsgMath::Vec4d lightDir2 = lightPos - MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vecModi2 );
            lightDir2.normalize();
            
            MsgMath::Vec4d lightDir3 = lightPos - MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vecModi3 );;  
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
          
            if( two_sided )
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

              _edges.push_back( edge );

              ++count;
            }           

            bool edge2Passed = false;
            
            if( ( normal2Modi.dot( lightDir2 ) > 0 ) && ( normal3Modi.dot( lightDir3 ) > 0 ) )
            {
              edge2Passed = true;
            }

            if( two_sided )
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

              _edges.push_back( edge );

              ++count;
            }
            
            ///////////////////////////////////////////////////////////////////
            // 
            // Third edge.  
            //

            bool edge3Passed = false;

            if( ( normal3Modi.dot( lightDir3 ) > 0 ) && ( normal1Modi.dot( lightDir1 ) > 0 ) )  
            {
              edge3Passed = true;
            }

            if( two_sided )
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

              _edges.push_back( edge );

              ++count;
            }

            if( count == 3 )
            {
              Triangle triangle;
              triangle._faceIndex = MsgMath::Vec3i( i1, i2, i3 );
              _capTriangles.push_back( triangle );
            }

          } // End  for( size_t k = 0; k < indices->size() ; ++k )            
        

          // Remove duplicate edges. 
          _edges.unique( compare() );

          // Extrude the vertices. 
          std::vector< MsgMath::Vec4d > _extendedVertices;          
          std::list< Edge >::iterator jItr = _edges.begin();
          const float extensionFactor = 5.0f;

          // @Todo: Use display list. 
          for( jItr; jItr != _edges.end(); ++jItr )
          {            
            glPushMatrix();
            glLoadIdentity();
            glBegin( GL_QUADS );
              
              MsgMath::Vec3d vec3d1 = vertices->at( jItr->_vertex2._vertexIndex );
              MsgMath::Vec3d vec3d2 = vertices->at( jItr->_vertex1._vertexIndex );
              
              MsgMath::Vec4d vec4d1( vec3d1[0], vec3d1[1], vec3d1[2], 1.0 );
              MsgMath::Vec4d vec4d2( vec3d2[0], vec3d2[1], vec3d2[2], 1.0 );

              vec4d1 = MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vec4d1 );
              vec4d2 = MsgMath::MatrixVecOps::mult< MsgMath::Matrix44d, MsgMath::Vec4d >( mat, vec4d2 );
              
              //glVertex3dv( vertices->at( jItr->_vertex2._vertexIndex ).front() );
              //glVertex3dv( vertices->at( jItr->_vertex1._vertexIndex ).front() );
              
              //MsgMath::Vec3d vertex11 = vertices->at( jItr->_vertex2._vertexIndex );
              //MsgMath::Vec4d vertex41( vertex11[0] - lightPos[0], vertex11[1] - lightPos[1], vertex11[2] - lightPos[2] );
              
              MsgMath::Vec4d vertex41( vec4d1[0] - lightPos[0], vec4d1[1] - lightPos[1], vec4d1[2] - lightPos[2], 1.0 );
              vertex41 = vec4d1 + vertex41 * extensionFactor;
              vertex41[3] = 1.0;

              //MsgMath::Vec3d vertex22 = vertices->at( jItr->_vertex1._vertexIndex );
              //MsgMath::Vec3d vertex42( vertex22[0] - lightPos[0], vertex22[1] - lightPos[1], vertex22[2] - lightPos[2] );              
              //vertex42 = vertex22 + vertex42 * extensionFactor;

              MsgMath::Vec4d vertex42( vec4d2[0] - lightPos[0], vec4d2[1] - lightPos[1], vec4d2[2] - lightPos[2], 1.0 );
              vertex42 = vec4d2 + vertex42 * extensionFactor;
              vertex42[3] = 1.0;

              //glVertex3dv( vertex42.front() );              
              //glVertex3dv( vertex41.front() );

              glVertex4dv( vec4d1.front() );
              glVertex4dv( vec4d2.front() );
              glVertex4dv( vertex42.front() );
              glVertex4dv( vertex41.front() );

            glEnd();                                      
            glPopMatrix();

            _extendedVertices.push_back( vertex42 );
            _extendedVertices.push_back( vertex41 );
          }

          
          /////////////////////////////////////////////////////////////////////
          // Front cap. 
          //

          glPushMatrix();
          std::vector< Triangle >::const_iterator constItr;
          glEnable( GL_POLYGON_OFFSET_FILL );
          glPolygonOffset( 0.0f, 2.0f );
          glBegin( GL_POLYGON );
          for( constItr = _capTriangles.begin(); constItr != _capTriangles.end(); ++constItr )
          {           
            glVertex3dv( vertices->at( constItr->_faceIndex[0] ).front() );
            glVertex3dv( vertices->at( constItr->_faceIndex[1] ).front() );
            glVertex3dv( vertices->at( constItr->_faceIndex[2] ).front() );            
          }
          glEnd();
          glDisable( GL_POLYGON_OFFSET_FILL );  
          glPopMatrix();


          /////////////////////////////////////////////////////////////////////
          // Back cap. 
          //

          // Drawing in the reverse order of drawing for front cap. 
          glPushMatrix();
          glLoadIdentity();
          glBegin( GL_POLYGON );
          int count = 0;
          for( int i = _extendedVertices.size()-1; i >= 0 ; --i )
          {            
              if( i % 2 == 0 )
              {
                glVertex4dv( _extendedVertices[i].front() );
              }
          }
          glEnd();
          glPopMatrix();

        } // End if( geom  )

      } // End for( size_t i = 0; i < drawables.size(); ++i ) 

    } // End if( ge ) 

  } // End  for loop. 

}


void drawFloor()
{
  glBegin( GL_QUADS );
    glVertex3f( -20.0,  0.0,  20.0 );
    glVertex3f(  20.0,  0.0,  20.0 );
    glVertex3f(  20.0,  0.0, -20.0 );
    glVertex3f( -20.0,  0.0, -20.0 );
  glEnd();
}


void drawQuad()
{
  glBegin(GL_QUADS);
    glVertex2f ( -1.0, 0.0 );
    glVertex2f ( 0.0, 1.0  );
    glVertex2f ( 1.0, 0.0  );
    glVertex2f ( 0.0, -1.0 );
   glEnd();
}


void drawScene() 
{ 
  glEnable( GL_DEPTH_TEST );  
  glDepthMask( GL_TRUE );
  glDepthFunc( GL_LEQUAL );
  
  /*glColor3f( 1.0, 1.0, 1.0 );
  drawShadowVolume();*/

#if 1
   _viewer->draw();

  // Turn on OpenGL states.
  // Requied for the algorithm. 
  glEnable( GL_CULL_FACE );    
  glClearStencil( 0x00 );
  glEnable( GL_STENCIL_TEST );
  glClear( GL_STENCIL_BUFFER_BIT );
  
  glDepthMask( GL_FALSE );
  glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
    
  glStencilFunc( GL_ALWAYS, 0x00, 0xff );
  glStencilOp( GL_KEEP, GL_INCR, GL_KEEP );
  glCullFace( GL_FRONT );
  drawShadowVolume();

  glStencilFunc( GL_ALWAYS, 0x00, 0xff );
  glStencilOp( GL_KEEP, GL_DECR, GL_KEEP );      
  glCullFace( GL_BACK );
  drawShadowVolume(); 

  glDepthMask( GL_TRUE );
  glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
  glDepthFunc( GL_LEQUAL );

  // Now render the shadow part. 
  // @todo: I still dont understand this glStencilFunc. 
  glStencilFunc( GL_EQUAL, 0x1, 0x1 );
  glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
  
  glCullFace( GL_BACK );
 
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  //glMaterialfv( GL_FRONT, GL_AMBIENT,  &shadowMat[0] ); 
  //glMaterialfv( GL_FRONT, GL_DIFFUSE,  &shadowMat[0] ); 
  //glMaterialfv( GL_FRONT, GL_SPECULAR, &shadowMat[0] ); 
  
  if( _matShadow.valid() )
  {
    _root->getOrCreateStateSet()->attribute( _matShadow.get(), IStateAttribute::OVERRIDE | IStateAttribute::ON );
  }  

  _viewer->draw();

  if( _matShadow.valid() )
  {
    _root->getOrCreateStateSet()->attribute( _matShadow.get(), IStateAttribute::OFF );
  }  

  // Turn off OpenGL states. 
  glDisable( GL_CULL_FACE );
  glDisable( GL_STENCIL_TEST );  

#endif 
} 


void display()
{

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glEnable( GL_DEPTH_TEST );
  
  glPushMatrix();
  glLoadIdentity();
  glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
  glTranslatef( lightPosition[0], lightPosition[1], lightPosition[2] );
  glDisable( GL_LIGHTING );
  glutSolidSphere( 1.0f, 10, 10 );
  glEnable( GL_LIGHTING );
  glPopMatrix();

  //glRotatef( 10.0f, 1.0f, 0.0f, 0.0f );
  //glRotatef( 10.0f, 0.0f, 1.0f, 0.0f );
  drawScene();

  /*
  glClear( GL_STENCIL_BUFFER_BIT );
  glEnable( GL_STENCIL_TEST );
  glStencilFunc( GL_ALWAYS, 0, ~0 );  

  glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
  glDepthMask( GL_FALSE );
  
  glStencilOp( GL_KEEP, GL_INCR, GL_KEEP );
  glCullFace( GL_FRONT );
  
  drawScene(); 

  glStencilOp( GL_KEEP, GL_DECR, GL_KEEP );
  glCullFace( GL_BACK );
  
  drawScene(); 

  glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
  glDepthFunc( GL_EQUAL );
  glStencilFunc( GL_GEQUAL, 1, 1 );
  glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );
  
  glCullFace( GL_BACK );
  drawScene();

  glDisable( GL_STENCIL_TEST );
  */

  glutSwapBuffers();
}


void reshape( int w, int h )
{

  glViewport( 0, 0, w, h );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  gluPerspective( 45.0, ( float )w/h, 0.1, 1000.0 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( 0.0, 0.0, 60.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}


void idle()
{
  const static float distance = -20.0f;
  static float angle = 0.0f; 

  if( !_pause )
  {
    lightPosition[0] = distance * cos( angle ); 
    lightPosition[2] = -60.0 + distance * sin( angle );

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
  if( key == 'a' )
  {
    //glRotatef( 1.0f, 0.0f, 1.0f, 0.0f );
    lightPosition[0] = lightPosition[0] - 1.0;
  }

  if( key == 'd' ) 
  {
    //glRotatef( -1.0f, 0.0f, 1.0f, 0.0f );
    lightPosition[0] = lightPosition[0] + 1.0;
  }

  if( key == 'w' ) 
  {
    //glRotatef( 1.0f, 1.0f, 0.0f, 0.0f );
    lightPosition[2] = lightPosition[2] - 1.0;
  }

  if( key == 's' )
  {
    //glRotatef( -1.0f, 1.0f, 0.0f, 0.0f );
    lightPosition[2] = lightPosition[2] + 1.0;
  }

  if( key == 'u' )
  {
    lightPosition[1] = lightPosition[1] + 1.0;
  }

  if( key == 'j' )
  {
    lightPosition[1] = lightPosition[1] - 1.0;
  }

  if( key == 'p' )
  {
    _pause = !_pause;
  }

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