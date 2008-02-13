
#include "oge/core/Text.h"


void core::Text::setText( std::string text )
{
	mText = text;
}

void core::Text::setPos( Vec3f pos )
{
	mPos = pos;
}

void core::Text::setRot( Vec4f rot )
{
	mRot = rot;
}

void core::Text::setScale( Vec3f scale )
{
	mScale = scale;
}