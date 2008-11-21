
#ifndef __LIME_CAMERA_BASE_H__
#define __LIME_CAMERA_BASE_H__

// Lime includes. 
#include "ILimeCamera.h"
#include "ISceneCamera.h"
#include "Setup.h"
#include "View.h"
#include "BG.h"

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
                              LimeVrjCamera(const View& view=View(), const Setup& setup=Setup(), const BG& bg=BG());
    virtual                  ~LimeVrjCamera();    

    ISceneCamera*             getSceneCamera();
    virtual void              setSceneCamera(ISceneCamera* sCamera);

    virtual void              setOSGCamera(OSG::MatrixCameraRefPtr osgCamera);

    // \note Move these functions into RenderContext. 
    virtual void              viewSetup(double viewAspect,      double viewNS,      double viewEW,
                                        double viewField,       double viewCrot,    double viewPegOffset,
                                        double setupImageWidth, double setupField,  double setupLens,
                                        double setupNear,       double setupFar,    double bgAspect,
                                        double bgNS,            double bgEW,        double bgField,
                                        double bgCrot,          double bgPegOffset, bool   cam3dPerspective);

    virtual void              v3dSetup  (double viewAspect,     double viewNS,          double viewEW,
                                         double viewPegOffset,  double setupImageWidth, double setupNS,
                                         double setupEW,        double setupField,      double setupLens);              

    virtual void              evaluate();
    
    bool                      layoutMode() const;     

    virtual gmtl::Matrix44d   getPerspective(double fovy, double aspect, double near, double far);


  protected: 

    void                      convert(const gmtl::Matrix44d& input, gmtl::Matrix44f& output);                      


  protected:
 
    OSG::MatrixCameraRefPtr _osgCamera;
    ISceneCamera*           _sceneCamera;

    gmtl::Matrix44d         _viewSetupMatrix; 
    gmtl::Matrix44d         _3dSetupMatrix;    

    bool                    _layoutMode;

    double                  _mmToInch;

    View                    _view;
    
    Setup                   _setup;

    BG                      _bg;
};


inline LimeVrjCamera::LimeVrjCamera(const View& view, const Setup& setup, const BG& bg) : ILimeCamera(),
  _osgCamera      (0x00),
  _sceneCamera    (0x00), 
  _layoutMode     (false), 
  _mmToInch       (0.0393700787),
  _view           (view),
  _setup          (setup), 
  _bg             (bg)
{  
  gmtl::identity(_viewSetupMatrix);
  gmtl::identity(_3dSetupMatrix);
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
                                     double setupNear,       double setupFar,    double bgAspect,
                                     double bgNS,            double bgEW,        double bgField,
                                     double bgCrot,          double bgPegOffset, bool   cam3dPerspective)
{
  gmtl::identity(_viewSetupMatrix);
  if(layoutMode())
  {
    gmtl::postMult(_viewSetupMatrix, gmtl::makeTrans<gmtl::Matrix44d>(gmtl::Vec3d(
      (((bgPegOffset - bgEW)/100.0) / (bgField/2.0)), 
      (((5000.0 - bgNS)/100.0) / (bgField/2.0)) * viewAspect, 
      0.0)));
  }
  else
  {
    gmtl::postMult(_viewSetupMatrix, gmtl::makeScale<gmtl::Matrix44d>(gmtl::Vec3d(
     -(1.0 / (viewField/bgField)), 
      (1.0 / (viewField/bgField)), 
      1.0)));   
  }

  if(!cam3dPerspective)
  {
    // \todo Print some warning message. 
  }

  gmtl::postMult(_viewSetupMatrix, getPerspective(90.0, 1.0, setupNear, setupFar));

  gmtl::postMult(_viewSetupMatrix, gmtl::makeScale<gmtl::Matrix44d>(gmtl::Vec3d(
      ((_mmToInch * setupLens * 2.0 ) / setupImageWidth), 
      ((_mmToInch * setupLens * 2.0 ) / setupImageWidth ) * viewAspect, 
      1.0 ))); 

  if(!layoutMode())
  { 
    gmtl::postMult(_viewSetupMatrix, gmtl::makeRot<gmtl::Matrix44d>(gmtl::AxisAngled(-viewCrot, 0.0, 0.0, 1.0))); 
  }   
}


