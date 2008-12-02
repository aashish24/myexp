
#ifndef __BG_H__
#define __BG_H__


class BG
{
  public: 
    
                  BG(); 
                  BG(double bgAspect, double bgNS,   double bgEW,  
                             double bgField,  double bgCrot, double bgPegOffset);
      
                 ~BG();
      
    const double& getAspect()                             const;
          void    setAspect(const double& bgAspect);

    const double& getNS()                                 const;
          void    setNS(const double& bsNS);
      
    const double& getEW()                                 const;
          void    setEW(const double& bgEW);

    const double& getField()                              const;
          void    setField(const double& bgField);

    const double& getCrot()                               const;
          void    setCrot(const double& bgCrot);

    const double& getPegOffset()                          const;
          void    setPegOffset(const double& bgPegOffset);

  
  private: 
    
    double _bgAspect;
    double _bgNS;
    double _bgEW;
    double _bgField;
    double _bgCrot;
    double _bgPegOffset;
};


inline BG::BG() :
  _bgAspect     (1.6),   
  _bgNS         (5000.0), 
  _bgEW         (5000.0), 
  _bgField      (10.0), 
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


inline void BG::setAspect(const double& bgAspect)
{
  _bgAspect = bgAspect;
}


inline const double& BG::getNS() const
{
  return _bgNS;
}    


inline void BG::setNS(const double& bgNS)
{
  _bgNS = bgNS;
}


inline const double& BG::getEW() const
{
  return _bgEW;
}


inline void BG::setEW(const double& bgEW)
{
  _bgEW = bgEW;
}

 
inline const double& BG::getField() const
{
  return _bgField;
}


inline void BG::setField(const double& bgField)
{
  _bgField = bgField;
}


inline const double& BG::getCrot() const
{
  return _bgCrot;
}


inline void BG::setCrot(const double& bgCrot)
{
  _bgCrot = bgCrot;
}


inline const double& BG::getPegOffset() const
{
  return _bgPegOffset;
}  


inline void BG::setPegOffset(const double& bgPegOffset)
{
  _bgPegOffset = bgPegOffset;
}

#endif // __BG_H__


