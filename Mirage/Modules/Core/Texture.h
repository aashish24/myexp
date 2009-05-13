
#ifndef __MIRAGE_CORE_TEXTURE_H__
#define __MIRAGE_CORE_TEXTURE_H__

#include "Export.h"

#include "Core/Referenced.h"
#include "Core/TextureParam.h"
#include "Core/TextureEnv.h"
#include "Core/StateAttribute.h" 
#include "Core/Image.h"

#include "GL/glew.h"

namespace Mirage
{
	namespace Core
	{
		class MSG_EXPORT Texture : public StateAttribute
		{
			public:
				
        Texture() : StateAttribute(), 
          _texId    ( -1 ),
          _texType  (GL_TEXTURE_2D ), 
          _image    ( 0x0 ),
          _texParam ( new TextureParam() ), 
          _texEnv   ( new TextureEnv() )
        {
        }


				Texture( Image* image ) : StateAttribute(), 
          _texId    ( -1 ), 
          _texType  (GL_TEXTURE_2D ), 
          _image    ( image ), 
          _texParam ( new TextureParam() ), 
          _texEnv   ( new TextureEnv() )
        {          
        }        

            
        const int& getTexId() const 
        {
          return _texId;         
        }


        void setImage(Image* image)
        {
          _image = image;          
        }


        const TextureParam* getTextureParam() const
        {
          return _texParam.get();
        }

        void setTextureParam( TextureParam* texParam) 
        {
          _texParam = texParam;
        }


        const TextureEnv* getTexEnv() const
        {
          return _texEnv.get();
        }


        void setTextureEnv( TextureEnv* texEnv )
        {
          _texEnv = texEnv;
        }

      
        virtual std::string id() const
        {
          return "Texture";
        }


        virtual void init()
        {
        }

        
        virtual void contextInit()
        {
        }


        virtual void activate( Node* node )
        {
          glEnable( _texType );

          if( this->dirty() ) 
          {
            glGenTextures( 1, (GLuint*)&_texId );
            glBindTexture( _texType, _texId );

            // select modulate to mix texture with color for shading
            glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, _texEnv->_envMode );

            // when texture area is small, bilinear filter the closest mipmap
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                             _texParam->_minFilter );
            // when texture area is large, bilinear filter the first mipmap
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texParam->_magFilter );

            // if wrap is true, the texture wraps over at the edges (repeat)
            //       ... false, the texture ends at the edges (clamp)
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                             _texParam->_wrapS );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                             _texParam->_wrapT );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                             _texParam->_wrapR );                      
          
            switch(_texType )
            {
              case GL_TEXTURE_2D:
                glTexImage2D( _texType, 0, GL_RGB, _image->getWidth(), _image->getHeight(), 
                              0, _image->_format, GL_UNSIGNED_BYTE, _image->_data );
                _image = 0x0;
                break;
            };            
          }
          else
          {
            glBindTexture( _texType, _texId );
          }          
          
          this->dirty( false );
    
        }


        virtual void deActivate( Node* node )
        {
          glDisable( _texType );
        }


      protected: 

        virtual ~Texture()
        {
        }


      protected: 

        unsigned                      _texType;
        int                           _texId;         

        SmartPtr< Image >             _image;

        SmartPtr< TextureParam >      _texParam; 
        SmartPtr< TextureEnv >        _texEnv;
		};
	}
}

#endif  __MIRAGE_CORE_TEXTURE_H__


