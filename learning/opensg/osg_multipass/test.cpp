
#include <string>


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

#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGVisitSubTree.h>
#include <OpenSG/OSGOrthographicCamera.h>
#include <OpenSG/OSGSolidBackground.h>

#include <iostream>
#include <string>
#include <sstream>

OSG_USING_NAMESPACE

// This is how its going to work. 

// Globals. 
SimpleSceneManager   *mgr;
NodeRefPtr            stageCamBeaconN;
TransformRefPtr       stageCamBeacon;

const UInt32 fboWidth     = static_cast<UInt32>(1024);
const UInt32 fboHeight    = static_cast<UInt32>(1024);

struct RenderPass
{
  // OpenSG
  NodeRefPtr              _stageN;
  SimpleStageRefPtr       _stage;
  // Output
  TextureObjChunkRefPtr   _fboTex;
  
  void cleanUp()
  {
    _stageN  = 0x00;
    _fboTex  = 0x00;
  }


  RenderPass() 
  {
    try
    {
      //SimpleStageRefPtr stage = SimpleStage::create();    
      _stage  = SimpleStage::create();
      _stageN = OSG::Node  ::create();

      _stageN->setCore(_stage);      

      _fboTex = TextureObjChunk  ::create();      
    }
    catch(std::bad_alloc& e)
    {     
      std::cerr << "Error" << e.what() << std::endl;
      cleanUp();  
    }  
  }


 ~RenderPass()
  {
    cleanUp();      
  } 
};

// Global. 
std::vector<RenderPass> renderPassVec;

void preRender(DrawEnv *drawEnv)
{
    std::cout << "preRender: " << drawEnv->getCameraViewing() << std::endl;
}

void postRender(DrawEnv *drawEnv)
{
    std::cout << "postRender: " << drawEnv->getCameraViewing() << std::endl;
}


void parseShader(const std::string& fullPath, std::string& program)
{
  std::ifstream stream(fullPath.c_str());

  if(stream.good())
  {
    const int bufferSize = 500;
    OSG::Char8* buffer = new OSG::Char8[bufferSize];
    
    do
    {
      stream.getline(buffer, bufferSize);
      program.append(buffer);
      program.append("\n");
    }
    while(!stream.eof());

    delete [] buffer;     
  }
  else
  {
    std::cerr << "Could not parse input file." << std::endl;
  }
}


// Construct render pass. 
void buildRenderPass( RenderPass* rPass, NodeRefPtr subTree, ChunkMaterialRefPtr mat)
{
  if(!rPass)
  {
    std::cerr << "NULL or void RenderPass pointer." << std::endl;
    return;
  }

  //  
  // 1. Create VisitSubTree 
  // 2. Create MaterialGroup
  // 3. Apply material to 2 and set the ref material. 
  // 4. Attach 1 to 2.

  NodeRefPtr          materialN = OSG::Node::create();
  MaterialGroupRefPtr material  = OSG::MaterialGroup::create();  
  materialN->setCore(material);

  material->setMaterial(mat);
  
  NodeRefPtr          vSubTreeN = OSG::Node::create();
  VisitSubTreeRefPtr  vSubTree  = OSG::VisitSubTree::create();    
  vSubTreeN->setCore(vSubTree);    

  // Add VisitSubTree node to MaterialGroup node. 
  materialN->addChild(vSubTreeN);
  commitChanges();

  //  
  rPass->_stageN->addChild(materialN);

  //rPass->_stage->addPreRenderFunctor (preRender,  "preRender" );
  //rPass->_stage->addPostRenderFunctor(postRender, "postRender");
  commitChanges();

  //stageCamBeacon;
  //stageCamBeaconN      = makeCoredNode<Transform>(&stageCamBeacon);  
  
  // move the camera back
  /*
  Pnt3f bbMin, bbMax;
  subTree->updateVolume();
  subTree->getVolume().getBounds(bbMin, bbMax);
  
  Real32 bbDia = (bbMax - bbMin).length();
  std::cout << "BB diameter. " << bbDia << std::endl;
  stageCamBeacon->editMatrix().setTranslate(Vec3f(0.0f, 0.0f, bbDia));
  
  materialN->addChild(stageCamBeaconN);
  commitChanges();
  */

  // Add scene to the VisitSubTree node. 
  vSubTree->setSubTreeRoot(subTree);

  // Now set the fbo. 
  ImageRefPtr             fboTexImg = Image            ::create();    
    
  FrameBufferObjectRefPtr fbo       = FrameBufferObject::create();
  TextureBufferRefPtr     texBuf    = TextureBuffer    ::create();
  RenderBufferRefPtr      depthBuf  = RenderBuffer     ::create();
  
  // set up the texture ...
  fboTexImg->set(Image::OSG_RGB_PF, fboWidth, fboHeight);
  rPass->_fboTex->setImage(fboTexImg);
  
  // ... and add it to the texture buffer
  texBuf->setTexture(rPass->_fboTex);
  
  // add a depth attachment, otherwise there is no depth buffer when
  // rendering to the FBO
  depthBuf->setInternalFormat(GL_DEPTH_COMPONENT24);
  
  // make the fbo render to the texture
  fbo->setColorAttachment(texBuf,   0);
  fbo->setDepthAttachment(depthBuf   );
  fbo->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
  fbo->setWidth (fboWidth );
  fbo->setHeight(fboHeight);
  fbo->setPostProcessOnDeactivate(true);
  
  // make the stage render to the FBO instead of the normal framebuffer
  rPass->_stage->setRenderTarget(fbo);
//  rPass->_stage->setInheritedTarget(true);
  
  // use the full size of the target (this is like setting up the viewport
  // of the stage)
  rPass->_stage->setSize(0.0f, 0.0f, 1.0f, 1.0f);
  
  // set a different background for things on the stage ...
  //GradientBackgroundRefPtr gb = GradientBackground::create();
  //gb->addLine(Color3f(0.0, 0.0, 0.0), 0.0);
  //gb->addLine(Color3f(0.5, 0.5, 0.5), 1.0);
  //rPass->_stage->setBackground(gb);
  
  // ... and add a camera
  //PerspectiveCameraRefPtr stageCam = PerspectiveCamera::create();
  //rPass->_stage->setCamera(stageCam);
  
  //stageCam->setBeacon(stageCamBeaconN);
  //stageCam->setNear  (   0.1);
  //stageCam->setFar   (10000.0);
  //stageCam->setAspect(1.0);
  //stageCam->setVerticalSize(1200);
  //stageCam->setFov   (   45.0);
  
  Camera *pCam = mgr->getCamera();

  if(pCam != NULL)
  {
    rPass->_stage->setCamera(mgr->getCamera());
  }
  else
  {
    std::cerr << "mgr->getCamera is NULL!" << std::endl;
  }

  SolidBackgroundRefPtr solidBkg = SolidBackground::create();
  solidBkg->setColor(Color3f(0.5, 0.5, 0.5));
  rPass->_stage->setBackground(solidBkg);

  commitChanges();
}


