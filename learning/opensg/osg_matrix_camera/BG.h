
#ifndef __BG_H__
#define __BG_H__


class BG
{
  public: 
    
                          BG(); 
                          BG(double bgAspect, double bgNS,   double bgEW,  
                             double bgField,  double bgCrot, double bgPegOffset);
      
                         ~BG();
      
    const double& getAspect()     const;

    const double& getNS()         const;
      
    const double& getEW()         const;

    const double& getField()      const;

    const double& getCrot()       const;

    const double& getPegOffset()  const;

  
  private: 
    
    double _bgAspect;
    double _bgNS;
    double _bgEW;
    double _bgField;
    double _bgCrot;
    double _bgPegOffset;
};


inline BG::BG() :
  _bgAspect     (1.3333),   
  _bgNS         (5000.0), 
  _bgEW         (5000.0), 
  _bgField      (16.0), 
  _bgCrot       (0.0),
  _bgPegOffset  (5000.0)
{
}


inline BG::BG(double bgAspect, double bgNS,   double bgEW,  
              double bgField,  double bgCrot, double bgPegOffset) :
  _bgAspect   (bgAspect),
  _bgNS       (bgNS), 
  _bgEW       (bgEW), 
  _bgField    (bgField), 
  _bgCrot     (bgCrot), 
  _bgPegOffset(bgPegOffset)
{  
}
 

inline BG::~BG()
{
}


inline const double& BG::getAspect() const
{
  return _bgAspect;
}


inline const double& BG::getNS() const
{
  return _bgNS;
}    


inline const double& BG::getEW() const
{
  return _bgEW;
}


inline const double& BG::getField() const
{
  return _bgField;
}


inline const double& BG::getCrot() const
{
  return _bgCrot;
}


inline const double& BG::getPegOffset() const
{
  return _bgPegOffset;
}  

#endif // __BG_H__


