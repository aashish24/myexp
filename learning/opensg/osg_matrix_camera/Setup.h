
#ifndef __SETUP_H__
#define __SETUP_H__

class Setup
{
  public: 
    
                  Setup(); 
                  Setup(double setupImageWidth, double setupNS,   double setupEW, 
                        double setupField,      double setupLens, double setupNear, 
                        double setupFar);

      
                 ~Setup();
  
    const double& getImageWidth()  const;
    void          setImageWidth(const double& setupImageWidth);

    const double& getNS()          const;
    void          setNS(const double& setupNS);

    const double& getEW()          const;
    void          setEW(const double& setupEW);

    const double& getField()       const;
    void          setField(const double& setupField);

    const double& getLens()        const;
    void          setLens(const double& setupLens);
      
    const double& getNear()        const;
    void          setNear(const double& setupNear);

    const double& getFar()         const;
    void          setFar(const double& setupFar);

  
  private:
  
    double _setupImageWidth;
    double _setupNS;
    double _setupEW;
    double _setupField;
    double _setupLens;
    double _setupNear;
    double _setupFar;    
};


inline Setup::Setup() :
  _setupImageWidth(1.0),
  _setupNS        (5000.0),
  _setupEW        (5000.0),
  _setupField     (16.0),
  _setupLens      (35.0),
  _setupNear      (0.1),
  _setupFar       (5000.0)  
{
}


inline Setup::Setup(double setupImageWidth, double setupNS,   double setupEW, 
                    double setupField,      double setupLens, double setupNear, 
                    double setupFar) :
  _setupImageWidth(setupImageWidth),
  _setupNS        (setupNS),
  _setupEW        (setupEW),
  _setupField     (setupField),
  _setupLens      (setupLens),
  _setupNear      (setupNear),
  _setupFar       (setupFar)
{  
}
 

inline Setup::~Setup()
{
}


inline const double& Setup::getImageWidth() const
{
  return _setupImageWidth;
}


inline void Setup::setImageWidth(const double& setupImageWidth)
{
  _setupImageWidth = setupImageWidth;    
}


inline const double& Setup::getNS() const
{
  return _setupNS;
}


inline void Setup::setNS(const double& setupNS)
{
  _setupNS = setupNS;
}


inline const double& Setup::getEW() const 
{
  return _setupEW;
}


inline void Setup::setEW(const double& setupEW)
{
  _setupEW = setupEW;
}


inline const double& Setup::getField() const
{
  return _setupField;
}    


inline void Setup::setField(const double& setupField)
{
  _setupField = setupField;
}


inline const double& Setup::getLens() const
{
  return _setupLens;
}


inline void Setup::setLens(const double& setupLens)
{
  _setupLens = setupLens;
}


inline const double& Setup::getNear() const
{
  return _setupNear;
}


inline void Setup::setNear(const double& setupNear) 
{
  _setupNear = setupNear;
}


inline const double& Setup::getFar() const
{
  return _setupFar;
}


inline void Setup::setFar(const double& setupFar)
{
  _setupFar = setupFar;
}  

#endif // __SETUP_H__

