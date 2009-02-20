// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGPointLight.h>

// New Headers

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#include <boost/bind.hpp>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// Scene objects. 
NodeRefPtr      sceneN;
GroupRefPtr     sceneC;

NodeRefPtr      transformN;
TransformRefPtr transformC;

TransformRefPtr lightTransformC;


// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// helper class to find a named node
// names are handled as simple attachments, get the header for that
#include <OpenSG/OSGNameAttachment.h>

#if 0

// There are two convenience functions for name access: getName() and
// setName(). For details about general attachment handling see the
// attachments tutorial

class NamedNodeFinder
{
  public:

    NamedNodeFinder(void) : _name(), _found() {}

    Node *operator() (Node *root, const std::string &name)
    {
        _name  = name;
        _found = NULL;

        TraverseEnterFunctor enter =
            boost::bind(&NamedNodeFinder::check, this, _1);
        traverse(root, enter);

        return _found;
    }

    static Node *find(Node *root, const std::string &name)
    {
        NamedNodeFinder f;

        return f(root, name);
    }

  private:

    Action::ResultE check(Node *node)
    {
        if(getName(node) && _name == getName(node))
        {
            _found = node;
            return Action::Quit;
        }

        return Action::Continue;
    }

    Node        *_found;
    std::string  _name;
};

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
    
        // load the scene
    
        NodeRefPtr scene;
    
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
    
            std::list<const char*> suffixes;
            SceneFileHandler::the()->getSuffixList(suffixes);
            //SceneFileHandler::the()->print();
    
            for(std::list<const char*>::iterator it  = suffixes.begin();
                                                it != suffixes.end();
                                            ++it)
            {
                FWARNING(("%s\n", *it));
            }
    
            scene = makeTorus(.5, 2, 16, 16);
        }
        else
        {
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
            scene = SceneFileHandler::the()->read(argv[1], NULL);
        }
    
    
        NodeRefPtr found;
    
        NamedNodeFinder f;
    
        // Try to find the Scene object. As it hasn't been named yet,
        // it's not expected to be found.
        found = f(scene, "Scene");
        
        if(found == NULL)
        {
            SLOG << "Found no object named 'Scene'.\n";
        }
        else
        {
            SLOG << "Found object " << found 
                 << " named 'Scene'. How did that happen?\n";
        }
    
        // Try to find the TF_DETAIL object. An object in Data/tie.wrl is called
        // TF_DETAIL, so we might find it.
        found = NamedNodeFinder::find(scene, "TF_DETAIL");
        
        if(found == NULL)
        {
            SLOG << "Found no object named 'TF_DETAIL' (did you load the tie?)."
                << endLog;
        }
        else
        {
            SLOG << "Found object " << found << " named 'TF_DETAIL'." << endLog;
        }
    
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

#endif 

void idle()
{
  static int t = 0;
 
  if( t < 360 )
  {
    ++t;
  }
  else
  {
    t = 0;
  }    

  Real32 time = glutGet(GLUT_ELAPSED_TIME );

  Matrix m; 

  //m.setRotate( Quaternion( Vec3f( 0.0, 1.0, 0.0 ), 
  //            ( 30 + t / 180.0 ) * ( 22.0 / 7.0 ) ) );  

  m.setRotate( Quaternion( Vec3f( 1.0, 1.0, 0.0 ), 
               time / 1000.f ) );

  lightTransformC->setMatrix( m );

  glutPostRedisplay();
}


// redraw the window
void display(void)
{
    mgr->idle();
    mgr->redraw();
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


// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            delete mgr;
            
            OSG::osgExit();
            exit(0);
        }
        break;

        case 'f':
        {
            mgr->setNavigationMode(Navigator::FLY);
        }
        break;

        case 't':
        {
            mgr->setNavigationMode(Navigator::TRACKBALL);
        }
        break;

    case 's':
       {
          mgr->setStatistics(!mgr->getStatistics());
       }
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
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

#define __LEARN_OSG_MATH__  1
#define __LEARN_OSG_SCENE__ 1

#ifdef __LEARN_OSG_MATH__

