
#ifndef _VJ_OPENSG2_APP_H_
#define _VJ_OPENSG2_APP_H_

#include <vrj/vrjConfig.h>
#include <sstream>

#include <vpr/Util/Debug.h>
#include <vrj/Draw/OGL/GlContextData.h>

/*-----------------------------OpenSG includes--------------------------------*/
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGPassiveViewport.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGMatrixUtility.h>

#include <OpenSG/OSGRenderAction.h>

/*----------------------------------------------------------------------------*/

#include <vrj/Draw/OGL/GlApp.h>

namespace vrj
{

/** \class OpenSG2App OpenSG2App.h vrj/Draw/OpenSG/OpenSG2App.h
 *
 * Base type for OpenSG application objects.
 */
  class OpenSG2App : public vrj::GlApp
  {
    public:
      struct context_data
      {
        context_data()
        : mRenderAction            (NULL )
        , mWin                     (NULL )
        , mViewport                (NULL )
        , mBackground              (NULL )
        , mCamera                  (NULL )
        , mContextThreadInitialized(false)
        , mOsgThread               (NULL )
        {
          ;
        }

        ~context_data()
        {          
        }
  
        OSG::RenderAction*            mRenderAction;    /**< The render action for the scene */
        OSG::PassiveWindowRefPtr      mWin;             /**< passive window to render with (the context) */
        OSG::PassiveViewportRefPtr    mViewport;        /**< passive viewport to render with (the context) */
        OSG::PassiveBackgroundRefPtr  mBackground;      /**< passive background to render with (the context) */
        OSG::MatrixCameraRefPtr       mCamera;        
      
        bool                          mContextThreadInitialized;
        OSG::ExternalThread*          mOsgThread;
      };
  
    public:
      
      OpenSG2App(vrj::Kernel* kern=NULL)
      : GlApp(kern)
      {
        ;
      }
  
      virtual ~OpenSG2App()
      {        
      }
  
      /**
       * Scene initialization function.
       * User code for initializing the OpenSG scene should be placed here.
       */
      virtual void initScene() = 0;
  
      /**
       * Get the OpenSG Scene root.
       * @return NodePtr to the root of the scene to render.
       */
      virtual OSG::Node *getScene() = 0;
  
      /**
       * Initializes OpenSG for drawing.
       * If overridden, the overriding method MUST call this method.
       */
      virtual void init();
  
      /**
       * Initializes OpenSG.
       * Make sure to call initScene if you override this function.
       * If a derived class overrides this method, the overriding function MUST
       * call OpenSG2App::apiInit().
       */
      virtual void apiInit();
  
      /**
       * Shuts down OpenSG.  If overridden, the overriding method must call this
       * method.
       */
      virtual void exit();
  
      /**
       * For OpenSG 1.x, this method does nothing. For OpenSG 2, it ensures that
       * all scene graph changes have been committed prior to rendering. If
       * overridden, the overriding method must call this method. It is
       * recommended that the invocation of this method be the last step in the
       * override of latePreFrame().
       *
       * @since 2.1.28
       */
      virtual void latePreFrame()
      {
        OSG::commitChanges();
      }
  
      /**
       * OpenGL Drawing functions.
       * If user code overrides these functions, the overriding functions MUST
       * call these methods.
       */
      //@{
      virtual void contextInit();
      virtual void contextPreDraw();
      virtual void contextPostDraw();
      virtual void draw();
      //@}
  
      /**
       * Called once per frame, per buffer (basically context).
       * This is needed so that we can use subviewports.
       */
      virtual void bufferPreDraw()
      {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
      }
  
    protected:

      /**
       * Optional. Used if the application class manipulating 
       * projection and modelview matrices using some of its own 
       * parameters and using existing modelview and projection matrices. 
       *
       */
      virtual void setupCamera(){;}

    protected:
      
      vrj::GlContextData<context_data>  mContextData;  /**< OpenSG context data */
  
      OSG::UInt32 OSG_MAIN_ASPECT_ID;
  };

// Handle any initialization needed before API
  inline void OpenSG2App::init()
  {
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_VERB_LVL,
                         "vrj::OpenSG2App::init() entered.\n",
                         "vrj::OpenSG2App::init() exited.\n");

    GlApp::init();

    // XXX: Complete initialization
    // if(!osgInitAlreadyCalled())
    OSG::osgInit(0,0);                  // Binds to primordial thread

    OSG_MAIN_ASPECT_ID = OSG::Thread::getCurrentAspect();   // Gets the base aspect id to use
  }


  inline void OpenSG2App::apiInit()
  {
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_VERB_LVL,
                         "vrj::OpenSG2App::apiInit() entered.\n",
                         "vrj::OpenSG2App::apiInit() exited.\n");

    this->initScene();
    vprASSERT(getScene() != NULL);
  }


  inline void OpenSG2App::exit()
  {
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_VERB_LVL,
                         "vrj::OpenSG2App::exit() entered.\n",
                         "vrj::OpenSG2App::exit() exited.\n");

    OSG::osgExit();
  }


