
#ifndef __LIME_CAMERA_VIEW_H__
#define __LIME_CAMERA_VIEW_H__

class LimeCameraView
{
  public: 
    
                          CameraView(); 
                          CameraView(double viewAspect, double viewNS, 
                                    double viewEW,     double viewField, 
                                    double viewCrot,   double viewPegOffset);

      
                         ~CameraView();
  
    const double& getViewAspect()     const;
    const double& getViewNS()         const;
    const double& getViewEW()         const;
    const double& getViewField()      const;
    const double& getViewCrot()       const;
    const double& getViewPegoffset()  const;  
    
    double _viewAspect,
    double _viewNS,
    double _viewEW,
    double _viewField,
    double _viewCrot,
    double _viewPegoffset
};


inline CameraView::CameraView() :
  _viewAspect   (1.0), 
  _viewNS       (5000.0), 
  _viewEW       (5000.0), 
  _viewField    (16.0), 
  _viewCrot     (0.0),
  _viewPegoffset(5000.0)
{
}
 

#endif // __LIME_CAMERA_VIEW_H__
