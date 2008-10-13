
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSHLChunk.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *_mgr  = NULL;
NodeRefPtr _scene         = 0x00;

// Storage for all light positions. 
MFVec4f light_positions; 

// Storage for all colors of all lights. 
MFVec4f light_colors; 

// vertex shader program.
static std::string _vp_program =
"// output variables to the fragment program.\n"
"varying vec3 vNormal;\n"
"varying vec3 vViewVec;\n"
"varying vec3 vPos;\n"
"\n"
"void main(void)\n"
"{\n"
"   // Normalize and scale, just because the source\n"
"   // model is not a perfect sphere around origin\n"   
"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"   vPos = vec3(gl_Position);\n"
"   // gl_NormalMatrix the inverse of the upper 3x3 of the view matrix.\n"
"   vNormal   =  gl_NormalMatrix  * gl_Normal;\n"
"\n"
"   vViewVec   = -vec3((gl_ModelViewMatrix * vec4(vPos, 1.0)));\n"
"}\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"varying vec3   vPos;\n"
"uniform int    no_lights;\n"
"uniform float  lights_used[3];\n"
"uniform vec4   light_positions[252];\n"
"uniform vec4   light_colors[252];\n"
"\n"
"// input variables from the vertex program.\n"
"varying vec3 vNormal;\n"
"varying vec3 vViewVec;\n"
"\n"
"void main(void)\n"
"{\n"
"   vec4 final_color = vec4( 0,0,0,0 );\n"
"   for( int i=0; i < 3; i++ )\n"
"   {\n"   
"     const int light_index = lights_used[i];\n"
"     vec4 lightDir         = light_positions[light_index];\n "
"     vec3 nLightVec        = normalize(vec3(lightDir.x, lightDir.y, lightDir.z) - vPos);\n"
"     // Simple diffuse and specular\n"
"     vec3  nNormal         = normalize(vNormal);  // nNormal = normalized normal\n"
"     float diffuse         = clamp( (dot(vNormal, nLightVec)) ,0.0 ,1.0 );\n"
"     vec3  reflectVec      = reflect(-normalize(vViewVec), nNormal);\n"
"     float specular        = pow(clamp( dot(reflectVec, vec3(nLightVec)) ,0.0 ,1.0 ),32.0);\n"
"     final_color          += ( vec4( ( diffuse * vec3( 1.0, 1.0, 1.0 ) ), 1.0 ) * ( light_colors[light_index] ) );\n"
" }\n"   
" gl_FragColor = final_color;\n"
"}\n";

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// redraw the window
void display(void)
{
    static Real32 t = glutGet(GLUT_ELAPSED_TIME);

    Real32 td = (glutGet(GLUT_ELAPSED_TIME) - t) / 100.0f;
    //_shl->setUniformParameter("time", td);

    _mgr->redraw();
}


