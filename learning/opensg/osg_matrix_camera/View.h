
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
    void                  setAspect(const double& viewAspect);

    const double&         getNS()         const;
    void                  setNS(const double& viewNS);
      
    const double&         getEW()         const;
    void                  setEW(const double& viewEW);

    const double&         getField()      const;
    void                  setField(const double& viewField);

    const double&         getCrot()       const;
    void                  setCrot(const double& viewCrot);

    const double&         getPegOffset()  const;  
    void                  setPegOffset(const double& viewPegOffset);

   
 private: 

    double _viewAspect;
    double _viewNS;
    double _viewEW;
    double _viewField;
    double _viewCrot;
    double _viewPegOffset;
};


inline View::View() : 
  _viewAspect   (1.7777), 
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


inline void View::setAspect(const double& viewAspect)
{
  _viewAspect = viewAspect;
}


inline const double& View::getNS() const
{
  return _viewNS;
}    


inline void View::setNS(const double& viewNS)
{
  _viewNS = viewNS;
}


inline const double& View::getEW() const
{
  return _viewEW;
}


inline void View::setEW(const double& viewEW)
{
  _viewEW = viewEW;
}


inline const double& View::getField() const
{
  return _viewField;
}


inline void View::setField(const double& viewField)
{
  _viewField = viewField;
}


inline const double& View::getCrot() const
{
  return _viewCrot;
}


inline void View::setCrot(const double& viewCrot)
{
  _viewCrot = viewCrot;
}


inline const double& View::getPegOffset() const
{
  return _viewPegOffset;
}  


inline void View::setPegOffset(const double& viewPegOffset)
{
  _viewPegOffset = viewPegOffset;
}

#endif // __VIEW_H__


