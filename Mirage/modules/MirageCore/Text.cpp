
#include "MirageCore/Text.h"


void MirageCore::Text::setText( std::string text )
{
	mText = text;
}

void MirageCore::Text::setPos( Vec3f pos )
{
	mPos = pos;
}

void MirageCore::Text::setRot( Vec4f rot )
{
	mRot = rot;
}

void MirageCore::Text::setScale( Vec3f scale )
{
	mScale = scale;
}