inline void LimeVrjCamera::v3dSetup(double viewAspect,     double viewNS,          double viewEW,
                                    double viewPegOffset,  double setupImageWidth, double setupNS,
                                    double setupEW,        double setupField,      double setupLens)
{
  gmtl::identity(_3dSetupMatrix);
  
  double PRP[3], CW[3], DOP[3];
  double shx, shy;

  if(layoutMode() ) 
  {
    CW[0] = CW[1] = CW[2] = 0.0;
  }
  else
  {
    CW[0] = (viewPegOffset - viewEW) / 100.0;
    CW[1] = (5000.0 - viewNS) / 100.0;
    CW[2] = 0.0;
  }

  PRP[0] = (5000.0 - setupEW) / 100.0;
  PRP[1] = (5000.0 - setupNS) / 100.0;
  PRP[2] = -setupField/setupImageWidth* _mmToInch * setupLens;

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
  gmtl::Vec4d x   (_sceneCamera->getXDir());  
  gmtl::Vec4d up  (_sceneCamera->getUpDir());  
  gmtl::Vec4d look(_sceneCamera->getLookDir());
  gmtl::Vec4d pos (_sceneCamera->getPosition());

  // GMTL set(...) takes row major args. 
  gmtl::Matrix44d mat; 
  mat.set(x[0],    x[1],    x[2],    -((x[0]*pos[0])     - (x[1]*pos[1])     - (x[2]*pos[2])),
          up[0],   up[1],   up[2],   -((up[0]*pos[0])    - (up[1]*pos[1])    - (up[2]*pos[2])),
          look[0], look[1], look[2], -((look[0]*pos[0])  - (look[1]*pos[1])  - (look[2]*pos[2])),
          0.0,     0.0,     0.0,     1.0);  

  // Hardcoded as of now. 
  //   this->viewSetup(1.7777, 5000.0, 5000.0, 
  //                   16.0,   0.0,    0.0, 
  //                   1.0,    16.0,   18.0,   
  //                   0.1,    5000.0, 1.7777, 
  //                   5000.0, 5000.0, 16.0, 

  this->viewSetup(_view.getAspect(),     _view.getNS(),     _view.getEW(), 
                  _view.getField(),      _view.getCrot(),   _view.getPegOffset(), 
                  _setup.getImageWidth(),_setup.getField(), _setup.getLens(), 
                  _setup.getNear(),      _setup.getFar(),   _bg.getAspect(), 
                  _bg.getNS(),           _bg.getEW(),       _bg.getField(), 
                  _bg.getCrot(),         _bg.getPegOffset(), true); 
  
  this->v3dSetup(_view.getAspect(),     _view.getNS(),          _view.getEW(),
                 _view.getPegOffset(),  _setup.getImageWidth(), _setup.getNS(),
                 _setup.getEW(),        _setup.getField(),      _setup.getLens());

  gmtl::preMult(mat, _viewSetupMatrix);
  gmtl::preMult(mat, _3dSetupMatrix);
  gmtl::Matrix44f compMat;

  this->convert(mat, compMat);
  
  OSG::Matrix     osgCompMat; 
  osgCompMat.setValue(compMat.mData);

//   std::cout << "Projection matrix is: " << std::endl;
//   for(size_t i=0; i < 4; ++i)
//   {
//     for(size_t j=0; j < 4; ++j)
//     {
//       std::cout << "row " << i << " col " << j << " " << _viewSetupMatrix[i][j] << std::endl;
//     }

  _osgCamera->setModelviewMatrix  (osgCompMat);
  _osgCamera->setProjectionMatrix (OSG::Matrix());
  _osgCamera->setNear (0.1);
  _osgCamera->setFar  (5000.0);  
}


inline bool LimeVrjCamera::layoutMode() const
{
  return _layoutMode;
}


inline gmtl::Matrix44d LimeVrjCamera::getPerspective(double fovy, double aspect, double near, double far)
{
  double depth = far - near;   

  double halfAngle = ( fovy * (3.14159/180.0) ) / 2.0;

  double cotHalfAngle = cos( halfAngle ) / sin( halfAngle );

  gmtl::Matrix44d mat;

  double P[16] = {cotHalfAngle/aspect,    0.0,            0.0,                  0.0,
          0.0,                    cotHalfAngle,   0.0,                  0.0,
          0.0,                    0.0,            -(far+near)/depth,   -1.0,
          0.0,                    0.0,            -2.0*far*near/depth,  0.0};
  
  // P is column major. 
  mat.set(P);
  
//   std::cout << "Pespective matrix is: " << std::endl;
//   for(size_t i=0; i < 4; ++i)
//   {
//     for(size_t j=0; j < 4; ++j)
//     {
//       std::cout << "row " << i << " col " << j << " " << mat[i][j] << std::endl;
//     }

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

