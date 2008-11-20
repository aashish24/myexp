
#include <GamepadNavigator.h>

#include <gmtl/Generate.h>
#include <gmtl/VecOps.h>
#include <gmtl/Xforms.h>

GamepadNavigator::GamepadNavigator(vrj::App *pApp)
    : Inherited           (pApp),
      mAnalogRotate       (),
      mAnalogLookUpDown   (),
      mAnalogStrafe       (),
      mAnalogMove         (),
      mButtonUpDownMode   (),
      mButtonMoveUp       (),
      mButtonMoveDown     (),
      mAnalogRotateName        ("GamepadStickLeftAxisX"),
      mAnalogLookUpDownName    ("GamepadStickLeftAxisY"),
      mAnalogStrafeName        ("GamepadStickRightAxisX"),
      mAnalogMoveName          ("GamepadStickRightAxisY"),
      mButtonMoveUpDownModeName("GamepadButtonUpDownMode"),
      mButtonMoveUpName        ("GamepadButtonMoveUp"),
      mButtonMoveDownName      ("GamepadButtonMoveDown"),
      mStickHasData            (false)
{
}

GamepadNavigator::~GamepadNavigator(void)
{
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setAnalogRotateName(std::string const  &analogName)
{
    mAnalogRotateName = analogName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setAnalogLookUpDownName(std::string const  &analogName)
{
    mAnalogLookUpDownName = analogName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setAnalogStrafeName(std::string const &analogName)
{
    mAnalogStrafeName = analogName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setAnalogMoveName(std::string const &analogName)
{
    mAnalogMoveName = analogName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setButtonMoveUpDownModeName(std::string const &buttonName)
{
    mButtonMoveUpDownModeName = buttonName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setButtonMoveUpName(std::string const &buttonName)
{
    mButtonMoveUpName = buttonName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
GamepadNavigator::setButtonMoveDownName(std::string const &buttonName)
{
    mButtonMoveDownName = buttonName;
}

void
GamepadNavigator::initialize(void)
{
    if(getInitialized())
        return;
    
    Inherited::initialize();
   
    mAnalogRotate    .init(mAnalogRotateName);
    mAnalogLookUpDown.init(mAnalogLookUpDownName);
    mAnalogStrafe    .init(mAnalogStrafeName);
    mAnalogMove      .init(mAnalogMoveName);
    mButtonUpDownMode.init(mButtonMoveUpDownModeName);
    mButtonMoveUp    .init(mButtonMoveUpName);
    mButtonMoveDown  .init(mButtonMoveDownName);
}

void
GamepadNavigator::navigate(
    gmtl::Matrix44f const &matrix, gmtl::Matrix44f &newMatrix)
{
    if(getEnabled() == false)
        return;

    Inherited::navigate(matrix, newMatrix);
        
//    std::cout << "Position:"
//              << matrix[0][3] << "  "
//              << matrix[1][3] << "  "
//              << matrix[2][3] << "  "
//              << matrix[3][3] << std::endl;
    
    float rotScale         = getFPSNormalizedRotateFactor   ();
    float transScale       = getFPSNormalizedTranslateFactor();
    
    float analogRotate     = readAdjustedAnalog(mAnalogRotate,     mStickHasData);
    float analogLookUpDown = readAdjustedAnalog(mAnalogLookUpDown, mStickHasData);
    float analogStrafe     = readAdjustedAnalog(mAnalogStrafe,     mStickHasData);
    float analogMove       = readAdjustedAnalog(mAnalogMove,       mStickHasData);
 
    gadget::Digital::State buttonUpDownMode = mButtonUpDownMode->getData();
    gadget::Digital::State buttonMoveUp     = mButtonMoveUp    ->getData();
    gadget::Digital::State buttonMoveDown   = mButtonMoveDown  ->getData();
    
//    gmtl::Matrix44f headMat (getHeadMatrix());
    gmtl::Matrix44f transMat;
    
    gmtl::Vec3f axisX(1.0f, 0.0f, 0.0f);
    gmtl::Vec3f axisY(0.0f, 1.0f, 0.0f);
    gmtl::Vec3f axisZ(0.0f, 0.0f, 1.0f);
    
    // transform the y axis into local coordinates
    gmtl::Vec3f axisYLocal;
    gmtl::xform    (axisYLocal, matrix, axisY);
    gmtl::normalize(axisYLocal               );
    
    // extract head translation
//    gmtl::Vec3f headTrans;   
//    gmtl::setTrans(headTrans, headMat);
    
    // translate to head pos
//    gmtl::identity(transMat           );
//    gmtl::setTrans(transMat, headTrans);

//    gmtl::mult(newMatrix, transMat, newMatrix);
      
    if(buttonUpDownMode == gadget::Digital::ON)
    {
        // move along initial camera y-axis (move up/down)
        gmtl::identity(transMat);
        gmtl::setTrans(transMat, analogLookUpDown * transScale * axisYLocal);
        
        gmtl::mult(newMatrix, transMat, newMatrix);
    }
    else
    {
        // rotate around current camera x-axis (look up/down)
        gmtl::AxisAnglef rotX(analogLookUpDown * rotScale, axisX);
        
        gmtl::identity(transMat      );
        gmtl::setRot  (transMat, rotX);
        
        gmtl::mult(newMatrix, transMat, newMatrix);
    }
    
    if((buttonUpDownMode == gadget::Digital::OFF) &&
       (buttonMoveUp     == gadget::Digital::ON )   )
    {
        // move along the current camera pos y-axis (move up)
        gmtl::identity(transMat);
        gmtl::setTrans(transMat, -0.5f * transScale * axisYLocal);
        
        gmtl::mult(newMatrix, transMat, newMatrix);
    }
    else if((buttonUpDownMode == gadget::Digital::OFF) &&
            (buttonMoveDown   == gadget::Digital::ON )   )
    {
        // move along the current camera neg y-axis (move down)      
        gmtl::identity(transMat);
        gmtl::setTrans(transMat, 0.5f * transScale * axisYLocal);
        
        gmtl::mult(newMatrix, transMat, newMatrix);
    }
    
    // rotate around initial y-axis (turn left/right)
    gmtl::AxisAnglef rotY(analogRotate * rotScale, axisYLocal);
    
    gmtl::identity(transMat      );
    gmtl::setRot  (transMat, rotY);
    
    gmtl::mult(newMatrix, transMat, newMatrix);
    
    // move along current camera z-axis (forward/backward)
    gmtl::identity(transMat                                          );
    gmtl::setTrans(transMat, (- analogMove * transScale) * axisZ);
    
    gmtl::mult(newMatrix, transMat, newMatrix);
        
    // move along current camera x-axis (strafe left/right)
    gmtl::identity(transMat                                          );
    gmtl::setTrans(transMat, (- analogStrafe * transScale) * axisX);
    
    gmtl::mult(newMatrix, transMat, newMatrix);
    
    // undo head translation
//    gmtl::identity(transMat             );
//    gmtl::setTrans(transMat, - headTrans);
    
//    gmtl::mult(newMatrix, transMat, newMatrix);
}

