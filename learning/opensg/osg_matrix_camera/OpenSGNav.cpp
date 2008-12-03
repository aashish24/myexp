
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <vrj/vrjConfig.h>

#include <math.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/Coord.h>
#include <gmtl/Xforms.h>

#include <vrj/Display/Projection.h>
#include <vrj/Display/CameraProjection.h>

#include "OpenSGNav.h"

// Handle any initialization needed before API
void OpenSGNav::init()
{
   vrj::OpenSG2App::init();      // Call base class init
}

/** Called once per context at context creation */
void OpenSGNav::contextInit()
{ 
  vrj::OpenSG2App::contextInit();

  mAppContextData->mLimeCamera = new LimeVrjCamera(mView, mSetup);
  mAppContextData->mLimeCamera->setOSGCamera(mContextData->mCamera);
  mAppContextData->mLimeCamera->setSceneCamera(dynamic_cast<SceneCamera*>(mNavigator));
  
  initGLState();
  mQuadObj = gluNewQuadric();
  gluQuadricDrawStyle( mQuadObj, GLU_FILL );
}

void OpenSGNav::draw()
{
  // Call parent class first to render the scene graph
  vrj::OpenSG2App::draw();

  // 
  mAppContextData->mLimeCamera->setView(mView);
  mAppContextData->mLimeCamera->setSetup(mSetup);  

  // Now draw OpenGL stuff. 
  glPushAttrib(GL_ALL_ATTRIB_BITS);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
    glDisable(GL_LIGHTING);    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    glLoadMatrixd(mAppContextData->mLimeCamera->getViewSetupMatrix().mData);
    draw_field_grid();   
  
    draw_cutin();

    glMultMatrixd(mAppContextData->mLimeCamera->get3dSetupMatrix().mData);
    draw_setup_guide();    
    
    glMultMatrixd(mAppContextData->mLimeCamera->getViewMatrix().mData);  

    glPushMatrix();
      glColor4f( 1.0, 0.0, 0.0, 1.0 );
      glPushMatrix();
      glScalef( 0.8, 0.8, 0.8 );
      gluSphere( mQuadObj, 1.0, 32, 16 );
      glPopMatrix();
  
      glPushMatrix();
      glTranslatef( 0.0, 0.0, -5.0 );
      glScalef( 0.8, 0.8, 0.8 );
      gluSphere( mQuadObj, 1.0, 32, 16 );
      glPopMatrix();
  
      glPushMatrix();
      glTranslatef( 0.0, 0.0, -10.0 );
      glScalef( 0.8, 0.8, 0.8 );
      gluSphere( mQuadObj, 1.0, 32, 16 );
      glPopMatrix();
  
      glColor4f( 0.0, 0.0, 1.0, 1.0 );
      glPushMatrix();
      glTranslatef( -2.0, 0.0, 0.0 );
      glScalef( 1.8, 1.8, 1.8 );
      gluSphere( mQuadObj, 1.0, 32, 16 );
      glPopMatrix();
  
      glColor4f( 1.0, 1.0, 0.0, 1.0 );
      glPushMatrix();
      glTranslatef( 0.0, 2.0, 0.0 );
      glScalef( 1.3, 1.3, 1.3 );
      gluSphere( mQuadObj, 1.0, 32, 16 );
      glPopMatrix();
    glPopMatrix();
  glPopAttrib(); 

  if(mGrabScreenShot)
  {
    static const int buff_size=100000;
    char filename[buff_size];
    snprintf(filename, buff_size, "view-%.2f-%.2f-%.2f-%.2f-%.2f-%.2f-setup-%.2f-%.2f-%.2f-%.2f-%.2f-%.2f-%.2f", 
    mView.getAspect(), mView.getNS(), mView.getEW(), mView.getField(), mView.getCrot(), mView.getPegOffset(), 
    mSetup.getImageWidth(), mSetup.getNS(),mSetup.getEW(), mSetup.getField(), mSetup.getLens(), mSetup.getNear(),mSetup.getFar());
    
    tgaGrabScreenSeries(filename, 0,0, 1600, 1050);
    
    mGrabScreenShot = false;
  }
}

