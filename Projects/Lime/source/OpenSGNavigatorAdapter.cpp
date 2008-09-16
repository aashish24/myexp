
#include <OpenSGNavigatorAdapter.h>

#include <gmtl/MatrixOps.h>
#include <gmtl/Xforms.h>

/*=======================================================================*/
/* Construction/Destruction                                              */

OpenSGNavigatorAdapter::OpenSGNavigatorAdapter(void)
    : Inherited()
{
}

OpenSGNavigatorAdapter::~OpenSGNavigatorAdapter(void)
{
}

/*=======================================================================*/
/* Forwarding                                                            */

void
OpenSGNavigatorAdapter::navigate(void)
{
    gmtl::Matrix44f matrix;
    gmtl::Matrix44f newMatrix;
    
    matrix.set(mTransform->getMatrix().getValues());
        
    mNavigator->navigate(matrix, newMatrix);
    
    if (mNavMode == NAV_INCREMENTAL){
//     	std::cout << " INCREMENTAL NAVIGATION .... " <<std::endl;
    	// newMatrix = newMatrix * matrix
    	gmtl::mult(newMatrix, newMatrix, matrix);
    }
    
    OSG::beginEditCP(mTransform);
        mTransform->getMatrix().setValue(newMatrix.getData());
    OSG::endEditCP(mTransform);
}
