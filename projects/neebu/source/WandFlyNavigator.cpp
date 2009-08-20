
#include <WandFlyNavigator.h>

#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

WandFlyNavigator::WandFlyNavigator(vrj::App *pApp)
    : Inherited(pApp),
      _wandPos (),
      _button0 (),
      _button1 (),
      _button2 (),
      _button3 (),
      _button4 (),
      _button5 (),
      _joyX    (),
      _joyY    ()
{
}

WandFlyNavigator::~WandFlyNavigator(void)
{
}

void
WandFlyNavigator::initialize(void)
{
    if(getInitialized())
        return;
        
    Inherited::initialize();
    
    std::string wandPosName("VJWand");
    std::string but0Name("VJButton0");
    std::string but1Name("VJButton1");
    std::string but2Name("VJButton2");
    std::string but3Name("VJButton3");
    std::string but4Name("VJButton4");
    std::string but5Name("VJButton5");

    std::string joyxName("VJAnalogX");
    std::string joyyName("VJAnalogY"); 
    
    _wandPos.init(wandPosName);
    _button0.init(but0Name);
    _button1.init(but1Name);
    _button2.init(but2Name);
    _button3.init(but3Name);
    _button4.init(but4Name);
    _button5.init(but5Name);
    _joyX   .init(joyxName);
    _joyY   .init(joyyName);
}

void
WandFlyNavigator::navigate(
    gmtl::Matrix44f const &matrix, gmtl::Matrix44f &newMatrix)
{
    if(getEnabled() == false)
        return;

    unsigned int const frameDelay = 10;
    float              rotScale   = getRotateFactor   ();
    float              transScale = getTranslateFactor();

    gmtl::Matrix44f wandMat(_wandPos->getData(getApp()->getDrawScaleFactor()));
    
    float stickX = adjustAnalog(_joyX->getData());
    float stickY = adjustAnalog(_joyY->getData());
    
    gadget::Digital::State b0State = _button0->getData();
    gadget::Digital::State b1State = _button1->getData();
    gadget::Digital::State b2State = _button2->getData();
    gadget::Digital::State b3State = _button3->getData();
        
    gmtl::Matrix44f transMat;
    
    gmtl::Vec3f axisX(1.0f, 0.0f, 0.0f);
    gmtl::Vec3f axisY(0.0f, 1.0f, 0.0f);
    gmtl::Vec3f axisZ(0.0f, 0.0f, 1.0f);
    
    // transform the y axis into local coordinates
    gmtl::Vec3f axisYLocal;
    gmtl::xform    (axisYLocal, matrix, axisY);
    gmtl::normalize(axisYLocal               );

    ++_frameCount;
    
    if(b0State == gadget::Digital::TOGGLE_ON)
    {
        _frameCount = 0;
        _matrixCache.clear();
    }
    
    if(b0State == gadget::Digital::ON)
    {
        if(_frameCount > frameDelay)
        {
            // after the delay rotate to follow wand direction
            std::cout << "WandFlyNavigator::navigate: Following wand direction" << std::endl;
            
            gmtl::Matrix44f currentDir = _matrixCache[0];
            gmtl::Matrix44f nextDir    = _matrixCache[1];
            
//             transMat.invertFrom(currentDir);
//             transMat.multLeft  (nextDir   );
//             
//             // erase translation component
//             transMat[3] = OSG::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
//             
//             modelMatrix.multLeft(transMat);
//             
//             _matrixCache.pop_front();
//             
//             transMat    .setValue (wandMat.getData());
//             _matrixCache.push_back(transMat         );
        }
        else
        {
            // remember wand direction
            std::cout << "WandFlyNavigator::navigate: Remembering wand direction" << std::endl;
            
//             transMat    .setValue (wandMat.getData());
//             _matrixCache.push_back(transMat         );
        }
    }
    
    if(stickY != 0.0f)
    {
        // move along the wand's -z axis
//         std::cout << "Move along wand -z axis" << std::endl;
//         
//         gmtl::Vec3f wandDir(axisZ[0], axisZ[1], axisZ[2]);
//         gmtl::xform(wandDir, wandMat, wandDir);
//         
//         std::cout << "wandDir: " << wandDir << std::endl;
//         
//         OSG::Vec3f trans(wandDir[0], wandDir[1], wandDir[2]);
//         
//         transMat.setIdentity (                            );
//         transMat.setTranslate(joyYVal * transScale * trans);
//     
//         std::cout << "transMat[4]: " << transMat[4] << std::endl;
//         
//         modelMatrix.multLeft(transMat);
    }
}