void OpenSGNav::preFrame()
{ 
  mNavigator->updateTimeSec(mHead->getTimeStamp().secd());  
  
  {
    float data = (mAnalog01->getData() - 0.5) * 2.0;    
    if(fabs(data) > 0.01)
    {        
      mNavigator->translate(gmtl::Vec3d(data, 0.0, 0.0));
    }   
  }
      
  {
    float data = (mAnalog02->getData() - 0.5 ) * 2.0;    
    if(fabs(data) > 0.01)
    {
      // Translation when we pushforward should move us in the -ve dir.        
      // (in case of joystick as top most val is 1 and bottom most is 0.
      //std::cout << "data from analog 2 is: " << mAnalog02->getData() << std::endl; 
      mNavigator->translate(gmtl::Vec3d(0.0, 0.0, data));
    }
  }

  {
    float data = (mAnalog03->getData() - 0.5 ) * 2.0;    
    if(fabs(data) > 0.01)
    {
      // Rotation is clockwise hence angle should be -ve 
      // (in case of joystick as left most val is 0 and right most is 1). 
      mNavigator->yaw(-data);
    }   
  }  

  {
    float data = (mAnalog04->getData() - 0.5 ) * 2.0;    
    if(fabs(data) > 0.01)
    {
      mNavigator->pitch(data);
    }   
  }

  {
    if(mButton01->getData() == gadget::Digital::TOGGLE_ON)
    {
      mGrabScreenShot = true;
    }
  }  

  {
    if(mButton02->getData() == gadget::Digital::TOGGLE_ON)
    {
      mView.setField(mView.getField()+1);
    }  

    if(mButton03->getData() == gadget::Digital::TOGGLE_ON)
    {
      mView.setField(mView.getField() - 1);
    }    
  }  

  {
    if(mButton04->getData() == gadget::Digital::TOGGLE_ON)
    {
      mSetup.setLens(mSetup.getLens() + 5);
    }  

    if(mButton05->getData() == gadget::Digital::TOGGLE_ON)
    {
      mSetup.setLens(mSetup.getLens() - 5);
    }    
  }

  vrj::OpenSG2App::preFrame();
}


void OpenSGNav::exit()
{
   // Ensure that we release all the OSG::RefPtr<T> objects that we hold so
   // that OpenSG can shut down cleanly.
   mSceneRoot      = 0x00;
   mSceneTransform = 0x00;
   mModelRoot      = 0x00;
   mLightNode      = 0x00;
   mLightBeacon    = 0x00;

   vrj::OpenSG2App::exit();
}


/** Initialize GL state. Hold over from regular OGL apps */
void OpenSGNav::initGLState()
{
   // OpenSG does not handle this yet, being smart about it is not
   // that trivial...
   glEnable( GL_DEPTH_TEST );
   glEnable(GL_NORMALIZE);
   glShadeModel(GL_SMOOTH);
}


void OpenSGNav::initScene()
{
   vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_CRITICAL_LVL,
                        "OpenSGNav::initScene() called.\n",
                        "OpenSGNav::initScene() exiting.\n");

   // --- Initialize vrj devices --- //
    mButton01.init("VJButton01");
    mButton02.init("VJButton02");
    mButton03.init("VJButton03");
    mButton04.init("VJButton04");
    mButton05.init("VJButton05");
    mButton06.init("VJButton06");
    mButton07.init("VJButton07");
    mButton08.init("VJButton08");
    mButton09.init("VJButton09");

    mAnalog01.init("VJAnalog01");
    mAnalog02.init("VJAnalog02");
    mAnalog03.init("VJAnalog03");
    mAnalog04.init("VJAnalog04");
    mAnalog05.init("VJAnalog05");
    mAnalog06.init("VJAnalog06");   

    mHead.init("VJHead");        

   // Load the model to use
   if (mFileToLoad ==  std::string("none"))
   {
      vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
         << "[OpenSGNav::initScene()] No model specified; creating torus."
         << std::endl << vprDEBUG_FLUSH;
      //mModelRoot = OSG::makeTorus(.5, 2, 16, 16);
   }
   else
   {
      vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
         << "[OpenSGNav::initScene()] Loading '" << mFileToLoad << "' ..."
         << std::endl << vprDEBUG_FLUSH;
      const OSG::Char8* file = mFileToLoad.c_str();
#if OSG_MAJOR_VERSION < 2
      mModelRoot = OSG::SceneFileHandler::the().read(file);
#else
      mModelRoot = OSG::SceneFileHandler::the()->read(file);
#endif
   }
   
   // --- Light setup --- //
   // - Add directional light for scene
   // - Create a beacon for it and connect to that beacon
   mLightNode   = OSG::Node::create();
   mLightBeacon = OSG::Node::create();
   OSG::PointLightRefPtr light_core = OSG::PointLight::create();
   OSG::TransformRefPtr light_beacon_core = OSG::Transform::create();

   // Setup light beacon
   OSG::Matrix light_pos;
   light_pos.setTransform(OSG::Vec3f(0.0f, 1000.0f, 10000.0f));

   light_beacon_core->setMatrix(light_pos);

   mLightBeacon->setCore(light_beacon_core);

   // Setup light node
   mLightNode->setCore(light_core);
   mLightNode->addChild(mLightBeacon);

   light_core->setAmbient  (0.9, 0.8, 0.8, 1);
   light_core->setDiffuse  (0.8, 0.8, 0.8, 1);
   light_core->setSpecular (0, 0, 1, 1);
   //light_core->setDirection(0, 0, -1);
   light_core->setBeacon   (mLightBeacon);

   // --- Setup Scene -- //
   // add the loaded scene to the light node, so that it is lit by the light
   //mLightNode->addChild(mModelRoot);

   // create the root part of the scene
   mSceneRoot = OSG::Node::create();
   mSceneTransform = OSG::Transform::create();

   // Set up the root node
   mSceneRoot->setCore(mSceneTransform);
   mSceneRoot->addChild(mLightNode);
}


void OpenSGNav::setupCamera()
{
  mAppContextData->mLimeCamera->evaluate();
}


