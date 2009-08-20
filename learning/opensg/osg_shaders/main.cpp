
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
SHLChunkRefPtr _shl       = 0x00;
SHLChunkRefPtr _shl_2     = 0x00;

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
"uniform vec4   light_positions[6];\n"
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
"     final_color          += vec4( ( diffuse * vec3( 1.0, 0.0, 0.0 ) ), 1.0 );\n"
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
    NodeRefPtr sphere = makeLatLongSphere(50, 50, 5.0);
    
    // Create another sphere. 
    NodeRefPtr sphere_2 = makeLatLongSphere(50,50,5.0);

    NodeRefPtr        transform_node = Node::create();
    TransformRefPtr   transform_core = Transform::create();
    
    transform_node->setCore(transform_core);
    Matrix m; 
    m.setTranslate(15.0, 0.0, 0.0);
    
    transform_core->setMatrix(m);
    
    transform_node->addChild(sphere_2);
    commitChanges();

    // create the shader material
    ChunkMaterialRefPtr cmat = ChunkMaterial::create();
    _shl = SHLChunk::create();
    _shl->setVertexProgram(_vp_program);
    _shl->setFragmentProgram(_fp_program);

    MFVec4f light_positions; 
    light_positions.push_back( Vec4f(    0.0,  100.0,    0.0,  1.0 ) );
    light_positions.push_back( Vec4f(    0.0, -100.0,    0.0,  1.0 ) );
    light_positions.push_back( Vec4f(  100.0,    0.0,    0.0,  1.0 ) );
    light_positions.push_back( Vec4f( -100.0,    0.0,    0.0,  1.0 ) );
    light_positions.push_back( Vec4f(    0.0,    0.0,  100.0,  1.0 ) );
    light_positions.push_back( Vec4f(    0.0,    0.0, -100.0,  1.0 ) );

    MFReal32 lights_used_1;
    lights_used_1.push_back( 0 );
    lights_used_1.push_back( 2 );
    lights_used_1.push_back( 4 );

    MFReal32 lights_used_2;
    lights_used_2.push_back( 1 );
    lights_used_2.push_back( 3 );
    lights_used_2.push_back( 5 );

    /*Vec3f lights_used_1( 0,2,4 );
    Vec3f lights_used_2( 1,3,5 );*/

    _shl->setUniformParameter( "no_lights", 3 );
    _shl->setUniformParameter( "lights_used", lights_used_1 );
    _shl->setUniformParameter( "light_positions", light_positions );

    cmat->addChunk(_shl);
    commitChanges();
    GeometryRefPtr spheregeo = dynamic_cast<Geometry*>(sphere->getCore());
    spheregeo->setMaterial(cmat);    
    commitChanges();  

    ChunkMaterialRefPtr cmat_2 = ChunkMaterial::create(); 
    _shl_2 = dynamic_pointer_cast<SHLChunk>(deepClone(_shl));
    _shl_2->setUniformParameter( "no_lights", 3 );
    _shl_2->setUniformParameter( "lights_used", lights_used_2 );
    _shl_2->setUniformParameter( "light_positions", light_positions );
    commitChanges();  
    cmat_2->addChunk(_shl_2);
    commitChanges();
    GeometryRefPtr spheregeo_2 = dynamic_cast<Geometry*>(sphere_2->getCore());
    spheregeo_2->setMaterial(cmat_2);
    commitChanges();

    _scene->addChild(sphere);
    _scene->addChild(transform_node);
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
