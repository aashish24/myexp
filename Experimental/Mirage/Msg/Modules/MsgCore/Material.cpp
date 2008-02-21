
#include "MsgCore/Material.h"

using namespace Msg::MsgCore;

void	Material::setAmbient( const Vec4f& ambient, Face face )
{
	switch( face )
	{
		case FRONT:
		{
			mFrontAmbientCom = ambient;
			break;
		}
		case BACK:
		{
			mBackAmbientCom  = ambient;
			break;
		}
		case FRONT_AND_BACK:
		{
			mFrontAmbientCom = ambient;
			mBackAmbientCom  = mFrontAmbientCom;
			mFrontAndBack    = true;
			break;
		}
	};
}

Vec4f	Material::getAmbient( Material::Face face ) const
{
	switch( face )
	{
		case FRONT:
		{
			return mFrontAmbientCom;
			break;
		}
		case BACK:
		{
			return mBackAmbientCom;
			break;
		}
		case FRONT_AND_BACK:
		{
			if( !mFrontAndBack )
			{
				std::cerr << "[Material::getAmbient] FRONT_AND_BACK called on material with "<< std::endl;
				std::cerr << "separate FRONT and BACK material. " << std::endl;
			}
			
			return mFrontAmbientCom;
			break;
		}
	};

	std::cerr << "[Material::getAmbient] Invalid Face : " << face << " passed. " << std::endl;
	return mFrontAmbientCom;
}

void	Material::setDiffuse( const Vec4f diffuse, Material::Face face )
{
	switch( face )
	{
		case FRONT:
		{
			mFrontDiffuseCom = diffuse;
			break;
		}
		case BACK:
		{
			mBackDiffuseCom = diffuse;
			break;
		}
		case FRONT_AND_BACK:
		{
			mFrontDiffuseCom = diffuse;
			mBackDiffuseCom  = mFrontDiffuseCom;
			mFrontAndBack	 = true;
			break;
		}
	};
}

Vec4f	Material::getDiffuse( Material::Face face ) const
{
	switch( face )
	{
		case FRONT:
		{
			return mFrontDiffuseCom;
			break;
		}
		case BACK:
		{
			return mBackDiffuseCom;
			break;
		}
		case FRONT_AND_BACK:
		{
			if( !mFrontAndBack )
			{
				std::cerr << "[Material::getDiffuse] FRONT_AND_BACK called on material with "<< std::endl;
				std::cerr << "separate FRONT and BACK material. " << std::endl;
			}
			return mFrontDiffuseCom;
			break;
		}
	};

	std::cerr << "[Material::getDiffuse] Invalid Face : " << face << " passed. " << std::endl;
	return mFrontDiffuseCom;
}

void	Material::setSpecular( const Vec4f specular, Material::Face face )
{
	switch( face )
	{
		case FRONT:
		{
			mFrontSpecularCom = specular;
			break;
		}
		case BACK:
		{
			mBackSpecularCom = specular;
			break;
		}
		case FRONT_AND_BACK:
		{
			mFrontSpecularCom = specular;
			mBackSpecularCom  = mFrontSpecularCom;
			mFrontAndBack	  = false;
			break;
		}
	};
}

Vec4f	Material::getSpecular( Material::Face face ) const
{
	switch( face )
	{
		case FRONT:
		{
			return mFrontSpecularCom;
			break;
		}
		case BACK:
		{
			mBackSpecularCom;
			break;
		}
		case FRONT_AND_BACK:
		{
			if( !mFrontAndBack )
			{
				std::cerr << "[Material::getSpecular] FRONT_AND_BACK called on material with "<< std::endl;
				std::cerr << "separate FRONT and BACK material. " << std::endl;
			}

			mFrontSpecularCom;
			break;
		}
	};
	return mFrontSpecularCom;
}

void	Material::setShininess( float shininess, Material::Face face )
{
	switch( face )
	{
		case FRONT:
		{
			mFrontShininess = shininess;
			break;
		}
		case BACK:
		{
			mBackShininess = shininess;
			break;
		}
		case FRONT_AND_BACK:
		{
			mFrontShininess = shininess;
			mBackShininess  = mFrontShininess;
			mFrontAndBack   = true;
			break;
		}
	};
}

float	Material::getShininess( Material::Face face ) const
{
	switch( face )
	{
		case FRONT:
		{
			return mFrontShininess;
			break;
		}
		case BACK:
		{
			return mBackShininess;
			break;
		}
		case FRONT_AND_BACK:
		{
			if( !mFrontAndBack )
			{
				std::cerr << "[Material::getShininess] FRONT_AND_BACK called on material with "<< std::endl;
				std::cerr << "separate FRONT and BACK material. " << std::endl;
			}
			return mFrontShininess;
			break;
		}
	}

	std::cerr << "[Material::getShininess] Invalid Face : " << face << " passed. " << std::endl;
	return  mFrontShininess;
}

bool Material::frontAndBack()
{
	return mFrontAndBack;
}