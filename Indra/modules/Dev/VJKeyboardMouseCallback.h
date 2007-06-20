/******************************************************************************
 *
 * Class implementing KeyboardMouse update callback. 
 *
 ******************************************************************************
 */ 

#ifndef __DEV_OSGKEYBOARDMOUSECALLBACK_H__
#define __DEV_OSGKEYBOARDMOUSECALLBACK_H__

#include "osg/Matrix"

#include "Producer/Trackball"

#include "Dev/KeyboardMouse.h"

namespace osg
{
  class Group;
}

namespace Dev 
{
  class OsgKeyboardMouseCallback : public KeyboardMouseCallback
  {
    public:
      OsgKeyboardMouseCallback( osg::Group* sceneGroup );        
      virtual ~OsgKeyboardMouseCallback();

      virtual void mouseMotion( float, float);
      virtual void passiveMouseMotion( float, float){}
      virtual void buttonPress( float, float, unsigned int );
      virtual void doubleButtonPress( float, float, unsigned int );
      virtual void buttonRelease( float, float, unsigned int );
      virtual void keyPress( char key );
      virtual void keyRelease( char key );
      virtual void specialKeyPress( char key ) {}
      virtual void specialKeyRelease( char key ){}
      virtual void shutdown(){}
      virtual bool idle() { return false; }

      virtual void resetTrackball();
      virtual void changeRenderState();
      osg::Matrixd getViewMatrix();

      float getX()
      {
        return mX;
      }

      float getY()
      {
        return mY;
      }

      unsigned int getButton()
      {
        return mButton;
      }
    
    private:      
      float      mX, mY;
      float      mXAtButtonPress, mYAtButtonPress;
      unsigned int    mButton;
      bool            mMouseMovingOnPreviousRelease;
        bool            mDone;

      osg::ref_ptr< Producer::Trackball >   mTrackball;
      osg::ref_ptr< osg::Group >        mSceneGroup;
  };
}

#endif // __DEV_OSGKEYBOARDMOUSECALLBACK_H__