int main( int argc, char** argv )
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Working with OSG vectors. 
  //
  /////////////////////////////////////////////////////////////////////////////

  Vec3f v   = Vec3f(1,2,3);
  Vec3f w(0.5, 0.5, 0.5); 

  Real32 l  = v.length();
  float  f  = v.length();
  
  v.normalize();
  
  std::cout << "@learning osg math: Vector length is: " << v.length() << std::endl;

  Vec3f   e   = v.cross(w);
  Real32  e1    = v.dot(w);

  Real32 c1 = v[0];
  Real32 c2 = v[1];
  Real32 c3 = v[2];

  Vec3f final  = e + v;

  /////////////////////////////////////////////////////////////////////////////
  //
  // Working with OSG points. 
  //
  /////////////////////////////////////////////////////////////////////////////

  Pnt3f pnt1 (1.0,0.0,0.0);
  Vec3f vecPnt1 = pnt1.subZero();
  Pnt3f pntVec1 = vecPnt1.addToZero();

  if( pntVec1 == pnt1 )
  {
    std::cout << "Converstaion preserves the data: " << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Working with OSG matrices. 
  //
  /////////////////////////////////////////////////////////////////////////////
    
  
  // Row major entry. Special case here. 
  Matrix m( 1,0,0,2, 0,1,0,3, 0,0,1,4, 0,0,0,1 );

  Vec3f result;
  m.mult(result,result);

  std::cout << "Matrix multiplication with a vector: " << result << std::endl;

  m.setIdentity();
  m.setScale(2,2,1);
  m.setTranslate(2,2,3);

  std::cout << "Row major matrix output of Matrix m is: " << m << std::endl;

  // Initialize opensg. 
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
  
    // load the scene   
    if(argc < 2)
    { 
      std::list<const char*> suffixes;
      SceneFileHandler::the()->getSuffixList(suffixes);
      
      for(std::list<const char*>::iterator it  = suffixes.begin();
                                          it != suffixes.end();
                                      ++it)
      {
          FWARNING(("%s\n", *it));
      }
    }
    
    // Initialize scene graph here. 
    sceneN      = Node::create();
    sceneC      = Group::create();

    transformN  = Node::create();
    transformC  = Transform::create();

    NodeRefPtr lightTransformN = Node::create();
    // This core will be used to rotate the lights. 
    lightTransformC = Transform::create();
    lightTransformN->setCore( lightTransformC );

    NodeRefPtr            matN = Node::create();
    MaterialGroupRefPtr   matC = MaterialGroup::create();

    // Add lighting. 
    NodeRefPtr       pointLightN = Node::create();
    PointLightRefPtr pointLightC = PointLight::create();

    pointLightC->setDiffuse  ( Color4f( 1, 0, 1, 1 ) );
    pointLightC->setAmbient  ( Color4f( 0.2, 0.2, 0.2, 1 ) );
    pointLightC->setSpecular ( Color4f( 1, 1, 1, 1 ) );
    pointLightC->setPosition ( Vec3f( 0.0, 10.0, 0.0 ) );
    pointLightC->setBeacon   ( lightTransformN );

    pointLightN->setCore( pointLightC );

    // Now apply some textures. 
    ImageRefPtr img = Image::create();
    if( img )
    {
      /*img->read( "sample.jpg"  );
      SimpleTexturedMaterialRefPtr mat = SimpleTexturedMaterial::create();
      mat->setImage( img );
      commitChanges();    
      matC->setMaterial( mat );
      commitChanges();  */
    }

    matN->setCore( matC );
    commitChanges();

    sceneN->setCore( sceneC.get() );
    commitChanges();

    Matrix m; 
    m.setIdentity();
    transformC->setMatrix( m );

    transformN->setCore(transformC.get());
    commitChanges();

    NodeRefPtr model = makeBox( 1,1,1, 10, 10, 10 );

    matN->addChild( model );
    pointLightN->addChild( matN );
    commitChanges();    

    transformN->addChild( pointLightN  );
    commitChanges();

    sceneN->addChild( transformN );        
    sceneN->addChild( lightTransformN );
    commitChanges();

#ifdef __LEARN_OSG_SCENE__
    setName( transformN, "SceneTransform" );
    setName( sceneN, "SceneRoot" );
    setName( model, "SceneModel" );

    std::cout << "SceneRoot has " << sceneN->getNChildren() 
              << " children. " 
              << std::endl;    

    //NodeRefPtr root = model->getParent()->getParent();
    //if( root )
    //{
    //  std::cout << "Found root and has name: " << getName( root.get() ) << std::endl;
    //}

    //// @todo: find a better way to do this. 
    //std::cout << "Transform core has parent: " 
    //  << getName( ( dynamic_cast<OSG::AttachmentContainer*>( ( transformC->getParents() )[0] ) ) )
    //  << std::endl;
    
#endif
    commitChanges();
  
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (sceneN);
  
    // show the whole scene
    mgr->showAll();
    
  }

  // GLUT main loop
  glutMainLoop();

  return 0;  
}

#endif // __LEARN_OSG_MATH__

