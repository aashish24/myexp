//what follows here is the smallest OpenSG programm possible
//most things used here are explained now or on the next few pages, so don’t
//worry if not everything is clear right at the beginning...
//Some needed include files - these will become more, believe me ;)

#include <deque>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>
#include <gmtl/Generate.h>

#include <gmtl/Output.h>

#include "Skeleton.hpp"
#include "AsfParser.hpp"

//In most cases it is useful to add this line, otherwise every OpenSG command
//must be preceeded by an extra OSG::

OSG_USING_NAMESPACE

//The SimpleSceneManager is a useful class which helps us to
//manage simple configurations. It will be discussed in detail later on

SimpleSceneManager *mgr;

//we have a forward declaration here, just to have a better order
//of codepieces
int setupGLUT( int *argc, char *argv[] );
NodeRecPtr root;

NodeTransitPtr createSceneGraph(void) {
   Skeleton *s = AsfParser::GetInstance()->Parse("02.asf");

   NodeRecPtr root = Node::create();

   root->setCore(Group::create());

   std::deque<int> q;

   q.push_back(0);
   std::cout << "createSceneGraph" << std::endl;
   while(!q.empty()) {
      int id = q.front();
      q.pop_front();
      std::vector<int> children = s->GetChildren(id);
      BoneInfo *bi = s->GetBoneInfo(id);
      for(size_t i = 0; i < children.size(); ++i) {
         q.push_back(children[i]);
      }
      TransformRecPtr t = Transform::create();
      Matrix m;
      gmtl::Matrix44f gm = bi->GetMatrix();
      gmtl::Vec3f yaxis, dir;
      yaxis.set(0.0, -1.0, 0.0);
      dir = bi->GetDirection();
      gmtl::normalize(dir);
      gmtl::Matrix44f rotMat;
      gmtl::setRot(rotMat, yaxis, dir);

      std::cout << "id: " << id << " matrix: " << std::endl << gm << std::endl;
      m.setValue(gm.getData());
      Matrix temp;
      temp.setValue(rotMat.getData());
      m.mult(temp);
      t->setMatrix(m);
      NodeRecPtr node = Node::create();
      node->setCore(t);
//      node->addChild(makeTorus(0.5, 2, 16, 16));
//      node->addChild(makeSphere(2, 1.0));
      node->addChild(makeCylinder(bi->GetLength(), 0.1, 16, true, true, true));
      root->addChild(node);
   }

//   NodeRecPtr torus = makeTorus(0.5, 2, 16, 16);
   return NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
   // Init the OpenSG subsystem
   osgInit(argc,argv);

   // We create a GLUT Window (that is almost the same for most applications)
   int winid = setupGLUT(&argc, argv);
   GLUTWindowRecPtr gwin= GLUTWindow::create();
   gwin->setGlutId(winid);
   gwin->init();

   // This will be our whole scene for now : an incredible torus
   root = createSceneGraph();

   // Create and setup our little friend - the SSM
   mgr = new SimpleSceneManager;
   mgr->setWindow(gwin);
   mgr->setRoot(root);
   mgr->showAll();
   // Give Control to the GLUT Main Loop
   glutMainLoop();
   return 0;
}

// react to size changes
void reshape(int w, int h)
{
   mgr->resize(w, h);
   glutPostRedisplay();
}

// just redraw our scene if this GLUT callback is invoked
void display(void)
{
   mgr->redraw();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
   mgr->mouseMove(x, y);
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

//The GLUT subsystem is set up here. This is very similar to other GLUT
//applications. If you have worked with GLUT before, you may have the
//feeling of meeting old friends again, if you have not used GLUT before
//that is no problem. GLUT will be introduced briefly on the next section
int setupGLUT(int *argc, char *argv[])
{
   glutInit(argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   int winid = glutCreateWindow("OpenSG/Mocap Application");
   // register the GLUT callback functions
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMotionFunc(motion);
   glutMouseFunc(mouse);
   glutIdleFunc(display);
   return winid;
}