NodeRefPtr createAndPlaceSpheres( const int& sqGridSize )
{
  if( sqGridSize <= 0 )
  {
    throw "Size of square grid size should be greater than zero. ";
  }

  NodeRefPtr        group_node     = Node::create();
  GroupRefPtr       group_core     = Group::create();

  group_node->setCore( group_core );

  for( int i=1; i <= ( sqGridSize * sqGridSize ); ++i )
  {
    NodeRefPtr        transform_node = Node::create();
    TransformRefPtr   transform_core = Transform::create();
    
    transform_node->setCore(transform_core);
    Matrix m; 

    // We will place the spheres in X-Z plane.  
    int max_size = ceil( static_cast<float>( sqGridSize ) / 2.0 );
    float x_pos  = i - max_size; 
      
    if( static_cast< int >( x_pos ) > static_cast< int >( ( floor( static_cast< double >( sqGridSize ) / 2.0 ) ) ) )
    {
      static int counter = 1;

      if( sqGridSize % 2 == 0 )
      {
        if( ( static_cast<int>( x_pos ) - ( sqGridSize * counter ) ) > max_size )
        {
          ++counter;
        }
      }
      else
      {
        if( ( static_cast<int>( x_pos ) - ( sqGridSize * counter ) ) >= max_size )
        {
          ++counter;
        }
      }

      x_pos = x_pos - sqGridSize * counter;      
    }

    int   temp   = static_cast< int >( ceil( static_cast<float>( sqGridSize ) / 2.0 ) );
    int   temp_2 = static_cast< int >( ceil( static_cast< float >( i ) / sqGridSize  ));
    
    
    float z_pos  = temp_2 - temp;
    

   /* if( static_cast< int >( z_pos ) > static_cast< int >( ( static_cast< float >( sqGridSize ) / 2.0 ) ) )
    {
      z_pos = -static_cast< float >( sqGridSize ) / 2.0;
    }*/

    m.setTranslate(x_pos, 0.0, z_pos);
    transform_core->setMatrix( m );

    NodeRefPtr sphere  = makeLatLongSphere( 50, 50, 1.0 );
    GeometryRefPtr sphere_geo = dynamic_cast<Geometry*>(sphere->getCore());

     // create the shader material
    ChunkMaterialRefPtr cmat = ChunkMaterial::create();

    MFReal32 lights_used;
    srand( time(NULL) );
    for( int no=0; no < 3; ++no )
    {           
      lights_used.push_back( rand() % 252 );
    }

    SHLChunkRefPtr _shl = SHLChunk::create();
    _shl->setVertexProgram(_vp_program);
    _shl->setFragmentProgram(_fp_program);   
    _shl->setUniformParameter( "no_lights", 3 );
    _shl->setUniformParameter( "lights_used", lights_used );
    _shl->setUniformParameter( "light_positions", light_positions );
    _shl->setUniformParameter( "light_colors", light_colors );
    
    cmat->addChunk(_shl);    
    commitChanges();

    sphere_geo->setMaterial(cmat);    

    transform_node->addChild( sphere );
    group_node->addChild( transform_node ); 
    commitChanges();     
  }

  return group_node;
}


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // create the scene
    _scene = makeCoredNode<Group>();

    // create a sphere.
    //NodeRefPtr sphere = makeLatLongSphere(50, 50, 5.0);
    
    // Create another sphere. 
    //NodeRefPtr sphere_2 = makeLatLongSphere(50,50,5.0);

    //NodeRefPtr        transform_node = Node::create();
    //TransformRefPtr   transform_core = Transform::create();
    
    //transform_node->setCore(transform_core);
    //Matrix m; 
    //m.setTranslate(15.0, 0.0, 0.0);
    
    //transform_core->setMatrix(m);
    
    //transform_node->addChild(sphere_2);
    commitChanges();    

    for( unsigned int i=0; i < 63; ++i )
    {
      light_positions.push_back( Vec4f(    0.0,  100.0,    0.0,  1.0 ) );
      light_positions.push_back( Vec4f(    0.0, -100.0,    0.0,  1.0 ) );
      light_positions.push_back( Vec4f(  100.0,    0.0,    0.0,  1.0 ) );
      light_positions.push_back( Vec4f( -100.0,    0.0,    0.0,  1.0 ) );
    }   

     for( unsigned int i=0; i < 63; ++i )
    {
      light_colors.push_back( Vec4f( 0.0,  1.0,  0.0,  1.0 ) );
      light_colors.push_back( Vec4f( 0.0,  0.0,  1.0,  1.0 ) );
      light_colors.push_back( Vec4f( 0.0,  1.0,  0.0,  1.0 ) );
      light_colors.push_back( Vec4f( 0.0,  0.0,  1.0,  1.0 ) );
    }

   /* MFReal32 lights_used_1;
    lights_used_1.push_back( 0 );
    lights_used_1.push_back( 4 );
    lights_used_1.push_back( 7 );

    MFReal32 lights_used_2;
    lights_used_2.push_back( 1 );
    lights_used_2.push_back( 3 );
    lights_used_2.push_back( 6 );*/
    

    /*ChunkMaterialRefPtr cmat_2 = ChunkMaterial::create(); 
    _shl_2 = dynamic_pointer_cast<SHLChunk>(deepClone(_shl));
    _shl_2->setUniformParameter( "no_lights", 3 );
    _shl_2->setUniformParameter( "lights_used", lights_used_2 );
    _shl_2->setUniformParameter( "light_positions", light_positions );
    _shl_2->setUniformParameter( "light_colors", light_colors );
    commitChanges();  
    cmat_2->addChunk(_shl_2);
    commitChanges();*/

    _scene->addChild( createAndPlaceSpheres( 23 ) );

    commitChanges();  

    // the connection between GLUT and OpenSG
    GLUTWindowRefPtr gwin= GLUTWindow::create();
    gwin->setGlutId(winid);
    //gwin->addPort(svp);
    gwin->init();

    commitChanges();

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot  (_scene);

    //svp->setCamera(_mgr->getCamera());

    _mgr->turnHeadlightOff();

    // show the whole scene
    _mgr->showAll();
    //_mgr->getNavigator()->setFrom(Pnt3f(0.0, 31, 47));

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
            OSG::osgExit();
            exit(0);
        break;
        case 'w':
            SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.\n");
        break;

        case 's':
        {
            _mgr->setStatistics(!_mgr->getStatistics());
        }
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
