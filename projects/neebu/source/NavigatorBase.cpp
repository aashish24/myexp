
#include <NavigatorBase.h>

#include <vpr/Util/Interval.h>

#include <vrj/Kernel/Kernel.h>
#include <vrj/Kernel/User.h>

/*=======================================================================*/
/* Construction/Destruction                                              */

NavigatorBase::NavigatorBase(vrj::App *pApp)
    : mInitialized           (false),
      mEnabled               (true),
      mApp                   (pApp),
      mTime                  (),
      mFPSNormalizationFactor(0.05f),
      mRotateFactor          (1.0f),
      mTranslateFactor       (3.0f)
{
    mTime.setNow();
}

NavigatorBase::~NavigatorBase(void)
{
}    

/*=======================================================================*/
/* Initialization                                                        */

void
NavigatorBase::initialize(void)
{
    if(mInitialized == true)
        return;
 
    mInitialized = true;
}

/*=======================================================================*/
/* Navigation                                                            */

void
NavigatorBase::updateTime(vpr::Interval const &time)
{
    mFPSNormalizationFactor = (time.msec() - mTime.msec()) / 1000.0;
    mTime = time;
}

/*! Compute the new camera coordinate system and store it to \a newMatrix.
    The previous camera coordinate system is available as \a matrix.
    
    Derived classes that override this function need to call the base class
    function in order to ensure correct updates of the frame rate independent
    scale factors (available through \c getFPSNormalizedRotateFactor and
    \c getFPSNormalizedTranslateFactor).
 */
void
NavigatorBase::navigate(gmtl::Matrix44f const &matrix,
                        gmtl::Matrix44f       &newMatrix)
{
    if((getEnabled() == false) || (getInitialized() == false))
        return;
}

/*=======================================================================*/
/* Helper                                                                */

float
NavigatorBase::readAdjustedAnalog(
    gadget::AnalogInterface &analog, bool &hasData, float deadZone) const
{
    float rawData = analog->getData();
    
//     vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
//         << "NavigatorBase::readAdjustedAnalog: rawData: "
//         << rawData << std::endl << vprDEBUG_FLUSH;
    
    if(!hasData && rawData > 0.0f)
        hasData = true;
        
    if(hasData)
    {
//         vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
//                 << "NavigatorBase::readAdjustedAnalog: Returning real data."
//                 << std::endl << vprDEBUG_FLUSH;
    
        return adjustAnalog(rawData, deadZone);
    }
    else
    {
//         vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
//             << "NavigatorBase::readAdjustedAnalog: Returning fake data."
//             << std::endl << vprDEBUG_FLUSH;
    
        return 0.0f;
    }        
}

float
NavigatorBase::adjustAnalog(float analogIn, float deadZone) const
{
    // scale to [-1.0, 1.0]
    float analogOut = (analogIn * 2.0f) - 1.0f;
    
    // dead zone -- values are adjusted to avoid jumps when leaving the d.z.
    if(-deadZone < analogOut && analogOut < deadZone)
    {
        analogOut = 0.0f;
    }
    else if(analogOut <= -deadZone)
    {
        analogOut += deadZone;
    }
    else
    {
        analogOut -= deadZone;
    }
    
    return analogOut;
}
