
#ifndef __OGE_INTERFACES_I_EVENT_H__
#define __OGE_INTERFACES_I_EVENT_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IEvent : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IEvent );

        enum { IID = 3162216114 };

        enum Type
        {
          None = 0, 
          Timer = 1, 
          MouseButtonPress = 2, 
          MouseButtonRelease = 3, 
          MouseButtonDblClick = 4, 
          MouseMove = 5, 
          KeyPress = 6, 
          KeyRelease = 7, 
          FocusIn = 8, 
          FocusOut = 9, 
          Enter = 10, 
          Leave = 11, 
          Paint = 12, 
          Move = 13, 
          Resize = 14, 
          Create = 15, 
          Destroy = 16, 
          Show = 17, 
          Hide = 18, 
          Close = 19, 
          Quit = 20, 
          Reparent = 21, 
          ShowMinimized = 22, 
          ShowNormal = 23, 
          WindowActivate = 24, 
          WindowDeactivate = 25, 
          ShowToParent = 26, 
          HideToParent = 27, 
          ShowMaximized = 28, 
          ShowFullScreen = 29, 
          Accel = 30, 
          Wheel = 31, 
          AccelAvailable = 32, 
          CaptionChange = 33, 
          IconChange = 34, 
          ParentFontChange = 35, 
          ApplicationFontChange = 36, 
          ParentPaletteChange = 37, 
          ApplicationPaletteChange = 38, 
          PaletteChange = 39, 
          Clipboard = 40, 
          Speech = 42, 
          SockAct = 50, 
          AccelOverride = 51, 
          DeferredDelete = 52, 
          DragEnter = 60, 
          DragMove = 61, 
          DragLeave = 62, 
          Drop = 63, 
          DragResponse = 64, 
          ChildInserted = 70, 
          ChildRemoved = 71, 
          LayoutHint = 72, 
          ShowWindowRequest = 73, 
          WindowBlocked = 74, 
          WindowUnblocked = 75, 
          ActivateControl = 80, 
          DeactivateControl = 81, 
          ContextMenu = 82, 
          IMStart = 83, 
          IMCompose = 84, 
          IMEnd = 85, 
          Accessibility = 86, 
          TabletMove = 87, 
          LocaleChange = 88, 
          LanguageChange = 89, 
          LayoutDirectionChange = 90, 
          Style = 91, 
          TabletPress = 92, 
          TabletRelease = 93, 
          OkRequest = 94, 
          HelpRequest = 95, 
          WindowStateChange = 96, 
          IconDrag = 97, 
          JoystickTiltUp = 98, 
          JoystickTiltDown = 99, 
          JoystickTiltLeft= 100, 
          JoystickTiltRight = 101, 
          JoystickTiltUpLeft = 102,          
          JoystickTiltUpRight = 103,          
          JoystickTiltDownLeft = 104,
          JoystickTiltDownRight = 105,
          JoystickTiltStickClick = 106,
          JoystickTilt = 107, 
          JoystickTiltPos = 108, 
          JoystickTiltNeg = 109, 
          KeyUp = 110, 
          KeyDown = 111,
          User = 1000, 
          MaxUser = 65535          
        };
              
        virtual Type  type() const = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_EVENT_H__
