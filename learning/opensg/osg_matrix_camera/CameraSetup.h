
#ifndef __LIME_CAMERA_VIEW_H__
#define __LIME_CAMERA_VIEW_H__

class CameraView
{
  public: 
    
                          CameraView(); 
                          CameraView(double viewAspect, double viewNS,   double viewEW, 
                                     double viewField,  double viewCrot, double viewPegOffset);

      
                         ~CameraView();
  
    const double& getViewAspect()     const;
    const double& getViewNS()         const;      
    const double& getViewEW()         const;
    const double& getViewField()      const;
    const double& getViewCrot()       const;
    const double& getViewPegOffset()  const;  
    
    double _viewAspect,
    double _viewNS,
    double _viewEW,
    double _viewField,
    double _viewCrot,
    double _viewPegOffset
};


inline CameraView::CameraView() :
  _viewAspect   (1.0), 
  _viewNS       (5000.0), 
  _viewEW       (5000.0), 
  _viewField    (16.0), 
  _viewCrot     (0.0),
  _viewPegOffset(5000.0)
{
}


inline CameraView::CameraView(double viewAspect, double viewNS,   double viewEW, 
                              double viewField,  double viewCrot, double viewPegOffset) :
  _viewAspect   (viewAspect), 
  _viewNS       (viewNS), 
  _viewEW       (viewEW), 
  _viewField    (viewField), 
  _viewCrot     (viewCrot), 
  _viewPegPffset(viewPegOffset)
{  
}
 

inline const double& CameraView::getViewAspect() const
{
  return _viewAspect;
}


inline const double& CameraView::getViewNS() const
{
  return _viewNS;
}    


inline const double& CameraView::getViewEW() const
{
  return _viewEW;
}


inline const double& CameraView::getViewField() const
{
  return _viewField;
}


inline const double& CameraView::getViewCrot() const
{
  return _viewCrot;
}


inline const double& CameraView::getViewPegOffset() const
{
  return _viewPegOffset;
}  

#endif // __LIME_CAMERA_VIEW_H__

