
#ifndef _WAND_NAVIGATOR_H_
#define _WAND_NAVIGATOR_H_

#include <NavigatorBase.h>

// VRJuggler includes
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <gadget/Type/PositionInterface.h>

class WandNavigator : public NavigatorBase
{
  public:
    typedef NavigatorBase Inherited;
    typedef WandNavigator Self;
    
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             WandNavigator(vrj::App *pApp);
    virtual ~WandNavigator(void);
  
    /*=======================================================================*/
    /* Initialization                                                        */
    
    void setWandPositionName    (std::string const &posName =
                                 "VJWand"                       );
    void setAnalogRotateName    (std::string const &analogName =
                                 "WandStickAxisX"               );
    void setAnalogMoveName      (std::string const &analogName =
                                 "WandStickAxisY"               );
    void setButtonUpDownModeName(std::string const &buttonName =
                                 "WandButtonUpDownMode"         );
    
    virtual void initialize(void);
    
    /*=======================================================================*/
    /* Navigation                                                            */
    
    virtual void navigate(gmtl::Matrix44f const &matrix,
                          gmtl::Matrix44f       &newMatrix);

  private:
    gadget::PositionInterface  _wandPosition;      /**< The position of the wand */
    gadget::AnalogInterface    _analogRotate;      /**< Wand joystick X */
    gadget::AnalogInterface    _analogMove;        /**< Wand joystick Y */
    gadget::DigitalInterface   _buttonUpDownMode;  /**< Wand button 0 */
    
    std::string _wandPositionName;
    std::string _analogRotateName;
    std::string _analogMoveName;
    std::string _buttonUpDownModeName;
    bool        mStickHasData;
};

#endif // _WAND_NAVIGATOR_H_
