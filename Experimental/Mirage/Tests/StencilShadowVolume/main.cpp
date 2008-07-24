
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

#include "MsgCore/Material.h"

#include <list>

static bool animate = false;

static bool two_sided = false;

static bool _pause = false;

static const GLfloat lightAmbient[]   = { 1.0f, 0.6f, 0.6f, 1.0f };
static const GLfloat lightDiffuse[]   = { 1.0f, 0.6f, 0.6f, 1.0f };
static const GLfloat lightSpecular[]  = { 1.0f, 0.6f, 0.6f, 1.0f };

static       GLfloat lightPosition[]  = { -8.0f, 4.0f, 0.0f, 1.0 };

Msg::MsgCore::SmartPtr< Msg::MsgCore::Material > _matBlue   = new Msg::MsgCore::Material();
Msg::MsgCore::SmartPtr< Msg::MsgCore::Material > _matRed    = new Msg::MsgCore::Material();
Msg::MsgCore::SmartPtr< Msg::MsgCore::Material > _matShadow = new Msg::MsgCore::Material();


Msg::MsgCore::SmartPtr< Msg::MsgCore::GLSLProgram > extrusionProgram = new Msg::MsgCore::GLSLProgram();
Msg::MsgCore::SmartPtr< Msg::MsgCore::GLSLShader >  vertShader = new Msg::MsgCore::GLSLShader( Msg::MsgCore::GLSLShader::VERTEX_SHADER );
Msg::MsgCore::SmartPtr< Msg::MsgCore::GLSLShader >  fragShader = new Msg::MsgCore::GLSLShader( Msg::MsgCore::GLSLShader::FRAGMENT_SHADER );

Msg::MsgCore::SmartPtr< Msg::MsgCore::Viewer > _viewer = new Msg::MsgCore::Viewer();

// Create scene _root node. 
Msg::MsgCore::SmartPtr< Msg::MsgCore::Group > _root( new Msg::MsgCore::Group() );



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
  Msg::MsgMath::Vec3i _faceIndex;
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
 /* vertShader->sourceAsFile( "PositionExtrusionShader.vert" );
  fragShader->sourceAsFile( "PositionExtrusionShader.frag" );

  vertShader->contextInit();
  fragShader->contextInit();

  extrusionProgram->attach( vertShader.get() );
  extrusionProgram->attach( fragShader.get() );

  extrusionProgram->link();*/

  //glEnable( GL_CULL_FACE );
  //glCullFace( GL_FRONT );

  glClearColor( 0.0, 0.0, 0.0, 1.0 );

  // Initialize viewer. 
  _viewer->init();
  
  if( !_root.valid() )
  {
    std::cerr << " ERROR: Out of memory or invalid pointer. " << std::endl;
    std::exit( 0 );
  }

  // Read geometry files. 
  Msg::MsgCore::SmartPtr< Msg::MsgCore::Node > model =  
    Msg::MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\head\\Mirage\\Data\\Models\\Sphere.obj" );

  if( model.valid() )
  {
    _root->addChild( model.get() );
  }

  Msg::MsgCore::SmartPtr< Msg::MsgCore::Node > floor =  
    Msg::MsgDB::FileRead::readFile( "E:\\aashish\\src\\osve\\head\\Mirage\\Data\\Models\\Floor.obj" );

  if( floor.valid() )
  {
    _root->addChild( floor.get() );    
  }

  _viewer->sceneData( _root.get() );

  // Set materials. 
  if( _matBlue.valid() )
  {
    _matBlue->setProperty( DIFFUSE, Msg::MsgMath::Vec4f( 0.0, 0.0, 0.5, 1.0 ) );
    _matBlue->setProperty( AMBIENT, Msg::MsgMath::Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
    _matBlue->setProperty( SPECULAR, Msg::MsgMath::Vec4f( 0.0, 0.0, 0.5, 1.0 ) );


    model->getOrCreateStateSet()->attribute( _matBlue.get() );
  }
  else
  {
    // Warning. 
  }

  // Set materials. 
  if( _matRed.valid() )
  {
    _matRed->setProperty( DIFFUSE, Msg::MsgMath::Vec4f( 0.0, 0.7, 0.1, 1.0 ) );
    _matRed->setProperty( AMBIENT, Msg::MsgMath::Vec4f( 0.0, 0.0, 0.0, 1.0 ) );
    _matRed->setProperty( SPECULAR, Msg::MsgMath::Vec4f( 0.0, 0.7, 0.1, 1.0 ) );

    floor->getOrCreateStateSet()->attribute( _matRed.get() );
  }
  else
  {
    // Warning. 
  }

   // Set materials. 
  if( _matShadow.valid() )
  {
    _matShadow->setProperty( DIFFUSE, Msg::MsgMath::Vec4f( 0.1, 0.1, 0.1, 0.5 ) );
    _matShadow->setProperty( AMBIENT, Msg::MsgMath::Vec4f( 0.1, 0.1, 0.1, 0.5 ) );
    _matShadow->setProperty( SPECULAR, Msg::MsgMath::Vec4f( 0.1, 0.1, 0.1, 0.5 ) );

    //floor->getOrCreateStateSet()->attribute( _matRed.get() );
  }
  else
  {
    // Warning. 
  }
}

