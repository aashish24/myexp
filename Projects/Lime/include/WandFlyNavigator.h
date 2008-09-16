
#ifndef _WAND_FLY_NAVIGATOR_H_
#define _WAND_FLY_NAVIGATOR_H_

#include <NavigatorBase.h>

// VRJuggler includes
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <gadget/Type/PositionInterface.h>

#include <gmtl/Matrix.h>

#include <deque>

class WandFlyNavigator : public NavigatorBase
{
  public:
    typedef NavigatorBase    Inherited;
    typedef WandFlyNavigator Self;
    
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             WandFlyNavigator(vrj::App *pApp);
    virtual ~WandFlyNavigator(void);
  
    /*=======================================================================*/
    /* Initialization                                                        */
    
    virtual void initialize(void);
    
    /*=======================================================================*/
    /* Navigation                                                            */
    
    virtual void navigate(gmtl::Matrix44f const &matrix,
                          gmtl::Matrix44f       &newMatrix);
  
  protected:
  
  private:
    gadget::PositionInterface  _wandPos;     /**< The position of the wand */
    gadget::DigitalInterface   _button0;     /**< Wand button 0 */
    gadget::DigitalInterface   _button1;     /**< Wand button 1 */
    gadget::DigitalInterface   _button2;     /**< Wand button 2 */
    gadget::DigitalInterface   _button3;     /**< Wand button 3 */
    gadget::DigitalInterface   _button4;     /**< Wand button 4 */
    gadget::DigitalInterface   _button5;     /**< Wand button 5 */
    gadget::AnalogInterface    _joyX;        /**< Wand joystick X */
    gadget::AnalogInterface    _joyY;        /**< Wand joystick Y */
    
    unsigned int                _frameCount;
    std::deque<gmtl::Matrix44f> _matrixCache;
    
};

#endif // _WAND_FLY_NAVIGATOR_H_
