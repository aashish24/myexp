
#ifndef __LIME_CAMERA_BASE_H__
#define __LIME_CAMERA_BASE_H__

// Lime includes. 
#include "ILimeCamera.h"
#include "ISceneCamera.h"
#include "Setup.h"
#include "View.h"
#include "UnitConversions.h"

// OpenSG includes. 
#include "OpenSG/OSGMatrixCamera.h"

// GMTL includes. 
#include "gmtl/Matrix.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Generate.h"
#include "gmtl/Vec.h"
#include "gmtl/AxisAngle.h"

// STD library includes. 
#include <cmath>

class LimeVrjCamera  : public ILimeCamera
{
  public:   
                              LimeVrjCamera(const View& view=View(), const Setup& setup=Setup());
    virtual                  ~LimeVrjCamera();    

    virtual const View&       getView()  const { return _view; }
    virtual void              setView(const View& view){ _view = view; }

    virtual const Setup&      getSetup() const { return _setup; }
    virtual void              setSetup(const Setup& setup){ _setup = setup; }

    ISceneCamera*             getSceneCamera();
    virtual void              setSceneCamera(ISceneCamera* sCamera);

    virtual void              setOSGCamera(OSG::MatrixCameraRefPtr osgCamera);

    // \note Move these functions into RenderContext. 
    virtual void              viewSetup(double viewAspect,      double viewNS,      double viewEW,
                                        double viewField,       double viewCrot,    double viewPegOffset,
                                        double setupImageWidth, double setupField,  double setupLens,
                                        double setupNear,       double setupFar,    bool   cam3dPerspective);

    virtual void              v3dSetup  (double viewAspect,     double viewNS,          double viewEW,
                                         double viewPegOffset,  double setupImageWidth, double setupNS,
                                         double setupEW,        double setupField,      double setupLens);              

    virtual void              evaluate();
    
    bool                              layoutMode() const;     

    virtual gmtl::Matrix44d           getPerspective(double fovy, double aspect, double near, double far);

    virtual const gmtl::Matrix44d&    getViewSetupMatrix() const  { return _viewSetupMatrix; }

    virtual const gmtl::Matrix44d&    get3dSetupMatrix() const    { return _3dSetupMatrix; }

    virtual const gmtl::Matrix44d&    getViewMatrix() const       { return _viewMatrix; }


  protected: 

    void                      convert(const gmtl::Matrix44d& input, gmtl::Matrix44f& output);                      


  protected:
 
    OSG::MatrixCameraRefPtr _osgCamera;
    ISceneCamera*           _sceneCamera;

    gmtl::Matrix44d         _viewSetupMatrix; 
    gmtl::Matrix44d         _3dSetupMatrix;    
    gmtl::Matrix44d         _viewMatrix;

    bool                    _layoutMode;

    View                    _view;
    Setup                   _setup;
    
};


inline LimeVrjCamera::LimeVrjCamera(const View& view, const Setup& setup) : ILimeCamera(),
  _osgCamera      (0x00),
  _sceneCamera    (0x00), 
  _layoutMode     (false),
  _view           (view),
  _setup          (setup)
{  
  gmtl::identity(_viewSetupMatrix);
  gmtl::identity(_3dSetupMatrix);
  gmtl::identity(_viewMatrix);
}


inline LimeVrjCamera::~LimeVrjCamera()
{  
}

inline ISceneCamera* LimeVrjCamera::getSceneCamera()  
{
  return _sceneCamera;
}



inline void LimeVrjCamera::setSceneCamera(ISceneCamera* sCamera)
{ 
  _sceneCamera = sCamera;  
}


inline void LimeVrjCamera::setOSGCamera(OSG::MatrixCameraRefPtr osgCamera)
{
  _osgCamera = osgCamera;  
}


