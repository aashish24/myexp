
#ifndef __VIEW_H__
#define __VIEW_H__

class View
{
  public: 
    
                          View(); 
                          View(double viewAspect, double viewNS,   double viewEW, 
                               double viewField,  double viewCrot, double viewPegOffset);

      
                         ~View();
  
    const double&         getAspect()     const;

    const double&         getNS()         const;
      
    const double&         getEW()         const;

    const double&         getField()      const;

    const double&         getCrot()       const;

    const double&         getPegOffset()  const;  

   
 private: 

    double _viewAspect;
    double _viewNS;
    double _viewEW;
    double _viewField;
    double _viewCrot;
    double _viewPegOffset;
};


inline View::View() : 
  _viewAspect   (1.3333), 
  _viewNS       (5000.0), 
  _viewEW       (5000.0), 
  _viewField    (16.0), 
  _viewCrot     (0.0),
  _viewPegOffset(5000.0)
{
}


inline View::View(double viewAspect, double viewNS,   double viewEW, 
                  double viewField,  double viewCrot, double viewPegOffset) :
  _viewAspect   (viewAspect), 
  _viewNS       (viewNS), 
  _viewEW       (viewEW), 
  _viewField    (viewField), 
  _viewCrot     (viewCrot), 
  _viewPegOffset(viewPegOffset)
{  
}
 

inline View::~View()
{
}


inline const double& View::getAspect() const
{
  return _viewAspect;
}


inline const double& View::getNS() const
{
  return _viewNS;
}    


inline const double& View::getEW() const
{
  return _viewEW;
}


inline const double& View::getField() const
{
  return _viewField;
}


inline const double& View::getCrot() const
{
  return _viewCrot;
}


inline const double& View::getPegOffset() const
{
  return _viewPegOffset;
}  

#endif // __VIEW_H__

