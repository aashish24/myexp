

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

NodeRefPtr     buildScene()
{
  OSG::NodeRefPtr root = OSG::Node::create();
  
  // Just add the terrain here and return the scene.
}


NodeTransitPtr buildStage(int argc, char *argv[])
{  
    hMinusOne = TextureChunk::create();
    hMinusTwo = TextureChunk::create();
    hTemp     = TextureChunk::create();
    hFinal    = TextureChunk::create();
    
    // Build scene here. 
    OSG::NodeRefPtr sceneN = buildScene();
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