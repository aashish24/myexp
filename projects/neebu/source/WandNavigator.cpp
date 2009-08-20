
#include <WandNavigator.h>

#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Xforms.h>

WandNavigator::WandNavigator(vrj::App *pApp)
    : Inherited        (pApp),
      _wandPosition    (),
      _analogRotate    (),
      _analogMove      (),
      _buttonUpDownMode(),
      _wandPositionName    ("VJWand"),
      _analogRotateName    ("WandStickAxisX"),
      _analogMoveName      ("WandStickAxisY"),
      _buttonUpDownModeName("WandButtonUpDownMode"),
      mStickHasData       (false)
{
}

WandNavigator::~WandNavigator(void)
{
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
WandNavigator::setWandPositionName(std::string const &posName)
{
    _wandPositionName = posName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
WandNavigator::setAnalogRotateName(std::string const &analogName)
{
    _analogRotateName = analogName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
WandNavigator::setAnalogMoveName(std::string const &analogName)
{
    _analogMoveName = analogName;
}

/*! Set the name to use vor the vrjuggler device.
    \note Only has an effect if set \em before calling \c initialize
 */
void
WandNavigator::setButtonUpDownModeName(std::string const &buttonName)
{
    _buttonUpDownModeName = buttonName;
}

void
WandNavigator::initialize(void)
{
    if(getInitialized())
        return;
        
    Inherited::initialize();
        
    _wandPosition    .init(_wandPositionName);
    _analogRotate    .init(_analogRotateName);
    _analogMove      .init(_analogMoveName);
    _buttonUpDownMode.init(_buttonUpDownModeName);
}

void
WandNavigator::navigate(
    gmtl::Matrix44f const &matrix, gmtl::Matrix44f &newMatrix)
{
    if(getEnabled() == false)
        return;
        
    Inherited::navigate(matrix, newMatrix);
        
//     std::cout << "Position:"
//               << matrix[0][3] << "  "
//               << matrix[1][3] << "  "
//               << matrix[2][3] << "  "
//               << matrix[3][3] << std::endl;
    
     setTranslateFactor(30.0f);
    float rotScale   = getFPSNormalizedRotateFactor   ();
    float transScale = getFPSNormalizedTranslateFactor();
       
    gmtl::Matrix44f wandMat(_wandPosition->getData(
        getApp()->getDrawScaleFactor()));
//    gmtl::Matrix44f headMat(getHeadMatrix());
        
    float analogRotate = readAdjustedAnalog(_analogRotate, mStickHasData);
    float analogMove   = readAdjustedAnalog(_analogMove,   mStickHasData);
       
    gadget::Digital::State upDownModeState = _buttonUpDownMode->getData();
        
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
    
    if(analogMove != 0.0f)
    {
        if(upDownModeState == gadget::Digital::ON)
        {
            // move along initial camera y-axis (move up/down)
            gmtl::identity(transMat                                      );
            gmtl::setTrans(transMat, analogMove * transScale * axisYLocal);
            
            gmtl::mult(newMatrix, transMat, newMatrix);
        }
        else
        {
            // move along the wand's -z axis
            gmtl::Vec3f wandDir;
            gmtl::xform(wandDir, wandMat, axisZ);
            
            gmtl::identity(transMat                               );
            gmtl::setTrans(transMat, analogMove * transScale * wandDir);
            
            gmtl::mult(newMatrix, transMat, newMatrix);
        }
    }
    
    if(analogRotate != 0.0f)
    {
        // rotate around initial y-axis (turn left/right)
        gmtl::AxisAnglef rotY     (analogRotate * rotScale, axisYLocal);
               
        gmtl::identity(transMat      );
        gmtl::setRot  (transMat, rotY);
        
        gmtl::mult(newMatrix, transMat, newMatrix);
    }
    
    // undo head translation
//    gmtl::identity(transMat             );
//    gmtl::setTrans(transMat, - headTrans);
    
//    gmtl::mult(newMatrix, transMat, newMatrix);
}