inline void LimeVrjCamera::viewSetup(double viewAspect,      double viewNS,      double viewEW,
                                     double viewField,       double viewCrot,    double viewPegOffset,
                                     double setupImageWidth, double setupField,  double setupLens,
                                     double setupNear,       double setupFar,    bool   cam3dPerspective)
{
  gmtl::identity(_viewSetupMatrix);  
  
  if(layoutMode()) 
  {
    gmtl::postMult(_viewSetupMatrix, gmtl::makeScale<gmtl::Matrix44d>(gmtl::Vec3d( 1.0 / viewAspect, 1.0, 1.0 )));    
  }
  else 
  {
    gmtl::postMult(_viewSetupMatrix, gmtl::makeScale<gmtl::Matrix44d>(
    gmtl::Vec3d( 
      (1.0 / (viewField/setupField)) / viewAspect, 
      (1.0 / (viewField/setupField)), 
      1.0 )));
    
    gmtl::postMult(_viewSetupMatrix, gmtl::makeRot<gmtl::Matrix44d>(gmtl::AxisAngled( gmtl::Math::deg2Rad(-viewCrot), 0.0, 0.0, 1.0 )));
    
    gmtl::postMult(_viewSetupMatrix, gmtl::makeTrans<gmtl::Matrix44d>(
    gmtl::Vec3d(
      ((viewPegOffset - viewEW)/100.0) / (setupField/2.0) * viewAspect, 
      ((5000.0 - viewNS)/100.0) / (setupField/2.0) * viewAspect, 
      0.0 )));
  }

  gmtl::postMult(_viewSetupMatrix, getPerspective( 90.0, 1.0, setupNear, setupFar ));

  gmtl::postMult(_viewSetupMatrix, gmtl::makeScale<gmtl::Matrix44d>(
  gmtl::Vec3d( 
    UnitConversions::MMToInch(setupLens) *2.0/setupImageWidth, 
    UnitConversions::MMToInch(setupLens)*2.0/setupImageWidth, 
    1.0)));

  gmtl::postMult(_viewSetupMatrix, gmtl::makeTrans<gmtl::Matrix44d>(
  gmtl::Vec3d( 
    0.0, 
    0.0, 
    (-setupField/setupImageWidth* UnitConversions::MMToInch(setupLens) / viewAspect))));
   
}


inline void LimeVrjCamera::v3dSetup(double viewAspect,     double viewNS,          double viewEW,
                                    double viewPegOffset,  double setupImageWidth, double setupNS,
                                    double setupEW,        double setupField,      double setupLens)
{
  gmtl::identity(_3dSetupMatrix);  
 
  double PRP[3], CW[3], DOP[3];
  double shx, shy;

  CW[0] = CW[1] = CW[2] = 0.0;

  PRP[0] = (5000.0 - setupEW) / 100.0;
  PRP[1] = (5000.0 - setupNS) / 100.0;

/*     PRP[2] = -setup_field/setup_imagewidth*MMToInch(setup_lens) / 1.68421; */
  PRP[2] = -setupField/setupImageWidth * UnitConversions::MMToInch(setupLens) / 1.3714;

  DOP[0] = CW[0] - PRP[0];
  DOP[1] = CW[1] - PRP[1];
  DOP[2] = CW[2] - PRP[2];

  shx = -( DOP[0] / DOP[2] );
  shy = -( DOP[1] / DOP[2] );

  double SH[16] = {1.0,    0.0,    0.0,    0.0,
                   0.0,    1.0,    0.0,    0.0,
                   shx,    shy,    1.0,    0.0,
                   0.0,    0.0,    0.0,    1.0};

      
  _3dSetupMatrix.set(SH);
}  


