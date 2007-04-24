/******************************************************************************
 *
 * Class defines the KeyboardMouse input and its callback. 
 *
 ******************************************************************************
 */
   
#ifndef __KEYBOARD_MOUSE_H__
#define __KEYBOARD_MOUSE_H__

#include <map>
#include <vector>
#include <string>

#include <gadget/Type/KeyboardMouseInterface.h>
#include <gadget/Type/KeyboardMouse/KeyEvent.h>
#include <gadget/Type/KeyboardMouse/MouseEvent.h>

namespace Dev
{
  /**************************************************************************
   *
   * Class defines the callback for the keyboard mouse input. 
   *
   **************************************************************************
   */
  class KeyboardMouseCallback 
  {
    public :
      /******************************************************************
       *
       * Constructor. 
       *
       ******************************************************************
       */
      KeyboardMouseCallback() {}

      /******************************************************************
       *
       * Destructor. 
       *
       ******************************************************************
       */
      virtual ~KeyboardMouseCallback() {}

      /******************************************************************
       *
       * Event handler for the "mouse move" event. 
       *
       ******************************************************************
       */
      virtual void mouseMotion( float, float) {}

      /******************************************************************
       *
       * 
       *
       ******************************************************************
       */
      virtual void passiveMouseMotion( float, float) {}

      /******************************************************************
       *
       * Event handler for a "mouse button press event". 
       *
       ******************************************************************
       */
      virtual void buttonPress( float, float, unsigned int ) {}
      
      /******************************************************************
       *
       * 
       *
       ******************************************************************
       */
      virtual void doubleButtonPress( float, float, unsigned int ) {}

      /******************************************************************
       *
       * Event handler for a "mouse button release event".
       *
       ******************************************************************
       */
      virtual void buttonRelease( float, float, unsigned int ) {}

      /******************************************************************
       *
       * Event handler for a "keyboard button press event". 
       *
       ******************************************************************
       */
      virtual void keyPress( char key ) {}

      /******************************************************************
       *
       * Event handler for a "keyboard button release event". 
       *
       ******************************************************************
       */
      virtual void keyRelease( char key) {}

      /******************************************************************
       *
       * Event handler for a "special key press event". 
       *
       ******************************************************************
       */
      virtual void specialKeyPress( char key ) {}

      /******************************************************************
       *
       * Event handler for a "keyboard button press event". 
       *
       ******************************************************************
       */
      virtual void specialKeyRelease( char key ) {}

      /******************************************************************
       *
       * ??
       *
       ******************************************************************
       */
      virtual void shutdown() {}

      /******************************************************************
       *
       * ??
       *
       ******************************************************************
       */
      virtual bool idle() { return false; }
  };

  /******************************************************************
   *
   * Class defines the keybaord mouse input device. 
   *
   ******************************************************************
   */
  class KeyboardMouse
  {
    public:
      /******************************************************************
       *
       * Constructor. 
       *
       ******************************************************************
       */
      KeyboardMouse();

      KeyboardMouse( int windth, int height );

      /******************************************************************
       *
       * Destructor. 
       *
       ******************************************************************
       */
      ~KeyboardMouse();
      
      /******************************************************************
       *
       * Singleton. 
       *
       ******************************************************************
       */
      static KeyboardMouse* instance();

      /******************************************************************
       *
       * Initialization. 
       *
       ******************************************************************
       */
      void init();

      /******************************************************************
       *
       * Return the current keyboard mouse callback. 
       *
       ******************************************************************
       */
      KeyboardMouseCallback* getCallBack(); 

      /******************************************************************
       *
       * Set the keyboard mouse callback. 
       *
       ******************************************************************
       */
      void setCallBack( KeyboardMouseCallback* cb );
      
      /******************************************************************
       *
       * Return the input area where the keyboard / mouse events 
       * are registered. 
       *
       ******************************************************************
       */
      void getInputArea( int width, int height );

      /******************************************************************
       *
       * Set the input area where the keyboard / mouse events will be 
       * registered. 
       *
       ******************************************************************
       */
      void setInputArea( int width, int height );

      /******************************************************************
       *
       * Update. 
       *
       ******************************************************************
       */
      void update();

    private:
      /******************************************************************
       *
       * Convert a gadget enum value to ascii value. 
       *
       ******************************************************************
       */
      unsigned int convertGadgetToAscii( gadget::Keys key );

      /******************************************************************
       *
       * Transform mouse position from window coordinate to in the 
       * range of [0-1]. 
       *
       ******************************************************************
       */
      void transformMousePos( int wx, int wy );

    private:
      /******************************************************************
       *
       * Extent of input area in the direction of X axis. 
       *
       ******************************************************************
       */
      int mInputAreaX;

      /******************************************************************
       *
       * Extent of input area in the direction of Y axis. 
       *
       ******************************************************************
       */
      int mInputAreaY;

      float mX;
      float mY;

      /******************************************************************
       *
       * Gaget keyboard mouse interface.
       *
       ******************************************************************
       */
      gadget::KeyboardMouseInterface    mKmInterface;
      
      /******************************************************************
       *
       * Its a singleton. 
       *
       ******************************************************************
       */
      static KeyboardMouse*        mKm;

      /******************************************************************
       *
       * Keyboard mouse callback. 
       *
       ******************************************************************
       */
      KeyboardMouseCallback*        mKmcb;
  };
}

#endif // __KEYBOARD_MOUSE_H__