// @todo: Two issues. 
// 1. How we are going to draw in the same coordinate system as where 
// we have the original geometry as still we dont have the transform node. 
// 2. We are not iterating over the nodes which are group nodes under the _root? 

void drawShadowVolume()
{
  // Lets query the vertices. 
  Msg::MsgCore::Node* node = _viewer->sceneData(); 
  
  // Check for valid node. 
  if( !node )
  {
    std::cerr << " WARNING: Invalid or NULL node. " << std::endl;
    return;
  }
   
  Msg::MsgCore::SmartPtr< Msg::MsgCore::Group > gr = node->asGroup();
  
  // Now check each child of the _root node. 
  // Grab any geometry. 
  // Construct shadow volume out of it. 

  // Now currently checking only at one level ( ignorning group  nodes ). 
  for( size_t index = 0; index < gr->children().size(); ++index )
  {
    Msg::MsgCore::SmartPtr< Msg::MsgCore::Node > node = gr->child( index );

    Msg::MsgCore::Geode* ge = node->asGeode();

    if( ge ) 
    {
      std::vector< Msg::MsgCore::SmartPtr< Msg::MsgCore::Drawable > > drawables = ge->getDrawableList();

      for( size_t i = 0; i < drawables.size(); ++i ) 
      {
        Msg::MsgCore::Geometry* geom = dynamic_cast< Msg::MsgCore::Geometry* >( drawables[i].get() );
        if( geom )
        {
          std::vector< Triangle > _capTriangles; 
          std::list< Edge > _edges;

          Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3iArray > indices    = geom->vertexIndices();
          Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3iArray > nIndices   = geom->normalIndices();
          Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array >  vertices    = geom->vertexArray();
          Msg::MsgCore::SmartPtr< Msg::MsgCore::Vec3Array >  normals     = geom->normalArray();
          
          Msg::MsgMath::Vec3d lightPos = Msg::MsgMath::Vec3d( lightPosition[0], lightPosition[1], lightPosition[2] );

          for( size_t k = 0; k < indices->size() ; ++k ) 
          {
            int i1 = indices->at( k )[0];
            int i2 = indices->at( k )[1];
            int i3 = indices->at( k )[2];

            // We may get the geometry which are not called single index geometries.  
            int ni1 = nIndices->at( k )[0];
            int ni2 = nIndices->at( k )[1];
            int ni3 = nIndices->at( k )[2];
              
            Msg::MsgMath::Vec3d lightDir1 = lightPos - vertices->at( i1 );
            lightDir1.normalize();

            Msg::MsgMath::Vec3d lightDir2 = lightPos - vertices->at( i2 );
            lightDir2.normalize();
            
            Msg::MsgMath::Vec3d lightDir3 = lightPos - vertices->at( i3 );  
            lightDir3.normalize();
            
            Msg::MsgMath::Vec3d normal1 =  normals->at( ni1 );
            Msg::MsgMath::Vec3d normal2 =  normals->at( ni2 );
            Msg::MsgMath::Vec3d normal3 =  normals->at( ni3 );

            int count = 0;

            bool edge1Passed = false; 

            if( ( normal1.dot( lightDir1 ) > 0 ) && ( normal2.dot( lightDir2 ) > 0 ) )
            {
              edge1Passed = true;
            }
          
            if( two_sided )
            {
              if( ( -normal1.dot( lightDir1 ) > 0 ) && ( -normal2.dot( lightDir2 ) > 0 ) )
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
            
            if( ( normal2.dot( lightDir2 ) > 0 ) && ( normal3.dot( lightDir3 ) > 0 ) )
            {
              edge2Passed = true;
            }

            if( two_sided )
            {
              if( ( -normal2.dot( lightDir2 ) > 0 ) && ( -normal3.dot( lightDir3 ) > 0 ) )
              {
                edge2Passed = true;
              }
            }

            if( edge2Passed )
            {
              //std::cout << "Vertex 2 passed: " << std::endl;

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

            if( ( normal3.dot( lightDir3 ) > 0 ) && ( normal1.dot( lightDir1 ) > 0 ) )  
            {
              edge3Passed = true;
            }

            if( two_sided )
            {
              if( ( -normal3.dot( lightDir3 ) > 0 ) && ( -normal1.dot( lightDir1 ) > 0 ) )  
              {
                edge3Passed = true;
              } 
            }

            if( edge3Passed )
            {
              //std::cout << "Vertex 3 passed: " << std::endl;

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
              triangle._faceIndex = Msg::MsgMath::Vec3i( i1, i2, i3 );
              _capTriangles.push_back( triangle );

            }

          } // End  for( size_t k = 0; k < indices->size() ; ++k )            
        
          _edges.unique( compare() );

          std::vector< Msg::MsgMath::Vec3d > _extendedVertices;          

          std::list< Edge >::iterator jItr = _edges.begin();

          const float extensionFactor = 10.0f;

          // Use display list. 
          for( jItr; jItr != _edges.end(); ++jItr )
          {            
            glBegin( GL_QUADS );
              
              glVertex3dv( vertices->at( jItr->_vertex2._vertexIndex ).front() );
              glVertex3dv( vertices->at( jItr->_vertex1._vertexIndex ).front() );
              
              Msg::MsgMath::Vec3d vertex11 = vertices->at( jItr->_vertex2._vertexIndex );
              Msg::MsgMath::Vec3d vertex41( vertex11[0] - lightPos[0], vertex11[1] - lightPos[1], vertex11[2] - lightPos[2] );
              
              vertex41 = vertex11 + vertex41 * extensionFactor;

              Msg::MsgMath::Vec3d vertex22 = vertices->at( jItr->_vertex1._vertexIndex );
              Msg::MsgMath::Vec3d vertex42( vertex22[0] - lightPos[0], vertex22[1] - lightPos[1], vertex22[2] - lightPos[2] );              
              
              
              vertex42 = vertex22 + vertex42 * extensionFactor;

              glVertex3dv( vertex42.front() );              
              glVertex3dv( vertex41.front() );

            glEnd();                          

            _extendedVertices.push_back( vertex42 );
            _extendedVertices.push_back( vertex41 );
          }

          
          /////////////////////////////////////////////////////////////////////
          // Front cap. 
          //

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


          /////////////////////////////////////////////////////////////////////
          // Back cap. 
          //

          // Drawing in the reverse order of drawing for front cap. 
          glBegin( GL_POLYGON );
          int count = 0;
          for( int i = _extendedVertices.size()-1; i >= 0 ; --i )
          {            
              if( i % 2 == 0 )
              {
                glVertex3dv( _extendedVertices[i].front() );
              }
          }
          glEnd();

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

  const GLfloat shadowMat[] = { 0.0, 0.0, 0.0, 0.5 };
  
  //glMaterialfv( GL_FRONT, GL_AMBIENT, &objectMat[0] );    
  //glMaterialfv( GL_FRONT, GL_DIFFUSE, &objectMat[0] );    
    
    
  // @start. For testing purposes.

  //drawShadowVolume();

  //glPolygonMode( GL_BACK, GL_LINE );
  //glPolygonMode( GL_FRONT, GL_LINE );
  //glEnable( GL_CULL_FACE );
  //glCullFace( GL_FRONT );
  //drawShadowVolume();

  //glClearStencil( 0x00 );
  //glEnable( GL_STENCIL_TEST );
  //glClear( GL_STENCIL_BUFFER_BIT );

  //glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
  ////glDepthMask( GL_FALSE );
  //glStencilFunc( GL_ALWAYS, 0x1, 0x1 );
  //glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );
  ////glCullFace( GL_FRONT );
  //drawQuad();
  //// _viewer->draw();

  //glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
  //glDepthMask( GL_TRUE );
  //glDepthFunc( GL_LEQUAL );

  //glStencilFunc( GL_NOTEQUAL, 0x1, 0x1 );
  //glDisable( GL_LIGHTING );
  //glColor3f( 0.0, 1.0, 0.0 );
  //drawQuad();
  ////_viewer->draw();

  //glDisable( GL_STENCIL_TEST );

  // @end: For testing purposes.   

  _viewer->draw();

#if 0
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
  const static float distance = -10.0f;
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
    glRotatef( 1.0f, 0.0f, 1.0f, 0.0f );
  }

  if( key == 'd' ) 
  {
    glRotatef( -1.0f, 0.0f, 1.0f, 0.0f );
  }

  if( key == 'w' ) 
  {
    glRotatef( 1.0f, 1.0f, 0.0f, 0.0f );
  }

  if( key == 's' )
  {
    glRotatef( -1.0f, 1.0f, 0.0f, 0.0f );
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