inline void LimeVrjCamera::evaluate()
{
  // Calculate project and modelview matrix here.    
  gmtl::Vec3d x   (_sceneCamera->getXDir());  
  gmtl::Vec3d up  (_sceneCamera->getUpDir());  
  gmtl::Vec3d look(_sceneCamera->getLookDir());
  gmtl::Vec3d pos (_sceneCamera->getPosition());

  gmtl::normalize(x);
  gmtl::normalize(up);
  gmtl::normalize(look); 

  //std::cout << "x is"     << x    << std::endl;
  //std::cout << "up is"    << up   << std::endl;
  //std::cout << "look is"  << look << std::endl;
  //std::cout << "pos is"   << pos  << std::endl;
  
  // GMTL set(...) takes row major args.
  _viewMatrix.set(x[0],    x[1],    x[2],    (-(x[0]*pos[0])     - (x[1]*pos[1])     - (x[2]*pos[2])),
                  up[0],   up[1],   up[2],   (-(up[0]*pos[0])    - (up[1]*pos[1])    - (up[2]*pos[2])),
                  look[0], look[1], look[2], (-(look[0]*pos[0])  - (look[1]*pos[1])  - (look[2]*pos[2])), 
                  0.0,     0.0,     0.0,      1.0);   

  this->viewSetup(_view.getAspect(),     _view.getNS(),     _view.getEW(), 
                  _view.getField(),      _view.getCrot(),   _view.getPegOffset(), 
                  _setup.getImageWidth(),_setup.getField(), _setup.getLens(), 
                  _setup.getNear(),      _setup.getFar(),   true); 
  
  this->v3dSetup(_view.getAspect(),     _view.getNS(),          _view.getEW(),
                 _view.getPegOffset(),  _setup.getImageWidth(), _setup.getNS(),
                 _setup.getEW(),        _setup.getField(),      _setup.getLens());  
  
  //std::cout << "View matrix is: " << _viewMatrix << std::endl; 
  
  gmtl::Matrix44f viewMat;
  this->convert(_viewMatrix, viewMat);  
  OSG::Matrix     osgViewMat; 
  osgViewMat.setValue(viewMat.mData);  

  // Combine view setup and 3dsetup matrices as projection matrix. 
  gmtl::Matrix44d setupMat;
  gmtl::mult(setupMat, _viewSetupMatrix, _3dSetupMatrix);
  
  gmtl::Matrix44f projMat;
  this->convert(setupMat, projMat);
  OSG::Matrix osgProjMat; 
  osgProjMat.setValue(projMat.mData);
  
  // \note Storing everything in the model view matrix did not work. 
  //       OSG seems to need projection matrix as separate. 

  // Finally set all the values.
  _osgCamera->setModelviewMatrix(osgViewMat);  
  _osgCamera->setProjectionMatrix(osgProjMat);  
  _osgCamera->setNear (_setup.getNear());
  _osgCamera->setFar  (_setup.getFar());  
}


inline bool LimeVrjCamera::layoutMode() const
{
  return _layoutMode;
}


inline gmtl::Matrix44d LimeVrjCamera::getPerspective(double fovy, double aspect, double near, double far)
{
  double depth = far - near;   

  double halfAngle = (fovy * (3.14159/180.0)) / 2.0;

  double cotHalfAngle = cos(halfAngle) / sin(halfAngle);

  gmtl::Matrix44d mat;

  double P[16] = {cotHalfAngle/aspect,    0.0,            0.0,                  0.0,
          0.0,                    cotHalfAngle,   0.0,                  0.0,
          0.0,                    0.0,            -(far+near)/depth,   -1.0,
          0.0,                    0.0,            -2.0*far*near/depth,  0.0};
  
  // P is column major and gmtl set(Type*) takes column major Type(double, float) array.   
  mat.set(P);

  return mat;
}


inline void LimeVrjCamera::convert(const gmtl::Matrix44d& input, gmtl::Matrix44f& output)
{
  for(unsigned int i=0; i < 4; ++i)
  {
    for(unsigned int j=0; j < 4; ++j)
    { 
      output[i][j] = static_cast<float>(input[i][j]);
    }
  }
}

#endif // __LIME_CAMERA_H__

