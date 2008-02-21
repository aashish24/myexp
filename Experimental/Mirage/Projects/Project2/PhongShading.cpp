
#include "PhongShading.h"
#include "ShadersUtil.h"

namespace Project
{
  PhongShading::PhongShading() : 
    _program( 0x00 )
  {
  }


  PhongShading::~PhongShading()
  {
  }


  void PhongShading::setShaders( const std::string &vert, const std::string &frag )
  {
    ShadersUtil* shUtil = new ShadersUtil();
    shUtil->setShaders( vert, frag );
    delete shUtil;
  }
}