// Build final scene. 
NodeRefPtr buildFinalScene(NodeRefPtr subTree)
{
  MaterialGroupRefPtr matGroup  = MaterialGroup::create();
  NodeRefPtr          matGroupN = Node::create();
    
  matGroupN->setCore(matGroup);

  SimpleMaterialRefPtr  mat       = SimpleMaterial ::create();
  TextureEnvChunkRefPtr fboTexEnv = TextureEnvChunk::create();
  
  fboTexEnv->setEnvMode(GL_REPLACE);
  
  mat->addChunk(renderPassVec[1]._fboTex);
  mat->addChunk(fboTexEnv);        
  mat->setLit(false);

  matGroup->setMaterial(mat);
  
  matGroupN->addChild(subTree);

  commitChanges();

  return matGroupN;
}


// Build scene. 
NodeRefPtr buildScene(int argc, char **argv)
{ 
  // Entry. 
  std::cout << "buildScene called " << std::endl; 

  // Root node. 
  NodeRefPtr   rootN = OSG::Node::create();
  GroupRefPtr  root  = OSG::Group::create();
  rootN->setCore(root);

  // 2 render pass.
  const size_t noRenderPass = 2;

  // Load the data. 
  NodeRefPtr terrain = SceneFileHandler::the()->read("./pretty.obj");
  if(terrain)
  {
    std::cout << "Loaded terrain. " << std::endl;
  }  

  // Load the shaders and build the materials. 
  std::vector<ChunkMaterialRefPtr> materials;
  std::vector<SHLChunkRefPtr>      shaders;

  for(size_t i=0; i < noRenderPass; ++i)
  {
    std::cout << "Constructing render pass and materials." << std::endl;

    renderPassVec.push_back(RenderPass());
 
    materials.push_back(ChunkMaterial::create());
    shaders.push_back(SHLChunk::create());
      
    // Parse shader.
    std::string vp;
    std::string fp;    

    std::cout << "test. " << std::endl;

    std::string shaderFileName("./shader");
    std::ostringstream oss;
    oss << i;
    
    std::cout << "test. " << oss.str() << std::endl;

    std::cout << "full name of the shader file is: " 
              << shaderFileName + oss.str() + std::string(".vp") 
              << std::endl;       
              
    parseShader(shaderFileName + oss.str() + std::string(".vp"), vp);
    parseShader(shaderFileName + oss.str() + std::string(".fp"), fp);

    std::cout << "Vertex shader is. "   << vp << std::endl;
    std::cout << "Fragment shader is. " << fp << std::endl;

    shaders[i]->setVertexProgram   (vp);
    shaders[i]->setFragmentProgram (fp);      
    commitChanges();

    materials[i]->addChunk(shaders[i]);
    commitChanges();
  }


  if(terrain)
  {
    for(size_t i=0; i < noRenderPass; ++i)
    {
      buildRenderPass(&renderPassVec[i], terrain, materials[i]);   
      commitChanges(); 
      rootN->addChild(renderPassVec[i]._stageN);
      commitChanges();      
    }    
    
    rootN->addChild(buildFinalScene(terrain));
    commitChanges();
  }
  else
  {
    std::cerr << "Unable to load model file. " << std::endl;
    std::exit(0);
  }

  commitChanges();

  return rootN;    
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
    
    /*
    Matrix m;
    mgr->getCamera()->getViewing(m, 0, 0);

    std::cerr << "Camera viewing: " << m << std::endl;
    */

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

	case '1':
	{
		std::cerr << "Writing pass 0 texture. ";
		renderPassVec[0]._fboTex->getImage()->write("pass0.png");
		std::cerr << "done." << std::endl;
 	}
	break;

	case '2':
	{
		std::cerr << "Writing pass 1 texture. ";
		renderPassVec[1]._fboTex->getImage()->write("pass1.png");
		std::cerr << "done." << std::endl;
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

        // create the SimpleSceneManager helper
        mgr = new SimpleSceneManager;

	      // force call of SSM::initialize()
        mgr->setWindow(gwin );
	      mgr->setRoot(NULL);

        NodeRefPtr scene = buildScene(argc, argv);	      
        
        commitChanges();
    
        // tell the manager what to manage
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}
