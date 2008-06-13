
#include "MsgCore/Material.h"

using namespace Msg::MsgCore;

void Material::getProperty( Material::ColorMode mode, Vec4f& val, Material::Face face ) const
{
  switch( mode )
  {
    case AMBIENT: 
    {
      switch( face )
      {
	      case FRONT:
	      {
		      val = mFrontAmbient;
		      break;
	      }
	      case BACK:
	      {
		      val = mBackAmbient;
		      break;
	      }
	      case FRONT_AND_BACK:
	      {
		      if( !mFrontAndBack )
		      {
            std::cerr << "Error No: FRONT_AND_BACK called on material with "<< std::endl;
			      std::cerr << "separate FRONT and BACK material. " << std::endl;
		      }
    			
		      val = mFrontAmbient;
		      break;
	      }
        default:
        {
          std::cerr << "Error No: Invalid Face " << face << std::endl;
          break;
        }
      };
      break;
    }
    case DIFFUSE: 
    {
      switch( face )
      {
	      case FRONT:
	      {
		      val = mFrontDiffuse;
		      break;
	      }
	      case BACK:
	      {
		      val = mBackDiffuse;
		      break;
	      }
	      case FRONT_AND_BACK:
	      {
		      if( !mFrontAndBack )
		      {
            std::cerr << "Error No: FRONT_AND_BACK called on material with "<< std::endl;
			      std::cerr << "separate FRONT and BACK material. " << std::endl;
		      }
    			
		      val = mFrontDiffuse;
		      break;
	      }
      };
      break;
    }
    case SPECULAR: 
    {
      switch( face )
      {
	      case FRONT:
	      {
		      val = mFrontSpecular;
		      break;
	      }
	      case BACK:
	      {
		      val = mBackSpecular;
		      break;
	      }
	      case FRONT_AND_BACK:
	      {
		      if( !mFrontAndBack )
		      {
            std::cerr << "Error No: FRONT_AND_BACK called on material with "<< std::endl;
			      std::cerr << "separate FRONT and BACK material. " << std::endl;
		      }
    			
		      val = mFrontSpecular;
		      break;
	      }
      };      
      break;
    }
    default:
    {
      std::cerr << "Error No: Invalid Face " << face << std::endl;
      break;
    }
  }
}   


void	Material::setProperty( Material::ColorMode mode, const Vec4f& val, Face face )
{
  switch( mode )
  {
    case Material::AMBIENT:
    {
      switch( face )
      {
        case FRONT:
		    {
			    mFrontAmbient = val;
			    break;
		    }
		    case BACK:
		    {
			    mBackAmbient = val;
			    break;
		    }
		    case FRONT_AND_BACK:
		    {
			    mFrontAmbient = val;
			    mBackAmbient  = val;
			    mFrontAndBack = true;
			    break;
		    }
        default: 
        {
          std::cerr << "Error No: Invalid Face " << face << std::endl;
          break;
        }
      };
      break;
    }
    case Material::DIFFUSE:
    {
      switch( face )
      {
        case FRONT:
		    {
			    mFrontDiffuse = val;
			    break;
		    }
		    case BACK:
		    {
			    mBackDiffuse = val;
			    break;
		    }
		    case FRONT_AND_BACK:
		    {
			    mFrontDiffuse = val;
			    mBackDiffuse  = val;
			    mFrontAndBack = true;
			    break;
		    }
        default: 
        {
          std::cerr << "Error No: Invalid Face " << face << std::endl;
          break;
        }
      };
      break;
    }
    case Material::SPECULAR:
    {
      switch( face )
      {
        case FRONT:
		    {
          mFrontSpecular = val;
			    break;
		    }
		    case BACK:
		    {
          mBackSpecular  = val;
			    break;
		    }
		    case FRONT_AND_BACK:
		    {
			    mFrontSpecular = val;
			    mBackSpecular  = val;
			    mFrontAndBack  = true;
			    break;
		    }
        default: 
        {
          std::cerr << "Error No: Invalid Face " << face << std::endl;
          break;
        }
      };
      break;
    }    
    default: 
    {
      std::cerr << "Error No: Invalid ColorMode " << mode << std::endl;
      break;
    }
  };
}


void Material::getProperty( Material::ColorMode mode, float& val, Material::Face face ) const
{
  switch( mode )
  {
    case SHININESS: 
    {
      switch( face )
      {
        case FRONT:
        {
          val = mFrontShininess;
          break;
        }
        case BACK:
        {
          val = mBackShininess;
          break;
        }
        case FRONT_AND_BACK:
        {
          if( !mFrontAndBack )
          {
            std::cerr << "Error No: FRONT_AND_BACK called on material with "<< std::endl;
	          std::cerr << "separate FRONT and BACK material. " << std::endl;
          }
    			
          val = mFrontShininess;
          break;
        }
        default:
        {
          std::cerr << "Error No: Invalid Face " << face << std::endl;
          break;
        }
      }; // switch( face ). 
      break;
    }
    default:
    {
      std::cerr << "Error No: Invalid ColorMode " << mode << std::endl;
      break;
    }
  }; // switch( mode ).
}


void Material::setProperty( Material::ColorMode mode, const float& val, Material::Face face )
{
  switch( mode )
  {
    case Material::SHININESS:
    {
      switch( face )
      {
        case FRONT:
	      {
          mFrontShininess = val;
		      break;
	      }
	      case BACK:
	      {
          mBackShininess  = val;
		      break;
	      }
	      case FRONT_AND_BACK:
	      {
		      mFrontShininess = val;
		      mBackShininess  = val;
		      mFrontAndBack   = true;
		      break;
	      }
        default: 
        {
          std::cerr << "Error No: Invalid Face " << face << std::endl;
          break;
        }
      };
      break;
    }
    default:
    {
      std::cerr << "Error No: Invalid ColorMode" << mode << std::endl;
      break;
    }
  }  
}


bool Material::enabledFrontAndBack()
{
	return mFrontAndBack;
}


void Material::activateStateSet( Node* node )
{
}