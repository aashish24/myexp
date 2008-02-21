
#include "MsgCore/Text.h"


void MsgCore::Text::setText( std::string text )
{
	mText = text;
}

void MsgCore::Text::setPos( Vec3f pos )
{
	mPos = pos;
}

void MsgCore::Text::setRot( Vec4f rot )
{
	mRot = rot;
}

void MsgCore::Text::setScale( Vec3f scale )
{
	mScale = scale;
}