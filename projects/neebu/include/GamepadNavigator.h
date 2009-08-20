
#ifndef _GAMEPADNAVIAGTOR_H_
#define _GAMEPADNAVIAGTOR_H_

#include <NavigatorBase.h>

// VRJuggler includes
#include <gadget/Type/DigitalInterface.h>
#include <gadget/Type/AnalogInterface.h>

class GamepadNavigator : public NavigatorBase
{
  public:
    typedef NavigatorBase    Inherited;
    typedef GamepadNavigator Self;
  
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             GamepadNavigator(vrj::App *pApp);
    virtual ~GamepadNavigator(void);
    
    /*=======================================================================*/
    /* Initialization                                                        */
    
    void setAnalogRotateName        (std::string const  &analogName =
                                     "GamepadStickLeftAxisX"          );
    void setAnalogLookUpDownName    (std::string const  &analogName =
                                     "GamepadStickLeftAxisY"          );
    void setAnalogStrafeName        (std::string const &analogName =
                                     "GamepadStickRightAxisX"         );
    void setAnalogMoveName          (std::string const &analogName =
                                     "GamepadStickRightAxisY"         );
    void setButtonMoveUpDownModeName(std::string const &buttonName =
                                     "GamepadButtonUpDownMode"        );
    void setButtonMoveUpName        (std::string const &buttonName =
                                     "GamepadButtonMoveUp"            );
    void setButtonMoveDownName      (std::string const &buttonName =
                                     "GamepadButtonMoveDown"          );
    
    virtual void initialize(void);
    
    /*=======================================================================*/
    /* Navigation                                                            */
    
    virtual void navigate(gmtl::Matrix44f const &matrix,
                          gmtl::Matrix44f       &newMatrix);
    
  private:
    gadget::AnalogInterface  mAnalogRotate;     /**< Gamepad left stick */
    gadget::AnalogInterface  mAnalogLookUpDown;
    gadget::AnalogInterface  mAnalogStrafe;     /**< Gamepad right stick */
    gadget::AnalogInterface  mAnalogMove;
    
    gadget::DigitalInterface mButtonUpDownMode; /**< Gamepad button 0 */
    gadget::DigitalInterface mButtonMoveUp;
    gadget::DigitalInterface mButtonMoveDown;
    
    std::string mAnalogRotateName;
    std::string mAnalogLookUpDownName;
    std::string mAnalogStrafeName;
    std::string mAnalogMoveName;
    std::string mButtonMoveUpDownModeName;
    std::string mButtonMoveUpName;
    std::string mButtonMoveDownName;
    bool        mStickHasData;    
};

#endif // _GAMEPADNAVIAGTOR_H_
