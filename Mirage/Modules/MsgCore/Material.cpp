
#include "MsgCore/Material.h"
#include "MsgCore/MirageOpenGL.h"

namespace Msg
{
  namespace MsgCore
  {
    void Material::getProperty( LightMode mode, MsgMath::Vec4f& val, Face face ) const
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


    void	Material::setProperty( LightMode mode, const MsgMath::Vec4f& val, Face face )
    {
      switch( mode )
      {
        case AMBIENT:
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
        case DIFFUSE:
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
        case SPECULAR:
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


    void Material::getProperty( LightMode mode, float& val, Face face ) const
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


    void Material::setProperty( LightMode mode, const float& val, Face face )
    {
      switch( mode )
      {
        case SHININESS:
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
    		      
              mFront = true;
              mBack = true;
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


    void Material::enable( const Face& face )
    {
      switch( face )
      {
        case FRONT: 
        {
          mFront = true;
          break;
        }
        case BACK: 
        {
          mBack = true;
          break;
        }
        case FRONT_AND_BACK: 
        {
          mFront = true;
          mBack = true;
          break;
        }
      }; // End switch. 
    }


    bool Material::enabledFrontAndBack()
    {
	    return ( mFront & mBack );
    }


    void Material::activate( Node* node )
    {
      if( this->mask() & IStateAttribute::ON )
      {
        if( mFront ) 
        {
          glMaterialfv( GL_FRONT, GL_AMBIENT,  mFrontAmbient.front() );
          glMaterialfv( GL_FRONT, GL_DIFFUSE,  mFrontDiffuse.front() );
          glMaterialfv( GL_FRONT, GL_SPECULAR, mFrontSpecular.front() );    
        }

        if( mBack ) 
        {
          glMaterialfv( GL_BACK, GL_AMBIENT,  mBackAmbient.front() );
          glMaterialfv( GL_BACK, GL_DIFFUSE,  mBackDiffuse.front() );
          glMaterialfv( GL_BACK, GL_SPECULAR, mBackSpecular.front() );    
        }
      }
    }


    void Material::deActivate( Node *node )
    {
    }
  }
}