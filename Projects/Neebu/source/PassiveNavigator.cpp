
#include <PassiveNavigator.h>

// gmtl includes
#include <gmtl/Generate.h>


    PassiveNavigator::PassiveNavigator(vrj::App *pApp)
    
    : Inherited(pApp),
      mPos(),
      mRot(),
      mScale()
{
    // nothing to do
}


    PassiveNavigator::~PassiveNavigator(void)
{
    // nothing to do
}

void
    PassiveNavigator::initialize(void)
{
    if(getInitialized())
        return;
    
    Inherited::initialize();
}

void
    PassiveNavigator::navigate(
        gmtl::Matrix44f const &matrix,
        gmtl::Matrix44f       &newMatrix)
{
    if(getEnabled() == false)
        return;
    
    Inherited::navigate(matrix, newMatrix);
    
    gmtl::Matrix44f tmpMat;
    
    // set tranlation and rotation parts
    gmtl::setTrans(newMatrix, mPos);
    gmtl::setRot  (newMatrix, mRot);
    
    // multiply the scale on top
    gmtl::setScale(tmpMat, mScale);
    gmtl::mult(newMatrix, newMatrix, tmpMat);
}

