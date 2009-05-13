
#ifndef __MIRAGE_CORE_TEXTURE_ENV_H__
#define __MIRAGE_CORE_TEXTURE_ENV_H__

#include "Export.h"

#include "Core/StateAttribute.h" 

#include "GL/glew.h"

namespace Mirage
{
	namespace Core
	{
    class MSG_EXPORT TextureEnv : public Object
		{
			public:
				
        TextureEnv() : Object(), 
          _envMode( GL_MODULATE )        
        {
        }		        


        const unsigned& getEnvMode() const
        {
          return _envMode;
        }


        void setEnvMode(const unsigned& val) 
        {
          _envMode = val;   
        }


      protected: 
        
        ~TextureEnv()
        {
        }


      public: 
        
        unsigned _envMode;
    };
  }
}

#endif  __MIRAGE_CORE_TEXTURE_ENV_H__


