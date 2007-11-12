
#ifndef __I_OSG_MODEL_H__
#define __I_OSG_MODEL_H__

#include "IModel.h" 

struct IOsgModel : public IModel
{
  enum{ IID = 3 };

  virtual osg::Node*    root() = 0;  

  virtual osg::Node*    rootNav() = 0;

  virtual osg::Node*    rootModel() = 0;  
  
  virtual osg::Node*    rootStatic() = 0;
  
  virtual osg::Node*    rootScreen() = 0;
  
  virtual void          setSceneData( osg::Node* node ) = 0;
};

#endif // __I_OSG_MODEL_H__