/** Called once per context at context creation */
  inline void OpenSG2App::contextInit()
  {
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_VERB_LVL,
                         "vrj::OpenSG2App::contextInit() entered.\n",
                         "vrj::OpenSG2App::contextInit() exited.\n");

    context_data* c_data = &(*mContextData);  // Context specific data. Should be one copy per context

    // Check for thread initialized
    // This will only happen for the first initialized context per pipe
    if(!c_data->mContextThreadInitialized)
    {
      c_data->mContextThreadInitialized = true;

      std::ostringstream thread_name;
      thread_name << "vprThread:" << vpr::Thread::self()->getTID();
      c_data->mOsgThread = OSG::ExternalThread::get(thread_name.str().c_str());

      if(!(c_data->mOsgThread->isInitialized()))
      {
        c_data->mOsgThread->initialize(OSG_MAIN_ASPECT_ID);     // XXX: In future this might need to be different thread
      }
    }

    // Allocate OpenSG stuff
    c_data->mWin        = OSG::PassiveWindow::create();
    c_data->mViewport   = OSG::PassiveViewport::create();
    c_data->mBackground = OSG::PassiveBackground::create();
    c_data->mCamera     = OSG::MatrixCamera::create();    

    // Set up the viewport.
    c_data->mViewport->setLeft  (0);
    c_data->mViewport->setRight (1);
    c_data->mViewport->setBottom(0);
    c_data->mViewport->setTop   (1);

    c_data->mViewport->setCamera    (c_data->mCamera);
    c_data->mViewport->setBackground(c_data->mBackground);

    // Set up the Window.
    c_data->mWin->addPort(c_data->mViewport);

    // Set up the camera.
    c_data->mCamera->setNear(0.1  );
    c_data->mCamera->setFar (10000);

    // Could actually make one of these per thread instead of context.
    c_data->mRenderAction = OSG::RenderAction::create();

    // Initialize OpenSG's OpenGL state
    c_data->mWin->init();

    OSG::commitChanges();
  }

  inline void OpenSG2App::contextPreDraw()
  {
    context_data* c_data = &(*mContextData);
    c_data->mWin->frameInit();
  }

  inline void OpenSG2App::contextPostDraw()
  {
    context_data* c_data = &(*mContextData);
    c_data->mWin->frameExit();
  }

  inline void OpenSG2App::draw()
  {
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_HVERB_LVL,
                         "vrj::OpenSG2App::draw() entered.\n",
                         "vrj::OpenSG2App::draw() exited.\n");

    glClear(GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    context_data* c_data = &(*mContextData);

    vrj::GlDrawManager* drawMan =
    dynamic_cast<vrj::GlDrawManager*>(this->getDrawManager());
    vprASSERT(drawMan != NULL);
    vrj::GlUserData* userData = drawMan->currentUserData();

    // Copy the matrix
    vrj::Projection* project     = userData->getProjection();
    const vrj::Frustum   & vrj_frustum = userData->getProjection()->getFrustum();

    const float* vj_proj_view_mat = project->getViewMatrix().mData;
    OSG::Matrix frustum_matrix, view_xform_mat;
    view_xform_mat.setValue(vj_proj_view_mat);

    OSG::MatrixFrustum(frustum_matrix,
                       vrj_frustum[vrj::Frustum::VJ_LEFT],
                       vrj_frustum[vrj::Frustum::VJ_RIGHT],
                       vrj_frustum[vrj::Frustum::VJ_BOTTOM],
                       vrj_frustum[vrj::Frustum::VJ_TOP],
                       vrj_frustum[vrj::Frustum::VJ_NEAR],
                       vrj_frustum[vrj::Frustum::VJ_FAR]);

    // Set up the camera.
    c_data->mCamera->setNear(vrj_frustum[vrj::Frustum::VJ_NEAR]);
    c_data->mCamera->setFar (vrj_frustum[vrj::Frustum::VJ_FAR] );
    c_data->mCamera->setProjectionMatrix(frustum_matrix);  // Set projection matrix
    c_data->mCamera->setModelviewMatrix (view_xform_mat);  // Set modelview matrix         
    
    /*std::cout << "Juggler Projection values: " << std::endl;
    std::cout << vrj_frustum[vrj::Frustum::VJ_LEFT]   << std::endl;
    std::cout << vrj_frustum[vrj::Frustum::VJ_RIGHT]  << std::endl;
    std::cout << vrj_frustum[vrj::Frustum::VJ_BOTTOM] << std::endl;
    std::cout << vrj_frustum[vrj::Frustum::VJ_TOP]    << std::endl;*/  
   
    
    // Make sure to call this so that application can do its own setup. 
    this->setupCamera();
  
    // Set up the viewport.
    c_data->mViewport->setRoot(getScene());

    // --- Trigger the draw --- //

    // Push the matrix so that drawing after this is not affected by the scene
    // graph.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    c_data->mWin->render(c_data->mRenderAction);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopAttrib();    // Pop the attribute store
  }

} // End of vrj namespace

#endif
