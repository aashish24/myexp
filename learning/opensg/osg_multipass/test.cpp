
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGComponentTransform.h>

#include <OpenSG/OSGSimpleStage.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGFrameBufferObject.h>
#include <OpenSG/OSGTextureBuffer.h>
#include <OpenSG/OSGRenderBuffer.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGTexGenChunk.h>
#include <OpenSG/OSGTwoSidedLightingChunk.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGImageFunctions.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGTextureTransformChunk.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>

OSG_USING_NAMESPACE

// This is how its going to work. 

// Load the scene 
// Load shaders for the first stage. (input for shaders = height(1) and terrain as height map)
// Render the output to texture
// Use this current scene for the stage 
// Now Load different shader on the same scene with input= 1. height(0), and height(1), depth texture, deltaT and deltaX 
// Render the output to another texture. 
 
TextureChunkRefPtr  hMinusOne; 
TextureChunkRefPtr  hMinusTwo;
TextureChunkRefPtr  hTemp;
TextureChunkRefPtr  hFinal;
TextureChunkRefPtr  terrainHeightField;

SimpleSceneManager   *mgr;

///////////////////////////////////////////////////////////////////////////////
//
// Functions. 
//
///////////////////////////////////////////////////////////////////////////////

NodeRefPtr buildScene()
{
  OSG::NodeRefPtr rootN = OSG::Node::create();
  OSG::GroupRefPtr root = OSG::Group::create();
    
  rootN->setCore(root);
  
  return rootN;

  // Just add the terrain here and return the scene.
}


NodeRefPtr buildStage(int argc, char *argv[])
{  
    hMinusOne = TextureChunk::create();
    hMinusTwo = TextureChunk::create();
    hTemp     = TextureChunk::create();
    hFinal    = TextureChunk::create();
    
    // Load the images.
    ImageRefPtr hMinusOneImg = Image::create();
    hMinusOneImg->read("test.png");
    if(hMinusOneImg)
    {
      hMinusTwo->setImage(hMinusOneImg);
    }

    ImageRefPtr hMinusTwoImg = Image::create();
    hMinusTwoImg->read("test.png");
    if(hMinusTwoImg)
    {
      hMinusTwo->setImage(hMinusTwoImg);
    }

    ImageRefPtr terrainHFImg = Image::create();
    terrainHFImg->read("test.png");
    if(terrainHFImg)
    {
      terrainHeightField->setImage(terrainHFImg);
    }
      
    // Build scene here. 
    OSG::NodeRefPtr sceneN = buildScene();
}


// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}


// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}


// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}


void update(void)
{
    glutPostRedisplay();
}


// redraw the window
void display( void )
{
    /*
    static Real64 t0 = OSG::getSystemTime();

    // get the current time
    Real64 t = OSG::getSystemTime() - t0;
    
    Matrix m;
    Quaternion q;
    q.setValueAsAxisDeg(0, 1, 0, t * 10.f);
    m.setRotate(q);
    modelTrans->setMatrix(m);
    */
    
    commitChangesAndClear();
    
    mgr->redraw();
}


// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            delete mgr;            
            osgExit();
            exit(0);
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
    glutIdleFunc(update);

    return winid;
}


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        GLUTWindowRefPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();

        NodeRefPtr scene = buildStage(argc, argv);
        
        commitChanges();
        
        // create the SimpleSceneManager helper
        mgr = new SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}