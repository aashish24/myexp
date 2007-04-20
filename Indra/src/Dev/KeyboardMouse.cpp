
#include "VrjDev/KeyboardMouse.h"

#include <cstdlib>

using namespace VrjDev;

KeyboardMouse::KeyboardMouse()
{
	mKmcb = NULL;
}

KeyboardMouse::KeyboardMouse( int width, int height ) :
	mInputAreaX( width ), 
	mInputAreaY( height )
{
	mKmcb = NULL;
}

KeyboardMouse::~KeyboardMouse()
{
	if( mKm )
	{
		delete mKm;
	}
}

KeyboardMouse* KeyboardMouse::instance()
{
	if( mKm )
	{
		return mKm;
	}
	else
	{
		mKm = new KeyboardMouse();
		return mKm;
	}
}

void KeyboardMouse::init()
{
	mKmInterface.init( "VJKeyboard" );
}

KeyboardMouseCallback* KeyboardMouse::getCallBack()
{
	return mKmcb;
}

void KeyboardMouse::setCallBack( KeyboardMouseCallback *cb )
{
	if( mKmcb != NULL )
	{
		delete mKmcb; 
		mKmcb = 0;
	}

	mKmcb = cb;
}

void KeyboardMouse::getInputArea( int width, int height )
{
	mInputAreaX  = width; 
	mInputAreaY  = height; 
}

void KeyboardMouse::setInputArea( int width, int height )
{
	mInputAreaX = width;
	mInputAreaY = height;
}

void KeyboardMouse::update()
{
	gadget::KeyboardMouse::EventQueue::iterator eventQueItr;
	gadget::KeyboardMouse::EventQueue eventQ = mKmInterface->getEventQueue();

	for(eventQueItr = eventQ.begin(); eventQueItr != eventQ.end(); ++eventQueItr)
	{
		gadget::KeyEventPtr		keyEventPtr;
		gadget::MouseEventPtr	mouseEventPtr;

		const gadget::EventType type = (*eventQueItr)->type();
	
		// Keybaord inputs. 
		switch(type)
		{
			case gadget::KeyPressEvent:
			{
				keyEventPtr = 
					boost::dynamic_pointer_cast<gadget::KeyEvent>(*eventQueItr);			
				mKmcb->keyPress(keyEventPtr->getKeyChar());
				break;
			}
			case gadget::KeyReleaseEvent:
			{
				keyEventPtr = 
					boost::dynamic_pointer_cast<gadget::KeyEvent>(*eventQueItr);			
				mKmcb->keyRelease(keyEventPtr->getKeyChar());
				break;
			}
			case gadget::MouseButtonPressEvent:
			{
				mouseEventPtr = 
					boost::dynamic_pointer_cast<gadget::MouseEvent>(*eventQueItr);
				transformMousePos( mouseEventPtr->getX(), mouseEventPtr->getY() );
				mKmcb->buttonPress( mX, mY, convertGadgetToAscii( mouseEventPtr->getButton() ) );
				break;
			}
			case gadget::MouseButtonReleaseEvent:
			{
				mouseEventPtr = 
					boost::dynamic_pointer_cast<gadget::MouseEvent>(*eventQueItr);
				transformMousePos( mouseEventPtr->getX(), mouseEventPtr->getY() );				
				mKmcb->buttonRelease( mY, mY, convertGadgetToAscii( mouseEventPtr->getButton() ) );
				break;
			}
			case gadget::MouseMoveEvent:
			{
				mouseEventPtr = 
					boost::dynamic_pointer_cast<gadget::MouseEvent>(*eventQueItr);
				transformMousePos( mouseEventPtr->getX(), mouseEventPtr->getY() );
				mKmcb->mouseMotion( mX, mY );
				break;
			}
			default:
			{
				std::cerr << " [KeyboardMouse::update] Event type " << type
					<< " not handled " << std::endl;
				break;
			}

		};
	}
}

unsigned int KeyboardMouse::convertGadgetToAscii( gadget::Keys key )
{
	switch( key )
	{
		case gadget::MBUTTON1:
		{
			return 1;
			break;
		}
		case gadget::MBUTTON2:
		{
			return 2;
			break;
		}
		case gadget::MBUTTON3:
		{
			return 4;
			break;
		}
		case gadget::MBUTTON4:
		{
			return 3;
			break;
		}
		case gadget::MBUTTON5:
		{
			return 5;
			break;
		}
		case gadget::NO_MBUTTON:
		{
			return 0;
			break;
		}
		default:
		{
			return 0;
			break;
		}
	};
}

void KeyboardMouse::transformMousePos( int wx, int wy )
{
	mX = ( (double) wx / (double) mInputAreaX ) - 0.5;
	mY = 0.5 - ( (double) wy / (double) mInputAreaY );	
}

KeyboardMouse* KeyboardMouse::mKm = 0;
