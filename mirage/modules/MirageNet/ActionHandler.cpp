
#include "ActionHandler.h"

using namespace glControl;

void ActionHandler::setKeyToAction( Keys key, Action action)
{
	mKeyToAction[ key ]	= action;
}

void ActionHandler::setMouseToAction( MouseButtons mouseButton, Action action )
{
	mMouseToAction[ mouseButton ] = action;
}

Action ActionHandler::getAction( const Keys key )
{
	return mKeyToAction[ key ];
}

Action ActionHandler::getAction( const MouseButtons mouseButton )
{
	return mMouseToAction[ mouseButton ];
}