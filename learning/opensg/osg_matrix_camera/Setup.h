
#ifndef __SETUP_H__
#define __SETUP_H__

class Setup
{
  public: 
    
                          Setup(); 
                          Setup(double setupImageWidth, double setupField, double setupLens, 
                                double setupNear, double setupFar);

      
                         ~Setup();
  
    const double& getImageWidth()  const;
    const double& getField()       const;
    const double& getLens()        const;      
    const double& getNear()        const;
    const double& getFar()         const;
    
    double _setupImageWidth;
    double _setupField;
    double _setupLens;
    double _setupNear;
    double _setupFar;    
};


inline Setup::Setup() :
  _setupImageWidth(1.0),
  _setupField     (16.0),
  _setupLens      (35.0),
  _setupNear      (0.1),
  _setupFar       (10000.0)  
{
}


inline Setup::Setup(double setupImageWidth, double setupField, double setupLens, 
                    double setupNear, double setupFar) :
  _setupImageWidth(setupImageWidth),
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


inline const double& Setup::getField() const
{
  return _setupField;
}    


inline const double& Setup::getLens() const
{
  return _setupLens;
}


inline const double& Setup::getNear() const
{
  return _setupNear;
}


inline const double& Setup::getFar() const
{
  return _setupFar;
}  

#endif // __SETUP_H__