void OpenSGNav::draw_field_grid( void ) {
    float minx = -(mSetup.getField()/2.0);
    float maxx =  (mSetup.getField()/2.0);
    float miny = minx/mView.getAspect();
    float maxy = maxx/mView.getAspect();
    float x, y;

    glBegin( GL_LINES );
    for (x=0.0; x<=maxx; x+=1.0) 
    {
      if ( x == 0.0 ) glColor4f( 0.0, 1.0, 0.0, 1.0 );
      else glColor4f( 0.0, 0.6, 0.0, 0.8 );
      glVertex2d( x, miny );  glVertex2d( x, maxy );
    }
    for (x=-1.0; x>=minx; x-=1.0) 
    {
      if ( x == 0.0 ) glColor4f( 0.0, 1.0, 0.0, 1.0 );
      else glColor4f( 0.0, 0.6, 0.0, 0.8 );
      glVertex2d( x, miny );  glVertex2d( x, maxy );
    }
    for (y=0.0; y<=maxy; y+=1.0) 
    {
      if ( y == 0.0 ) glColor4f( 0.0, 1.0, 0.0, 1.0 );
      else glColor4f( 0.0, 0.6, 0.0, 0.8 );
      glVertex2d( minx, y );  glVertex2d( maxx, y );
    }
    for (y=-1.0; y>=miny; y-=1.0) 
    {
      if ( y == 0.0 ) glColor4f( 0.0, 1.0, 0.0, 1.0 );
      else glColor4f( 0.0, 0.6, 0.0, 0.8 );
      glVertex2d( minx, y );  glVertex2d( maxx, y );
    }
    glEnd();
}


void OpenSGNav::draw_setup_guide( void ) {
    float rx = mSetup.getField() / 2.0;
    float ry = rx / mView.getAspect();

    { /* ---- locate vanishing point ---- */
  float z1 = 0.0, z2 = -10000.0;

  glBegin( GL_LINES );
  glColor4f( 1.0, 1.0, 0.0, 0.2 );
  glVertex3d( -rx, -ry,  z1 );    
  glColor4f( 1.0, 1.0, 0.0, 1.0 );
  glVertex3d( 0, 0, z2 );

  glColor4f( 1.0, 1.0, 0.0, 0.2 );
  glVertex3d(  rx, -ry,  z1 );    
  glColor4f( 1.0, 1.0, 0.0, 1.0 );
  glVertex3d( 0, 0, z2 );

  glColor4f( 1.0, 1.0, 0.0, 0.2 );
  glVertex3d(  rx,  ry,  z1 );    
  glColor4f( 1.0, 1.0, 0.0, 1.0 );
  glVertex3d( 0, 0, z2 );

  glColor4f( 1.0, 1.0, 0.0, 0.2 );
  glVertex3d( -rx,  ry,  z1 );    
  glColor4f( 1.0, 1.0, 0.0, 1.0 );
  glVertex3d( 0, 0, z2 );
  glEnd();    
    }

    { /* ---- setup rectangles ---- */
  float z[3] = { -10.0, -100.0, -1000.0 };
  float a[3] = {   1.0,    0.7,     0.4 };
        int i;

  for ( i=0; i<3; i++ ) {
      glColor4f( 1.0, 1.0, 0.0, a[i] );
      glBegin( GL_LINE_LOOP );
      glVertex3d( -rx, -ry,  z[i] );
      glVertex3d(  rx, -ry,  z[i] );
      glVertex3d(  rx,  ry,  z[i] );
      glVertex3d( -rx,  ry,  z[i] );
      glEnd();
  }
    }
}


void OpenSGNav::draw_cutin( void ) 
{
    float minx  = -( mView.getField()/2.0 * 0.9 );    /* video (est) */
    float maxx  =  ( mView.getField()/2.0 * 0.9 );
    float miny  = minx / 1.33;
    float maxy  = maxx / 1.33;
    float cminx = -(mView.getField()/2.0);
    float cmaxx =  (mView.getField()/2.0);
    float cminy = cminx / mView.getAspect();
    float cmaxy = cmaxx / mView.getAspect();

    glPushMatrix();
    glTranslatef( ((mView.getEW() - mView.getPegOffset()) / 100.0), 
      ((mView.getNS() - 5000.0) / 100.0), 0.0);
    glRotatef( -mView.getCrot(), 0.0, 0.0, 1.0 );
    glBegin( GL_LINE_LOOP );
    glColor4f( 0.6, 0.2, 0.0, 0.6 );
    glVertex2d( minx, miny );  glVertex2d( maxx, miny );
    glVertex2d( maxx, maxy );  glVertex2d( minx, maxy );
    glEnd();

    if ( mAppContextData->mLimeCamera->layoutMode() ) 
    {
      glBegin( GL_LINE_LOOP );
      glColor4f( 0.8, 0.3, 0.0, 1.0 );
      glVertex2d( cminx, cminy );  glVertex2d( cmaxx, cminy );
      glVertex2d( cmaxx, cmaxy );  glVertex2d( cminx, cmaxy );
      glEnd();
    }

    glPopMatrix();
}
